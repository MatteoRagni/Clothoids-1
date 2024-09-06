# Copyright (c) 2020, Matteo Ragni
# All rights reserved.
# 
#   Based on the work of Enrico Bertolazzi
#   http://ebertolazzi.github.io/Clothoids/
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
# 
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the distribution
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(READ "${CMAKE_CURRENT_SOURCE_DIR}/VERSION" CLOTHOIDS_VERSION)

project(
  Clothoids
  VERSION ${CLOTHOIDS_VERSION}
  HOMEPAGE_URL "https://github.com/MatteoRagni/Clothoids-1")

option(CLOTHOIDS_BUILD_SHARED "Build dynamic library" OFF)
option(CLOTHOIDS_ENABLE_EIGEN_SOLVER "Enable buildP1 and buildP2 interpolator functions" OFF)
option(CLOTHOIDS_ENABLE_IPOPT_SOLVER 
  "Enable buildP4, buildP5, buildP6, buildP7, buildP8 and buildP9 interpolator functions" OFF)

add_subdirectory(./deps/PolynomialRoots)
if(CLOTHOIDS_ENABLE_IPOPT_SOLVER)
add_subdirectory(./deps/Ipopt)
endif()
if(CLOTHOIDS_ENABLE_EIGEN_SOLVER)
add_subdirectory(./deps/Eigen3)
endif()
#   ___
#  / __| ___ _  _ _ _ __ ___ ___
#  \__ \/ _ \ || | '_/ _/ -_|_-<
#  |___/\___/\_,_|_| \__\___/__/
#
set(CLOTHOIDS_SRCS
  Utils.hxx
  Format.hxx
  Constants.cc
  AABBtree.cc
  Biarc.cc
  BiarcList.cc
  Circle.cc
  Clothoid.cc
  ClothoidDistance.cc
  ClothoidG2.cc
  ClothoidList.cc
  Fresnel.cc
  G2lib_intersect.cc
  G2lib.cc
  Line.cc
  PolyLine.cc
  Triangle2D.cc
  ClothoidSpline-Interpolation.cc)

if(CLOTHOIDS_ENABLE_EIGEN_SOLVER)
set(CLOTHOIDS_SRCS ${CLOTHOIDS_SRCS}
  ClothoidSpline-LMSolver.cc)
endif()

if(CLOTHOIDS_ENABLE_IPOPT_SOLVER)
set(CLOTHOIDS_SRCS ${CLOTHOIDS_SRCS}
  ClothoidSpline-IpoptSolver.cc)
endif()

set(CLOTHOIDS_HDRS
  Clothoids/AABBtree.hxx
  Clothoids/BaseCurve_using.hxx
  Clothoids/BaseCurve.hxx
  Clothoids/Biarc.hxx
  Clothoids/BiarcList.hxx
  Clothoids/Circle.hxx
  Clothoids/Clothoid.hxx
  Clothoids/ClothoidList.hxx
  Clothoids/Constants.hxx
  Clothoids/Fresnel.hxx
  Clothoids/G2lib.hxx
  Clothoids/Line.hxx
  Clothoids/PolyLine.hxx
  Clothoids/Triangle2D.hxx
  Clothoids/Types.hxx
  Clothoids/ClothoidSpline-Interpolation.hxx
  Clothoids.hh)

set(CLOTHOIDS_SRCS_BUILD)
foreach(s ${CLOTHOIDS_SRCS})
set(CLOTHOIDS_SRCS_BUILD ${CLOTHOIDS_SRCS_BUILD} src/${s})
endforeach()

