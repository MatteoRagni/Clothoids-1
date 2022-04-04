/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file ClothoidSpline-LMSolver.cc
 * @author Matteo Ragni (info@ragni.me)
 *
 * @copyright Copyright (c) 2022 Matteo Ragni
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifdef G2LIB_LMSOLVE_CLOTHOID_SPLINE

#include "Clothoids/ClothoidSpline-Solver.hxx"

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <Eigen/Eigen>
#include <unsupported/Eigen/LevenbergMarquardt>

namespace G2lib {
  namespace Interpolation {

    using G2lib::ClothoidSplineG2;
    using G2lib::int_type;
    using G2lib::real_type;
    typedef Eigen::SparseFunctor<real_type, int_type> SparseFunctor;

    /* Levemberg Marquardt Solver */
    class LMSolver : public Solver {
      struct ClothoidSplineProblem : SparseFunctor {
        LMSolver &             m_solver;
        std::vector<int_type>  m_jacobian_rows;
        std::vector<int_type>  m_jacobian_cols;
        std::vector<real_type> m_jacobian_result;

        ClothoidSplineProblem(LMSolver & solver);
        int operator()(const SparseFunctor::InputType & theta, SparseFunctor::ValueType & constraints_value) const;
        int df(const SparseFunctor::InputType & theta, SparseFunctor::JacobianType & jacobian_value);
      };

     public:
      LMSolver(const ClothoidSplineG2 & spline) : Solver(spline) {};
      virtual Result solve() override;
    };

    LMSolver::ClothoidSplineProblem::ClothoidSplineProblem(LMSolver & solver)
        : SparseFunctor(solver.theta_size(), solver.constraints_size()), m_solver(solver),
          m_jacobian_rows(std::vector<int_type>(solver.jacobian_pattern_size(), 0)),
          m_jacobian_cols(std::vector<int_type>(solver.jacobian_pattern_size(), 0)),
          m_jacobian_result(std::vector<real_type>(solver.jacobian_pattern_size(), 0.0)) {
      m_solver.spline().jacobian_pattern(&m_jacobian_rows.front(), &m_jacobian_cols.front());
    }

    int LMSolver::ClothoidSplineProblem::operator()(
        const SparseFunctor::InputType & theta, SparseFunctor::ValueType & constraints_value) const {
      if (m_solver.spline().constraints(theta.data(), constraints_value.data()))
        return 0;
      return 1;
    }

    int LMSolver::ClothoidSplineProblem::df(
        const SparseFunctor::InputType & theta, SparseFunctor::JacobianType & jacobian_value) {
      if (!(m_solver.spline().jacobian(theta.data(), &m_jacobian_result.front())))
        return 1;
      for (int i = 0; i < m_solver.jacobian_pattern_size(); i++) {
        jacobian_value.coeffRef(m_jacobian_rows[i], m_jacobian_cols[i]) = m_jacobian_result[i];
      }
      jacobian_value.makeCompressed();
      return 0;
    }

    Result LMSolver::solve() {
      LMSolver::ClothoidSplineProblem problem(*this);
      Eigen::LevenbergMarquardt<LMSolver::ClothoidSplineProblem> lm(problem);
      lm.setFtol(1e-20);

      Eigen::VectorXd theta_opts = Eigen::VectorXd::Map(theta_solution().data(), theta_solution().size());
      lm.minimize(theta_opts);
      Eigen::ComputationInfo info = lm.info();
      std::copy(theta_opts.data(), theta_opts.data() + theta_opts.size(), theta_solution().begin());

      switch (info) {
        case (Eigen::Success):
          return Result(ResultType::Success, lm.fnorm(), lm.iterations());
          break;
        case (Eigen::NumericalIssue):
          return Result(ResultType::NumericalIssue, lm.fnorm(), lm.iterations());
          break;
        case (Eigen::NoConvergence):
          return Result(ResultType::NoConvergence, lm.fnorm(), lm.iterations());
          break;
        case (Eigen::InvalidInput):
          return Result(ResultType::InvalidInput, lm.fnorm(), lm.iterations());
          break;
      }
      return false;
    }

    void Interpolator::buildP1(real_type theta_0, real_type theta_1, ClothoidList & result) {
      m_spline.setP1(theta_0, theta_1);
      build_clothoid_spline();
      LMSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

    void Interpolator::buildP2(ClothoidList & result) {
      m_spline.setP2();
      build_clothoid_spline();
      LMSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

  } /* namespace Interpolation */
} /* namespace G2lib */

#endif