/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file Constants.hxx
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
#include <utility>
#include <map>
#include "Types.hxx"

namespace G2lib {
  typedef enum {
    G2LIB_LINE = 0,
    G2LIB_POLYLINE,
    G2LIB_CIRCLE,
    G2LIB_BIARC,
    G2LIB_BIARC_LIST,
    G2LIB_CLOTHOID,
    G2LIB_CLOTHOID_LIST
  } CurveType;

  #ifndef DOXYGEN_SHOULD_SKIP_THIS

  using Ppair = std::pair<CurveType, CurveType>;

  // check if compiler is C++11
  static std::map<Ppair, CurveType> const promote_map = {
    { Ppair(G2LIB_LINE, G2LIB_LINE), G2LIB_LINE },
    { Ppair(G2LIB_LINE, G2LIB_CIRCLE), G2LIB_CIRCLE },
    { Ppair(G2LIB_LINE, G2LIB_CLOTHOID), G2LIB_CLOTHOID },
    { Ppair(G2LIB_LINE, G2LIB_BIARC), G2LIB_BIARC_LIST },
    { Ppair(G2LIB_LINE, G2LIB_BIARC_LIST), G2LIB_BIARC_LIST },
    { Ppair(G2LIB_LINE, G2LIB_CLOTHOID_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_LINE, G2LIB_POLYLINE), G2LIB_POLYLINE },

    { Ppair(G2LIB_CIRCLE, G2LIB_LINE), G2LIB_CIRCLE },
    { Ppair(G2LIB_CIRCLE, G2LIB_CIRCLE), G2LIB_CIRCLE },
    { Ppair(G2LIB_CIRCLE, G2LIB_CLOTHOID), G2LIB_CLOTHOID },
    { Ppair(G2LIB_CIRCLE, G2LIB_BIARC), G2LIB_BIARC_LIST },
    { Ppair(G2LIB_CIRCLE, G2LIB_BIARC_LIST), G2LIB_BIARC_LIST },
    { Ppair(G2LIB_CIRCLE, G2LIB_CLOTHOID_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CIRCLE, G2LIB_POLYLINE), G2LIB_CLOTHOID_LIST },

    { Ppair(G2LIB_BIARC, G2LIB_LINE), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_BIARC, G2LIB_CIRCLE), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_BIARC, G2LIB_CLOTHOID), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_BIARC, G2LIB_BIARC), G2LIB_BIARC },
    { Ppair(G2LIB_BIARC, G2LIB_BIARC_LIST), G2LIB_BIARC_LIST },
    { Ppair(G2LIB_BIARC, G2LIB_CLOTHOID_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_BIARC, G2LIB_POLYLINE), G2LIB_CLOTHOID_LIST },

    { Ppair(G2LIB_CLOTHOID, G2LIB_LINE), G2LIB_CLOTHOID },
    { Ppair(G2LIB_CLOTHOID, G2LIB_CIRCLE), G2LIB_CLOTHOID },
    { Ppair(G2LIB_CLOTHOID, G2LIB_CLOTHOID), G2LIB_CLOTHOID },
    { Ppair(G2LIB_CLOTHOID, G2LIB_BIARC), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID, G2LIB_BIARC_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID, G2LIB_CLOTHOID_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID, G2LIB_POLYLINE), G2LIB_CLOTHOID_LIST },

    { Ppair(G2LIB_CLOTHOID_LIST, G2LIB_LINE), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID_LIST, G2LIB_CIRCLE), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID_LIST, G2LIB_CLOTHOID), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID_LIST, G2LIB_BIARC), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID_LIST, G2LIB_BIARC_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID_LIST, G2LIB_CLOTHOID_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_CLOTHOID_LIST, G2LIB_POLYLINE), G2LIB_CLOTHOID_LIST },

    { Ppair(G2LIB_POLYLINE, G2LIB_LINE), G2LIB_POLYLINE },
    { Ppair(G2LIB_POLYLINE, G2LIB_CIRCLE), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_POLYLINE, G2LIB_CLOTHOID), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_POLYLINE, G2LIB_BIARC), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_POLYLINE, G2LIB_BIARC_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_POLYLINE, G2LIB_CLOTHOID_LIST), G2LIB_CLOTHOID_LIST },
    { Ppair(G2LIB_POLYLINE, G2LIB_POLYLINE), G2LIB_POLYLINE }
  };

#endif

  namespace Utils {
    extern const real_type m_pi;
    extern const real_type m_2pi;
    extern const real_type m_pi_2;
    extern const real_type m_1_pi;
    extern const real_type m_1_sqrt_pi;
    extern const real_type machepsi;
    extern const real_type machepsi10;
    extern const real_type machepsi100;
    extern const real_type machepsi1000;
    extern const real_type sqrtMachepsi;
  }  // namespace Utils
}  // namespace G2lib
