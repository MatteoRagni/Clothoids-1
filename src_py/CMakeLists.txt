# Copyright (c) 2022 Matteo Ragni
# 
#   Based on the work of Enrico Bertolazzi
#   http://ebertolazzi.github.io/Clothoids/
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
cmake_minimum_required(VERSION 3.14)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" PY_CLOTHOIDS_VERSION)

project(G2lib VERSION ${PY_CLOTHOIDS_VERSION})

add_subdirectory(.. Clothoids)
add_subdirectory(deps/pybind11)

set(G2LIB_SOURCES
	"src/python-Triangle2D.cc"
	"src/python-LineSegment.cc"
	"src/python-G2lib.cc"
	"src/python-Clothoid.cc"
	"src/python-CircleArc.cc"
	"src/python-Biarc.cc"
	"src/python-BaseCurve.cc"
	"src/python-AABBtree.cc")

set(G2LIB_INTERPOLATION_SOURCES
  "src/python-Interpolation.cc"
  "src/python-G2lib-Interpolation.cc")

pybind11_add_module(_G2lib MODULE ${G2LIB_SOURCES})
target_include_directories(_G2lib 
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(_G2lib PRIVATE cxx_std_14)
target_link_libraries(_G2lib PRIVATE Clothoids::Static)
set_target_properties(_G2lib PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib")
if(MSVC)
  set_target_properties(_G2lib PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib")
endif()

pybind11_add_module(_G2lib_Interpolation MODULE ${G2LIB_INTERPOLATION_SOURCES})
target_include_directories(_G2lib_Interpolation 
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(_G2lib_Interpolation PRIVATE cxx_std_14)
target_link_libraries(_G2lib_Interpolation PRIVATE Clothoids::Static)
set_target_properties(_G2lib_Interpolation PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib")
if(MSVC)
  set_target_properties(_G2lib_Interpolation PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
    LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/distrib/G2lib/G2lib")
endif()
