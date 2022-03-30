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

project(PolynomialRoots)

set(POLYNOMIAL_ROOTS_FLOCKE_GIT_REPOSITORY 
  "https://github.com/MatteoRagni/quarticRootsFlocke.git"
  CACHE STRING "Sets the origin for the Polynomial Roots repository")
set(POLYNOMIAL_ROOTS_FLOCKE_GIT_TAG 
  "v3.0.0"
  CACHE STRING "Sets the checkout point for Polynomial Roots. Can be a SHA or a git tag")

# Dependency Options
set(POLYNOMIAL_ROOTS_BUILD_SHARED OFF)

FetchContent_Declare(
  PolynomialRoots
  GIT_REPOSITORY ${POLYNOMIAL_ROOTS_FLOCKE_GIT_REPOSITORY}
  GIT_TAG ${POLYNOMIAL_ROOTS_FLOCKE_GIT_TAG})
FetchContent_MakeAvailable(PolynomialRoots)
