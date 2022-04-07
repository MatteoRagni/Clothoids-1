/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file ClothoidSpline-IpoptSolver.cc
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

#ifdef G2LIB_IPOPT_CLOTHOID_SPLINE

#include "Clothoids/ClothoidSpline-Interpolation.hxx"

#include <IpIpoptApplication.hpp>
#include <IpSolveStatistics.hpp>
#include <IpSmartPtr.hpp>
#include <algorithm>
#include <stdexcept>

namespace G2lib {
  namespace Interpolation {

    using G2lib::ClothoidSplineG2;
    using G2lib::int_type;
    using G2lib::real_type;

    using Ipopt::ApplicationReturnStatus;
    using Ipopt::Index;
    using Ipopt::IpoptApplication;
    using Ipopt::Number;
    using Ipopt::SmartPtr;
    using Ipopt::SolverReturn;
    using Ipopt::TNLP;

    class IpoptSolver : public Solver {
      class ClothoidSplineProblem : public TNLP {
        IpoptSolver & m_solver;
        SolverReturn  m_solver_return;

       public:
        ClothoidSplineProblem(IpoptSolver & solver);

        virtual bool get_nlp_info(
            Index &                theta_size,
            Index &                contraints_size,
            Index &                jacobian_pattern_size,
            Index &                hessian_pattern_size,
            TNLP::IndexStyleEnum & pattern_index_style);

        virtual bool get_bounds_info(
            Index    theta_size,
            Number * theta_min,
            Number * theta_max,
            Index    constraints_size,
            Number * constraints_min,
            Number * constraints_max);

        virtual bool get_starting_point(
            Index    theta_size,
            bool     init_theta,
            Number * theta_ics,
            bool     init_z,
            Number * z_L,
            Number * z_U,
            Index    constraints_size,
            bool     init_lambda,
            Number * lambda);

        virtual bool eval_f(Index theta_size, const Number * theta, bool new_theta, Number & obj_value);

        virtual bool eval_grad_f(Index theta_size, const Number * theta, bool new_theta, Number * grad_f);

        virtual bool eval_g(Index theta_size, const Number * theta, bool new_theta, Index constraints_size, Number * g);

        virtual bool eval_jac_g(
            Index          theta_size,
            const Number * theta,
            bool           new_theta,
            Index          constraints_size,
            Index          jacobian_pattern_size,
            Index *        jacobian_rows,
            Index *        jacobian_cols,
            Number *       jacobian_values);

        virtual void finalize_solution(
            SolverReturn                       status,
            Index                              n,
            const Number *                     x,
            const Number *                     z_L,
            const Number *                     z_U,
            Index                              m,
            const Number *                     g,
            const Number *                     lambda,
            Number                             obj_value,
            const Ipopt::IpoptData *           ip_data,
            Ipopt::IpoptCalculatedQuantities * ip_cq);

        SolverReturn solver_return() { return m_solver_return; }
      };

     public:
      IpoptSolver(const ClothoidSplineG2 & spline) : Solver(spline) {};
      virtual Result solve() override;
    };

    IpoptSolver::ClothoidSplineProblem::ClothoidSplineProblem(IpoptSolver & solver)
        : m_solver(solver), m_solver_return(SolverReturn::INVALID_OPTION) {}

    bool IpoptSolver::ClothoidSplineProblem::get_nlp_info(
        Index &                theta_size,
        Index &                constraints_size,
        Index &                jacobian_pattern_size,
        Index &                hessian_pattern_size,
        TNLP::IndexStyleEnum & pattern_index_style) {
      theta_size            = m_solver.theta_size();
      constraints_size      = m_solver.constraints_size();
      jacobian_pattern_size = m_solver.jacobian_pattern_size();
      hessian_pattern_size  = m_solver.lagrangian_hessian_size();
      pattern_index_style   = TNLP::C_STYLE;
      return true;
    }

