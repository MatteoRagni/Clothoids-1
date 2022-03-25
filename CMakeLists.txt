############################################################################
#                                                                          #
#  file: CMakeLists.txt                                                    #
#  Copyright (C) 2016                                                      #
#      Enrico Bertolazzi                                                   #
#      Dipartimento di Ingegneria Industriale                              #
#      Universita` degli Studi di Trento                                   #
#      email: enrico.bertolazzi@ing.unitn.it                               #
#                                                                          #
############################################################################

cmake_minimum_required(VERSION 3.14)

file(READ "./VERSION" CLOTHOIDS_VERSION)

project(
  Clothoids
  VERSION ${CLOTHOIDS_VERSION}
  HOMEPAGE_URL "https://github.com/MatteoRagni/Clothoids-1")

#   ___
#  / __| ___ _  _ _ _ __ ___ ___
#  \__ \/ _ \ || | '_/ _/ -_|_-<
#  |___/\___/\_,_|_| \__\___/__/
#
set(CLOTHOIDS_SRCS
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
  Triangle2D.cc)

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
  Clothoids/Utils.hxx
  Clothoids.hh)

set(CLOTHOIDS_SRCS_BUILD)
foreach(s ${CLOTHOIDS_SRCS})
set(CLOTHOIDS_SRCS_BUILD ${CLOTHOIDS_SRCS_BUILD} src/${s})
endforeach()

set(CLOTHOIDS_HDRS_BUILD)
foreach(h ${CLOTHOIDS_HDRS})
set(CLOTHOIDS_HDRS_BUILD ${CLOTHOIDS_HDRS_BUILD} include/${h})
endforeach()

add_subdirectory(./deps/quarticRootsFlocke)
add_subdirectory(./deps/fmt)

#   _____                  _
#  |_   _|_ _ _ _ __ _ ___| |_ ___
#    | |/ _` | '_/ _` / -_)  _(_-<
#    |_|\__,_|_| \__, \___|\__/__/
#                |___/
#
add_library(ClothoidsStatic STATIC)
target_sources(ClothoidsStatic
  PRIVATE "${CLOTHOIDS_SRCS_BUILD}"
  PUBLIC "${CLOTHOIDS_HDRS_BUILD}")
target_include_directories(ClothoidsStatic PRIVATE "include")
target_link_libraries(ClothoidsStatic PRIVATE ebertolazzi_quarticRootsFlocke_Static fmt::fmt-header-only)

#   _____       _
#  |_   _|__ __| |_ ___
#    | |/ -_|_-<  _(_-<
#    |_|\___/__/\__/__/
#
# if ( EB_ENABLE_TESTS )
# 
#   enable_testing()
# 
#   set( EXELISTBIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin" )
#   set( EXELISTCPP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src_tests" )
# 
#   set(
#     EXELISTCPP
#     testBiarc
#     testDistance
#     testDistanceCircuit
#     testG2
#     testG2plot
#     testG2stat
#     testG2stat2arc
#     testG2statCLC
#     testIntersect
#     testIntersect2
#     testIntersect3
#     testPolyline
#     testTriangle2D
#   )
# 
#   add_custom_target( "${PROJECT_NAME}_all_tests" ALL )
# 
#   set( EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin )
#   set( LIBS ${EB_NAMESPACE}_${PROJECT_NAME}_Static ${UTILS} ${ROOTS} ${CMAKE_DL_LIBS} )
#   foreach( S ${EXELISTCPP} )
#     add_executable( ${S} ${CMAKE_CURRENT_SOURCE_DIR}/src_tests/${S}.cc )
#     target_link_libraries( ${S} ${LIBS} )
#     add_test(
#       NAME "${S}"
#       COMMAND ./bin/${S}
#       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#     )
#     add_dependencies( "${PROJECT_NAME}_all_tests" ${S} )
#   endforeach()
# 
# endif()

#   ___         _        _ _
#  |_ _|_ _  __| |_ __ _| | |
#   | || ' \(_-<  _/ _` | | |
#  |___|_||_/__/\__\__,_|_|_|
#
# install(
#   TARGETS ${TARGETS_TO_BE_INSTALLED}
#   # EXPORT (da definire)
#   LIBRARY DESTINATION ${INSTALL_PREFIX}/dll
#   ARCHIVE DESTINATION ${INSTALL_PREFIX}/lib
#   RUNTIME DESTINATION ${INSTALL_PREFIX}/bin
#   PUBLIC_HEADER DESTINATION ${PROJECT_PUBLIC_HEADER_DESTINATION}
# )

#   ___         _
#  | _ \__ _ __| |____ _ __ _ ___
#  |  _/ _` / _| / / _` / _` / -_)
#  |_| \__,_\__|_\_\__,_\__, \___|
#                       |___/
#

# include( ./cmake/CMakeLists-cpack.txt )
# 
# ebertolazzi_final_messages()
