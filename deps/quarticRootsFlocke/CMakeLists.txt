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

project(quarticRootsFlocke)

set(EB_QUARTIC_ROOTS_FLOCKE_GIT_REPOSITORY 
  "https://github.com/ebertolazzi/quarticRootsFlocke.git"
  CACHE STRING "Sets the origin for the quarticRootsFlocke repository")
# Currently set to master as for 16.03.2022. We will set it to a tag when 
# a working version will be tagged
set(EB_QUARTIC_ROOTS_FLOCKE_GIT_TAG 
  "c789b60d046575ddfc83e4794ad0ca4c3bd4830c"
  CACHE STRING "Sets the checkout point for quarticRootsFlocke. Can be a SHA or a git tag")
set(EB_QUARTIC_ROOTS_FLOCKE_SEARCH_DIR
  "${CMAKE_CURRENT_SOURCE_DIR}/../../quarticRootsFlocke/lib"
  CACHE STRING "Search directory for a local installation of quarticRootsFlocke. Optional")

# Dependency Options, available only for Fetched Content, not 
# for local installation
set(EB_GIT_VERSION OFF)
set(EB_ENABLE_TESTS OFF)
set(EB_BUILD_SHARED OFF)
set(EB_INSTALL_LOCAL OFF)

FetchContent_Declare(
  quarticRootsFlocke
  GIT_REPOSITORY ${EB_QUARTIC_ROOTS_FLOCKE_GIT_REPOSITORY}
  GIT_TAG ${EB_QUARTIC_ROOTS_FLOCKE_GIT_TAG})
FetchContent_MakeAvailable(quarticRootsFlocke)
