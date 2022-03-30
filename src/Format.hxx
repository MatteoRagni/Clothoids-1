/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file Format.hxx
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
 *
 * Based on the work of:
 * Enrico Bertolazzi
 *  - http://ebertolazzi.github.io/Clothoids/
 *  - http://ebertolazzi.github.io/Utils/
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include <string>
#include <cstdio>
#include <algorithm>
#include <iostream>

#ifdef min
#undef min
#endif

#ifndef G2LIB_FORMAT_BUFFER_SIZE
#define G2LIB_FORMAT_BUFFER_SIZE 4096
#endif

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
#define G2LIB_UTILS_ERROR(...) throw std::runtime_error(G2lib::Utils::format_string(__VA_ARGS__));
#endif

#ifndef G2LIB_UTILS_ASSERT
#define G2LIB_UTILS_ASSERT(COND, ...)                                                                                  \
  if (!(COND)) {                                                                                                       \
    G2LIB_UTILS_ERROR(__VA_ARGS__)                                                                                     \
  }
#endif

namespace G2lib {
  namespace Utils {
    static constexpr size_t _format_buffer_size = G2LIB_FORMAT_BUFFER_SIZE;

    // Formatting Utilities
    inline std::string format_string(const std::string & format) {
      return std::string(format);
    }

    template <typename... Ts>
    inline std::string format_string(const std::string & format, const Ts &... inputs) {
      std::string output(std::max(_format_buffer_size, 2 * format.size()), '\0');
      std::snprintf(&output.front(), output.size(), format.data(), inputs...);
      return output;
    }

    // Printing Utilities
    inline void print_string(const std::string & format) {
      std::cout << format << std::endl;
    }

    template <typename... Ts>
    inline void print_string(const std::string & format, const Ts &... others) {
      std::cout << format_string(format, others...) << std::endl;
    }
  }  // namespace Utils
}  // namespace G2lib