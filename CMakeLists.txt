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

find_package(glm      REQUIRED)
find_package(glfw3    REQUIRED)
find_package(assimp   REQUIRED)
find_package(Freetype REQUIRED)

#################
##### BUILD #####
#################


add_subdirectory(libs)
# add_subdirectory(doc)

# add_executable(pangolin-demo apps/demo.cpp)
# because pangolin is a static lib, there's no need to link other libs
# what if pangolin is shared ? -> need to fix that
# target_link_libraries(pangolin-demo pangolin)


#####################
####    Tests    ####
#####################

#add_executable(testimage tests/testimage.cpp)
#target_link_libraries(testimage pangolin)

# option(BUILD_TESTING "Build the tests" ON)
# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
#   enable_testing()
#   include(GoogleTest)
#   add_subdirectory(tests)
# endif()

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

install(EXPORT pangolin-targets
  FILE
    pangolinTargets.cmake
  NAMESPACE
    pangolin::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/pangolin
)
