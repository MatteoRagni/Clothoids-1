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

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)

project(Eigen)

find_package(Eigen3 3.3 NO_MODULE)
if (NOT Eigen3_FOUND)
  message(STATUS "Eigen3 not found, downloading from repository")
  FetchContent_Declare(Eigen3
    URL https://gitlab.com/libeigen/eigen/-/archive/3.3.9/eigen-3.3.9.zip)
  FetchContent_MakeAvailable(Eigen3)
endif()

add_library(ClothoidsEigen3 INTERFACE IMPORTED GLOBAL)
target_link_libraries(ClothoidsEigen3 INTERFACE Eigen3::Eigen)
add_library(Clothoids::Eigen3 ALIAS ClothoidsEigen3)