    bool IpoptSolver::ClothoidSplineProblem::get_bounds_info(
        Index    theta_size,
        Number * theta_min,
        Number * theta_max,
        Index    constraints_size,
        Number * constraints_min,
        Number * constraints_max) {
      if (theta_size != m_solver.theta_size())
        return false;

      if (constraints_size != m_solver.constraints_size())
        return false;

      if ((theta_min == nullptr) || (theta_max == nullptr) || (constraints_min == nullptr) ||
          (constraints_max == nullptr))
        return false;

      std::fill_n(constraints_min, constraints_size, 0.0);
      std::fill_n(constraints_max, constraints_size, 0.0);
      std::copy(m_solver.theta_min().begin(), m_solver.theta_min().end(), theta_min);
      std::copy(m_solver.theta_max().begin(), m_solver.theta_max().end(), theta_max);
      return true;
    }

    bool IpoptSolver::ClothoidSplineProblem::get_starting_point(
        Index    theta_size,
        bool     init_theta,
        Number * theta_ics,
        bool     init_z,
        Number * z_L,
        Number * z_U,
        Index    constraints_size,
        bool     init_lambda,
        Number * lambda) {
      if (theta_size != m_solver.theta_size())
        return false;

      if (constraints_size != m_solver.constraints_size())
        return false;

      if (init_z)
        return false;

      if (init_lambda)
        return false;

      if (init_theta) {
        std::copy(m_solver.theta_solution().begin(), m_solver.theta_solution().end(), theta_ics);
      }
      return true;
    }

    bool IpoptSolver::ClothoidSplineProblem::eval_f(
        Index theta_size, const Number * theta, bool new_theta, Number & obj_value) {
      if (theta_size != m_solver.theta_size())
        return false;
      return m_solver.spline().objective(theta, obj_value);
    }

    bool IpoptSolver::ClothoidSplineProblem::eval_grad_f(
        Index theta_size, const Number * theta, bool new_theta, Number * grad_f) {
      if (theta_size != m_solver.theta_size())
        return false;
      return m_solver.spline().gradient(theta, grad_f);
    }

    bool IpoptSolver::ClothoidSplineProblem::eval_g(
        Index theta_size, const Number * theta, bool new_theta, Index constraints_size, Number * g) {
      if (theta_size != m_solver.theta_size())
        return false;
      if (constraints_size != m_solver.constraints_size())
        return false;
      return m_solver.spline().constraints(theta, g);
    }

    bool IpoptSolver::ClothoidSplineProblem::eval_jac_g(
        Index          theta_size,
        const Number * theta,
        bool           new_theta,
        Index          constraints_size,
        Index          jacobian_pattern_size,
        Index *        jacobian_rows,
        Index *        jacobian_cols,
        Number *       jacobian_values) {
      if (theta_size != m_solver.theta_size())
        return false;
      if (constraints_size != m_solver.constraints_size())
        return false;
      if (jacobian_pattern_size != m_solver.jacobian_pattern_size())
        return false;

      bool index_ok = true;
      if ((jacobian_rows != NULL) && (jacobian_cols != NULL)) {
        index_ok = m_solver.spline().jacobian_pattern(jacobian_rows, jacobian_cols);
      }

      bool jac_eval_ok = true;
      if (jacobian_values != NULL) {
        jac_eval_ok = m_solver.spline().jacobian(theta, jacobian_values);
      }

      return index_ok & jac_eval_ok;
    }

    void IpoptSolver::ClothoidSplineProblem::finalize_solution(
        SolverReturn                       status,
        Index                              theta_size,
        const Number *                     theta,
        const Number *                     z_L,
        const Number *                     z_U,
        Index                              constraints_size,
        const Number *                     g,
        const Number *                     lambda,
        Number                             obj_value,
        const Ipopt::IpoptData *           ip_data,
        Ipopt::IpoptCalculatedQuantities * ip_cq) {
      m_solver_return = status;
      std::copy(theta, theta + theta_size, m_solver.theta_solution().begin());
    }

