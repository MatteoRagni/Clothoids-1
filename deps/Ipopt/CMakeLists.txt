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

find_package(PkgConfig REQUIRED)

project(Ipopt)

if(WIN32)
  message(FATAL_ERROR "Ipopt option not available on Windows")
endif()

pkg_check_modules(Ipopt REQUIRED IMPORTED_TARGET ipopt GLOBAL)
add_library(Ipopt::Ipopt ALIAS PkgConfig::Ipopt)

# if (ipopt_FOUND)
#   add_library(${PROJECT_NAME} SHARED IMPORTED)
#   target_compile_definitions(${PROJECT_NAME} INTERFACE G2LIB_IPOPT_CLOTHOID_SPLINE)
#   target_include_directories(${PROJECT_NAME} INTERFACE ${ipopt_INCLUDE_DIRS})
#   target_link_libraries(${PROJECT_NAME} INTERFACE ${ipopt_LIBRARIES})
#   target_compile_definitions(${PROJECT_NAME} INTERFACE HAVE_CSTDDEF)
# else()
#   message(FATAL_ERROR "IPOPT development library not found")
# endif()