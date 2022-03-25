#pragma once
#include <map>
#include <algorithm>
#include <thread>
#include <mutex>

#include "fmt/ostream.h"
#include "fmt/core.h"

#ifndef G2LIB_UTILS_ERROR0
#define G2LIB_UTILS_ERROR0(MSG) throw std::runtime_error(MSG);
#endif

#ifndef G2LIB_UTILS_ASSERT0
#define G2LIB_UTILS_ASSERT0(COND, MSG)                                                                                 \
  if (!(COND)) {                                                                                                       \
    G2LIB_UTILS_ERROR0(MSG)                                                                                            \
  }
#endif

#ifndef G2LIB_UTILS_ERROR
#define G2LIB_UTILS_ERROR(...) throw std::runtime_error(fmt::format(__VA_ARGS__));
#endif

#ifndef G2LIB_UTILS_ASSERT
#define G2LIB_UTILS_ASSERT(COND, ...)                                                                                  \
  if (!(COND)) {                                                                                                       \
    G2LIB_UTILS_ERROR(__VA_ARGS__)                                                                                     \
  }
#endif

namespace G2lib {
  namespace Utils {

    static inline bool isZero(double x) { return FP_ZERO == std::fpclassify(x); }

    static inline bool isRegular(double x) { return !(FP_INFINITE == std::fpclassify(x) || FP_NAN == std::fpclassify(x)); }

    template<typename Data> class ThreadLocalData {
     public:
      using DataPtr = std::shared_ptr<Data>;

     private:
      mutable std::mutex                 m_data_mutex;
      std::map<std::thread::id, DataPtr> m_data;

     public:
      ThreadLocalData() {}

      ThreadLocalData(const ThreadLocalData<Data> & other) { *this = other; }

      ThreadLocalData(ThreadLocalData<Data> && other) { *this = other; }

      ~ThreadLocalData() {
        std::lock_guard<std::mutex> l(m_data_mutex);
        m_data.clear();
      }

      ThreadLocalData & operator=(const ThreadLocalData & other) {
        std::lock_guard<std::mutex> l1(m_data_mutex);
        std::lock_guard<std::mutex> l2(other.m_data_mutex);
        m_data = other.m_data;
        return *this;
      }

      ThreadLocalData & operator=(ThreadLocalData && other) {
        std::lock_guard<std::mutex> l1(m_data_mutex);
        std::lock_guard<std::mutex> l2(other.m_data_mutex);
        m_data = other.m_data;
        return *this;
      }

      DataPtr search(const std::thread::id & id) {
        std::lock_guard<std::mutex> l(m_data_mutex);
        auto                        el = m_data.find(id);
        if (el == m_data.end()) {
          auto data_ptr = std::make_shared<Data>();
          m_data[id]    = data_ptr;
          return data_ptr;
        } else {
          return el->second;
        }
      }
    };

    template<typename T_int, typename T_real>
    void search_interval(
        T_int npts, T_real const * X, T_real & x, std::shared_ptr<T_int> lastInterval, bool closed, bool can_extend) {
      int & lastInterval_ = *lastInterval;
      search_interval<T_int, T_real>(npts, X, x, lastInterval, closed, can_extend);
    }

    template<typename T_int, typename T_real>
    void search_interval(T_int npts, T_real const * X, T_real & x, T_int & lastInterval, bool closed, bool can_extend) {
      // For this implementation we must ensure a number of points greater than 1 (there
      // must be at least one interval). The number of intervals is npts - 2. The last
      // point is in n = npts - 1;
      const T_int n = npts - 1;
      G2LIB_UTILS_ASSERT(
          npts > 1 && lastInterval >= 0 && lastInterval < n,
          "In search_interval( npts={}, X, x={}, lastInterval={}, closed={}, can_extend={})\n"
          "npts musrt be >= 2 and lastInterval must be in [0,npts-2]\n",
          npts, lastInterval, closed, can_extend);

      // Handles the "closed" search, by limiting the value of x for the search inside the
      // limit of [X[0], X[n]]. This function will use fmod for detecting multiple "loops".
      // This part will modify the value of x. If the curve is not closed, the search can
      // be extended beyond the lomots only with the can_extend flag. Otherwise x must
      // be inside the limits of the X
      const T_real xl = X[0];
      const T_real xr = X[n];
      if (closed) {
        T_real L = xr - xl;
        x -= xl;                 // relative to xl
        x = fmod(x, L);          // remove loops
        x += (x < 0 ? L : 0.0);  // handling negative rotations
        x += xl;                 // relatie to 0 again
      } else {
        G2LIB_UTILS_ASSERT(
            can_extend || (x >= xl && x <= xr),
            "In search_interval( npts={}, X, x={}, lastInterval={}, closed={}, can_extend={})\n"
            "out of range: [{},{}]\n",
            npts, lastInterval, closed, can_extend, xl, xr);
      }

      // Find the interval of the support of the B-spline, using lastInterval as an hot start
      T_real const * XL = X + lastInterval;

      // We must consider 3 possible scenario:
      // 1. the searched point lies on the right of the current interval
      // 2. the searched point lies on the left of the current interval
      // 3. the searched point lies on the current interval. In this case there is nothing to do
      if (XL[1] < x) /* situation 1. */ {
        // We considers three situations in order to maximize performances:
        // 1.1: the point is beyond the second to last point. The valid interval is the last one (n - 1)
        // 1.2: the point is in the very next interval
        // 1.3: we must search the interval of the point in the intervals next to the current one, up to last
        if (x >= X[n - 1]) {
          lastInterval = n - 1;
        } else if (x < XL[2]) {
          ++lastInterval;
        } else {
          T_real const * XE = X + n;
          lastInterval += T_int(std::lower_bound(XL, XE, x) - XL);
          T_real const * XX = X + lastInterval;
          if (x < XX[0] || isZero(XX[0] - XX[1]))
            --lastInterval;
        }
      } else if (x < XL[0]) /* situation 2. */ {
        // We considers three situations in order to maximize performances:
        // 1.1: the point is beyond the second point. The valid interval is the first (0)
        // 1.2: the point is in the very next interval
        // 1.3: we must search the interval of the point in the intervals next to the current one, up to first
        if (x <= X[1]) {
          lastInterval = 0;
        } else if (XL[-1] <= x) {
          --lastInterval;
        } else {
          lastInterval      = T_int(lower_bound(X + 1, XL, x) - X);
          T_real const * XX = X + lastInterval;
          if (x < XX[0] || isZero(XX[0] - XX[1]))
            --lastInterval;
        }
      } /* situation 3: Do nothing. */
      // Check the computed interval
      G2LIB_UTILS_ASSERT(
          lastInterval >= 0 && lastInterval < n,
          "In search_interval( npts={}, X, x={}, lastInterval={}, closed={}, can_extend={})\n"
          "computed lastInterval of range: [{},{}]\n",
          npts, lastInterval, closed, can_extend, xl, xr);
    }

  }  // namespace Utils
}  // namespace G2lib