    Result IpoptSolver::solve() {
      SmartPtr<IpoptSolver::ClothoidSplineProblem> spline_problem = new IpoptSolver::ClothoidSplineProblem(*this);
      SmartPtr<IpoptApplication>                   app            = IpoptApplicationFactory();

      app->Options()->SetStringValue("jac_d_constant", "no");
      app->Options()->SetStringValue("hessian_constant", "no");
      app->Options()->SetStringValue("mu_strategy", "adaptive");
      app->Options()->SetStringValue("derivative_test", "none");
      app->Options()->SetStringValue("hessian_approximation", "limited-memory");
      app->Options()->SetStringValue("limited_memory_update_type", "bfgs");

      app->Options()->SetIntegerValue("max_iter", 400);

      app->Options()->SetNumericValue("tol", 1e-10);
      app->Options()->SetNumericValue("derivative_test_tol", 1e-5);

      // Disable all output
      app->Options()->SetIntegerValue("print_level", 0);
      app->Options()->SetStringValue("sb", "yes");

      ApplicationReturnStatus status = app->Initialize();
      if (status != ApplicationReturnStatus::Solve_Succeeded) {
        return Result(ResultType::InvalidInput);
      }

      status = app->OptimizeTNLP(spline_problem);
      const auto stats = app->Statistics();
      switch (status) {
        case (ApplicationReturnStatus::Solve_Succeeded):
        case (ApplicationReturnStatus::Solved_To_Acceptable_Level):
          return Result(ResultType::Success, stats->FinalObjective(), stats->IterationCount());
          break;
        case (ApplicationReturnStatus::Infeasible_Problem_Detected):
        case (ApplicationReturnStatus::Feasible_Point_Found):
          return Result(ResultType::NumericalIssue, stats->FinalObjective(), stats->IterationCount());
          break;
        case (ApplicationReturnStatus::Search_Direction_Becomes_Too_Small):
        case (ApplicationReturnStatus::Diverging_Iterates):
        case (ApplicationReturnStatus::User_Requested_Stop):
        case (ApplicationReturnStatus::Maximum_Iterations_Exceeded):
          return Result(ResultType::NoConvergence, stats->FinalObjective(), stats->IterationCount());
          break;
        case (ApplicationReturnStatus::Error_In_Step_Computation):
        case (ApplicationReturnStatus::Restoration_Failed):
        case (ApplicationReturnStatus::Maximum_CpuTime_Exceeded):
        case (ApplicationReturnStatus::Not_Enough_Degrees_Of_Freedom):
        case (ApplicationReturnStatus::Invalid_Number_Detected):
        case (ApplicationReturnStatus::Invalid_Option):
        case (ApplicationReturnStatus::Unrecoverable_Exception):
        case (ApplicationReturnStatus::NonIpopt_Exception_Thrown):
        case (ApplicationReturnStatus::Insufficient_Memory):
        case (ApplicationReturnStatus::Internal_Error):
          return Result(ResultType::InternalError, stats->FinalObjective(), stats->IterationCount());
          break;
        case (ApplicationReturnStatus::Invalid_Problem_Definition):
          return Result(ResultType::InvalidInput, stats->FinalObjective(), stats->IterationCount());
          break;
      }
      return Result(ResultType::InternalError);
    }

    Result Interpolator::buildP4(ClothoidList & result) {
      m_spline.setP4();
      build_clothoid_spline();
      IpoptSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

    Result Interpolator::buildP5(ClothoidList & result) {
      m_spline.setP5();
      build_clothoid_spline();
      IpoptSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

    Result Interpolator::buildP6(ClothoidList & result) {
      m_spline.setP6();
      build_clothoid_spline();
      IpoptSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

    Result Interpolator::buildP7(ClothoidList & result) {
      m_spline.setP7();
      build_clothoid_spline();
      IpoptSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

    Result Interpolator::buildP8(ClothoidList & result) {
      m_spline.setP8();
      build_clothoid_spline();
      IpoptSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

    Result Interpolator::buildP9(ClothoidList & result) {
      m_spline.setP9();
      build_clothoid_spline();
      IpoptSolver solver(m_spline);
      solver.guess();
      auto status = solver.solve();
      build_clothoid_list(solver.theta_solution(), result);
      return status;
    }

  } /* namespace Interpolation */
} /* namespace G2lib */

#endif