cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROFILING ON CACHE BOOL "Enabel profiling functions")
if (${PROFILING})
  add_definitions(-DPROFILING)
endif()

if(${CMAKE_VERSION} VERSION_LESS 3.17)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.17)
endif()

project(pangolin
  VERSION 0.1
  DESCRIPTION "Small game engine created for fun."
  LANGUAGES CXX C
)

# set(CMAKE_C_COMPILER /usr/bin/clang)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++)
# set(CMAKE_CXX_CPPCHECK "cppcheck")
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(glfw3    REQUIRED)
find_package(assimp   REQUIRED)
find_package(Freetype REQUIRED)

###########################
#### Compilation flags ####
###########################

add_library(compilation_flags INTERFACE)
target_compile_options(compilation_flags
  INTERFACE
      -Wall -Wextra -Wpedantic -Weffc++ -fconcepts-ts
)
target_compile_features(compilation_flags INTERFACE cxx_std_20)

#####################
####    Tests    ####
#####################

option(BUILD_TESTING "Build the tests" ON)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  enable_testing()
  include(GoogleTest)
endif()

#################
##### BUILD #####
#################

add_subdirectory(extern)
add_subdirectory(libs)
add_subdirectory(apps)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(doc)
endif()

#############################
#### Configuration files ####
#############################

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/pangolin)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/pangolinConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/pangolinConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/pangolinConfig.cmake
  INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#####################
####   INSTALL   ####
#####################

#Install the config, configversion and custom find modules
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/pangolinConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/pangolinConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

install(EXPORT pgl_targets
  FILE
    pangolinTargets.cmake
  NAMESPACE
    pgl::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/pangolin
)
