/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file Types.hxx
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

#include <istream>
#include <ostream>
#include <cmath>

#ifndef G2LIB_DEFAULT_REAL_TYPE
#define G2LIB_DEFAULT_REAL_TYPE double
#endif

#ifndef G2LIB_DEFAULT_INT_TYPE
#define G2LIB_DEFAULT_INT_TYPE int
#endif

#ifndef G2LIB_DEFAULT_OSTREAM_TYPE
#define G2LIB_DEFAULT_OSTREAM_TYPE std::basic_ostream<char>
#endif

#ifndef G2LIB_DEFAULT_ISTREAM_TYPE
#define G2LIB_DEFAULT_ISTREAM_TYPE std::basic_istream<char>
#endif

namespace G2lib {
  using std::sin;
  using std::cos;
  using std::atan2;
  using std::hypot;

  typedef G2LIB_DEFAULT_OSTREAM_TYPE ostream_type;
  typedef G2LIB_DEFAULT_ISTREAM_TYPE istream_type;
  typedef G2LIB_DEFAULT_REAL_TYPE    real_type;
  typedef G2LIB_DEFAULT_INT_TYPE     int_type;
}  // namespace G2lib