set(CLOTHOIDS_HDRS_BUILD)
set(CLOTHOIDS_HDRS_INSTALL)
set(CLOTHOIDS_HDRS_INSTALL_TARGET)
foreach(h ${CLOTHOIDS_HDRS})
  set(CLOTHOIDS_HDRS_BUILD ${CLOTHOIDS_HDRS_BUILD} 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/${h}>")
  set(CLOTHOIDS_HDRS_INSTALL ${CLOTHOIDS_HDRS_INSTALL} 
    "$<INSTALL_INTERFACE:include/${h}>")
  set(CLOTHOIDS_HDRS_INSTALL_TARGET ${CLOTHOIDS_HDRS_INSTALL_TARGET} 
    "${CMAKE_CURRENT_SOURCE_DIR}/include/${h}")
endforeach()
set(CLOTHOIDS_HDRS_TARGET ${CLOTHOIDS_HDRS_BUILD} ${CLOTHOIDS_HDRS_INSTALL})

#   _____                  _
#  |_   _|_ _ _ _ __ _ ___| |_ ___
#    | |/ _` | '_/ _` / -_)  _(_-<
#    |_|\__,_|_| \__, \___|\__/__/
#                |___/
#
set(CLOTHOIDS_EXPORT_TARGETS ClothoidsStatic)
add_library(ClothoidsStatic STATIC)
target_sources(ClothoidsStatic
  PRIVATE "${CLOTHOIDS_SRCS_BUILD}"
  PUBLIC "${CLOTHOIDS_HDRS_TARGET}")
target_compile_definitions(ClothoidsStatic PUBLIC "_USE_MATH_DEFINES")
target_include_directories(ClothoidsStatic PUBLIC 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include/Clothoids>")
target_include_directories(ClothoidsStatic PRIVATE 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
target_link_libraries(ClothoidsStatic PRIVATE PolynomialRootsStatic)
if(CLOTHOIDS_ENABLE_IPOPT_SOLVER)
target_compile_definitions(ClothoidsStatic PRIVATE G2LIB_IPOPT_CLOTHOID_SPLINE)
  target_link_libraries(ClothoidsStatic PRIVATE Ipopt::Ipopt)
endif()
if(CLOTHOIDS_ENABLE_EIGEN_SOLVER)
target_compile_definitions(ClothoidsStatic PRIVATE G2LIB_LMSOLVE_CLOTHOID_SPLINE)
  target_link_libraries(ClothoidsStatic PRIVATE Clothoids::Eigen3)
endif()
set_target_properties(ClothoidsStatic PROPERTIES
  POSITION_INDIPENDENT_CODE ON
  OUTPUT_NAME Clothoids
  EXPORT_NAME Clothoids_Targets)
target_compile_features(ClothoidsStatic PRIVATE cxx_std_17)
add_library(Clothoids::Static ALIAS ClothoidsStatic)

if(CLOTHOIDS_BUILD_SHARED)
  set(CLOTHOIDS_EXPORT_TARGETS ${CLOTHOIDS_EXPORT_TARGETS} "ClothoidsDynamic")
  add_library(ClothoidsDynamic SHARED)
  target_sources(ClothoidsDynamic
    PRIVATE "${CLOTHOIDS_SRCS_BUILD}"
    PUBLIC "${CLOTHOIDS_HDRS_TARGET}")
  target_compile_definitions(ClothoidsDynamic PUBLIC "_USE_MATH_DEFINES")
  target_include_directories(ClothoidsDynamic PUBLIC 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
    "$<INSTALL_INTERFACE:include/Clothoids>")
  target_include_directories(ClothoidsDynamic PRIVATE 
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>")
  target_link_libraries(ClothoidsDynamic PRIVATE PolynomialRootsStatic)
  if(CLOTHOIDS_ENABLE_IPOPT_SOLVER)
    target_compile_definitions(ClothoidsDynamic PRIVATE G2LIB_IPOPT_CLOTHOID_SPLINE)
    target_link_libraries(ClothoidsDynamic PRIVATE Ipopt::Ipopt)
  endif()
  if(CLOTHOIDS_ENABLE_EIGEN_SOLVER)
    target_compile_definitions(ClothoidsDynamic PRIVATE G2LIB_LMSOLVE_CLOTHOID_SPLINE)
    target_link_libraries(ClothoidsDynamic PRIVATE Clothoids::Eigen3)
  endif()
  set_target_properties(ClothoidsDynamic PROPERTIES
    POSITION_INDIPENDENT_CODE ON
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    OUTPUT_NAME Clothoids
    EXPORT_NAME Clothoids_Targets)
  target_compile_features(ClothoidsDynamic PRIVATE cxx_std_17)
  add_library(Clothoids::Dynamic ALIAS ClothoidsDynamic)
endif()

#  ___         _        _ _ 
# |_ _|_ _  __| |_ __ _| | |
#  | || ' \(_-<  _/ _` | | |
# |___|_||_/__/\__\__,_|_|_|
#                           
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
  "${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

set(PROJECT_INSTALL_CMAKEDIR
  "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
  CACHE STRING "Path To ${PROJECT_NAME} Cmake Files")

install(TARGETS ${CLOTHOIDS_EXPORT_TARGETS}
  EXPORT "${PROJECT_NAME}_Targets"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
          COMPONENT "${PROJECT_NAME}_Install"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
          COMPONENT "${PROJECT_NAME}_Install"
          NAMELINK_COMPONENT "${PROJECT_NAME}_Install"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
          COMPONENT "${PROJECT_NAME}_Install"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

install(FILES
  ${CLOTHOIDS_HDRS_INSTALL_TARGET}
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}"
  COMPONENT "${PROJECT_NAME}_Install")

# Packaging specific installs

export(EXPORT "${PROJECT_NAME}_Targets"
  FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake"
  NAMESPACE "${PROJECT_NAMESPACE}::")

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  @ONLY)

install(EXPORT "${PROJECT_NAME}_Targets"
  DESTINATION "${PROJECT_INSTALL_CMAKEDIR}"
  NAMESPACE "${PROJECT_NAMESPACE}::"
  FILE "${PROJECT_NAME}Targets.cmake"
  COMPONENT "${PROJECT_NAME}_Install")

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
  DESTINATION "${PROJECT_INSTALL_CMAKEDIR}"
  COMPONENT "${PROJECT_NAME}_Install")
