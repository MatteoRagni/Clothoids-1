# Copyright (c) 2022 Matteo Ragni
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

cmake_minimum_required(VERSION 3.14)
project(fmt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

# Options
set(FMT_DOC OFF)
set(FMT_INSTALL OFF)
set(FMT_TEST OFF)

set(CLOTHOIDS_FMT_VERSION "8.1.1" CACHE STRING "libfmt Version to use")
set(CLOTHOIDS_FMT_DOWNLOAD_URL "https://github.com/fmtlib/fmt/releases/download/${CLOTHOIDS_FMT_VERSION}/fmt-${CLOTHOIDS_FMT_VERSION}.zip"
  CACHE STRING "Download URL for libfmt library")

FetchContent_Declare(fmt URL ${CLOTHOIDS_FMT_DOWNLOAD_URL})
FetchContent_MakeAvailable(fmt)