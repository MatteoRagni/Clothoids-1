/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file Constants.cc
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
#include <cmath>
#include <limits>
#include "Clothoids/Constants.hxx"

namespace G2lib {
  namespace Utils {
    const real_type m_pi         = M_PI;
    const real_type m_2pi        = m_pi * 2;
    const real_type m_pi_2       = M_PI_2;
    const real_type m_1_pi       = M_1_PI;
    const real_type m_1_sqrt_pi  = 0.564189583547756286948079451561;  // 1/sqrt(pi)
    const real_type machepsi     = std::numeric_limits<real_type>::epsilon();
    const real_type machepsi10   = 10 * machepsi;
    const real_type machepsi100  = 100 * machepsi;
    const real_type machepsi1000 = 1000 * machepsi;
    const real_type     sqrtMachepsi = std::sqrt(machepsi);
  }  // namespace Utils
}  // namespace G2lib
