##
# PYTHON Wrapper for Clothoids
#
# License MIT - See LICENSE file
# 2019 Matteo Ragni, Claudio Kerov Ghiglianovich,
#      Enrico Bertolazzi, Marco Frego
#

cmake_minimum_required(VERSION 3.10.2)

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

pybind11_add_module(G2lib MODULE ${G2LIB_SOURCES})

target_include_directories(G2lib 
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_features(G2lib PRIVATE cxx_std_14)
target_link_libraries(G2lib PRIVATE Clothoids::Static)

# set(INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../lib/lib)
# install(TARGETS G2lib DESTINATION ${INSTALL_PREFIX})
