/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file ClothoidSpline-Interpolation.hh
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

#pragma once

#include <stdexcept>

#include "Types.hxx"
#include "ClothoidList.hxx"

namespace G2lib {
  namespace Interpolation {
    using G2lib::int_type;
    using G2lib::real_type;

    using G2lib::ClothoidList;
    using G2lib::ClothoidSplineG2;

    enum class ResultType {
      Success = 0,
      NumericalIssue = 1,
      NoConvergence = 2,
      InvalidInput = 3,
      InternalError = 4
    };

    class Result {
      ResultType m_status;
      real_type m_fnorm;
      int_type m_iters;

      public:
      Result() : m_status(ResultType::InternalError), m_fnorm(0.0), m_iters(0) {}
      Result(ResultType status, real_type fnorm = 0.0, int_type iters = 0) :
        m_status(status), m_fnorm(fnorm), m_iters(iters) {}

      bool ok() const { return m_status == ResultType::Success; }
      const ResultType & status() const { return m_status; }
      const real_type & objective_value() const { return m_fnorm; }
      const int_type & iters() const { return m_iters; }
    };

    /**
     * @brief User Entrypoint for interpolation problems
     */
    class Interpolator {
      const std::vector<real_type> m_xs;
      const std::vector<real_type> m_ys;
      ClothoidSplineG2             m_spline;

     public:
      Interpolator(const std::vector<real_type> & xs, const std::vector<real_type> & ys)
          : m_xs(xs), m_ys(ys), m_spline() {}

      Result buildP1(real_type theta_0, real_type theta_1, ClothoidList & result);
      Result buildP2(ClothoidList & result);
      Result buildP4(ClothoidList & result);
      Result buildP5(ClothoidList & result);
      Result buildP6(ClothoidList & result);
      Result buildP7(ClothoidList & result);
      Result buildP8(ClothoidList & result);
      Result buildP9(ClothoidList & result);

      const std::vector<real_type> & xs() const { return m_xs; }
      const std::vector<real_type> & ys() const { return m_ys; }

     private:
      void build_clothoid_spline();
      void check_input();
      void build_clothoid_list(const std::vector<real_type> & theta, ClothoidList & result);
    };

    /**
     * @brief Solver class, it is a base for the actual solvers to be implemented
     * 
     * This class will incapsulate actual solvers such as:
     *  
     *  * Levenberg Marquardt solver from eigen3
     *  * Interior point solver from coinor-ipopt
     */
    class Solver {
     private:
      const ClothoidSplineG2 & m_spline;
      int_type                 m_theta_size;
      int_type                 m_constraints_size;
      int_type                 m_jacobian_pattern_size;
      int_type                 m_jacobian_size;
      int_type                 m_lagrangian_hessian_size;
      std::vector<real_type>   m_theta_solution;
      std::vector<real_type>   m_theta_min;
      std::vector<real_type>   m_theta_max;

     public:
      Solver(const ClothoidSplineG2 & spline);

      void guess();

      virtual Result solve() = 0;

      int theta_size() const { return m_theta_size; }
      int constraints_size() const { return m_constraints_size; }
      int jacobian_pattern_size() const { return m_jacobian_pattern_size; }
      int jacobian_size() const { return m_jacobian_size; }
      int lagrangian_hessian_size() const { return m_lagrangian_hessian_size; }

      const ClothoidSplineG2 &       spline() { return m_spline; }
      std::vector<real_type> &       theta_solution() { return m_theta_solution; }
      const std::vector<real_type> & theta_min() const { return m_theta_min; }
      const std::vector<real_type> & theta_max() const { return m_theta_max; }
    };

  }  // namespace Interpolation
} /* namespace G2lib */