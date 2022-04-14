/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file ThreadLocalData.hxx
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
#include <map>
#include <thread>
#include <mutex>

namespace G2lib {
  namespace Utils {

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
          auto data_ptr = std::make_shared<Data>(Data());
          m_data[id]    = data_ptr;
          return data_ptr;
        } else {
          return el->second;
        }
      }
    };
  }  // namespace Utils
}  // namespace G2lib