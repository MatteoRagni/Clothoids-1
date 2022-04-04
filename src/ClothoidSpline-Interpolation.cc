/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file ClothoidSpline-Interpolation.cc
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

#include "Clothoids/ClothoidSpline-Interpolation.hxx"

#ifdef min
#undef min
#endif
#ifdef max
#undef max
#endif

#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace G2lib {
  namespace Interpolation {

    void Interpolator::build_clothoid_spline() {
      check_input();
      m_spline.build(xs().data(), ys().data(), xs().size());
    }

    void Interpolator::check_input() {
      /* Check equal size for input */
      if (xs().size() != ys().size()) {
        throw std::runtime_error("Input vectors must be of same length");
      }

      /* Check enough input */
      if (xs().size() < 2) {
        throw std::runtime_error("Input size too small");
      }

      const int_type         size = xs().size();
      std::vector<real_type> chk;
      for (int_type i = 1; i < size; i++) {
        const real_type x_diff2 = std::pow(xs()[i] - xs()[i - 1], 2);
        const real_type y_diff2 = std::pow(ys()[i] - ys()[i - 1], 2);
        chk.push_back(x_diff2 + y_diff2);
      }
      const auto min_chk = std::min_element(chk.begin(), chk.end());
      const auto max_chk = std::max_element(chk.begin(), chk.end());
      if (*min_chk == 0) {
        throw std::runtime_error("Minimal distance too short");
      }
      if (*min_chk < (1e-10 * *max_chk)) {
        throw std::runtime_error("Problem with too much deviation");
      }
    }

    void Interpolator::build_clothoid_list(const std::vector<real_type> & theta, ClothoidList & result) {
      if (theta.size() < 2) {
        throw std::runtime_error("Result has only two values??");
      }
      result.init();
      result.reserve(theta.size() - 1);
      for (int_type i = 0; i < static_cast<int_type>(theta.size()) - 1; i++)
        result.push_back_G1(xs()[i], ys()[i], theta[i], xs()[i + 1], ys()[i + 1], theta[i + 1]);
    }

#ifndef G2LIB_LMSOLVE_CLOTHOID_SPLINE
    Result Interpolator::buildP1(real_type theta_0, real_type theta_1, ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with libeigen3-dev library installed!");
    }

    Result Interpolator::buildP2(ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with libeigen3-dev library installed!");
    }
#endif

#ifndef G2LIB_IPOPT_CLOTHOID_SPLINE
    Result Interpolator::buildP4(ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with lipipopt-dev library installed!");
    }

    Result Interpolator::buildP5(ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with lipipopt-dev library installed!");
    }

    Result Interpolator::buildP6(ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with lipipopt-dev library installed!");
    }

    Result Interpolator::buildP7(ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with lipipopt-dev library installed!");
    }

    Result Interpolator::buildP8(ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with lipipopt-dev library installed!");
    }

    Result Interpolator::buildP9(ClothoidList & result) {
      throw std::runtime_error("Not supported. Recompile with lipipopt-dev library installed!");
    }
#endif

    Solver::Solver(const ClothoidSplineG2 & spline)
        : m_spline(spline), m_theta_size(spline.numTheta()), m_constraints_size(spline.numConstraints()),
          m_jacobian_pattern_size(spline.jacobian_nnz()),
          m_theta_solution(std::vector<real_type>(spline.numTheta(), 0.0)),
          m_theta_min(std::vector<real_type>(spline.numTheta(), 0.0)),
          m_theta_max(std::vector<real_type>(spline.numTheta(), 0.0)) {
      m_jacobian_size           = theta_size() * constraints_size();
      m_lagrangian_hessian_size = (theta_size() + constraints_size()) * (theta_size() + constraints_size());
    }

    void Solver::guess() { m_spline.guess(&m_theta_solution.front(), &m_theta_min.front(), &m_theta_max.front()); }

  } /* namespace Interpolation */
} /* namespace G2lib */
