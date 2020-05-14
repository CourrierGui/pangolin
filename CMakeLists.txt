cmake_minimum_required(VERSION 3.1)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PROFILING ON CACHE BOOL "Enabel profiling functions")
if (${PROFILING})
  add_definitions(-DPROFILING)
endif()

if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()

project(pangolin
  VERSION 0.1
  DESCRIPTION "Probably one of the worst game engines."
  LANGUAGES CXX
)

find_package(glm    REQUIRED)
find_package(glfw3  REQUIRED)
find_package(assimp REQUIRED)

#################
##### BUILD #####
#################

add_library(stb_image STATIC src/stb_image.cpp)
target_include_directories(stb_image PRIVATE include)

add_library(glad STATIC src/glad.cpp)
target_include_directories(glad PRIVATE include)
target_link_libraries(glad dl)

add_library(pangolin STATIC
  src/game-object.cpp
  src/mesh.cpp
  src/model.cpp
  src/particle-generator.cpp
  src/post-processor.cpp
  src/profile.cpp
  src/resource-manager.cpp
  src/shader.cpp
  src/sprite-renderer.cpp
  src/text-renderer.cpp
  src/texture.cpp
  src/image-loader.cpp
)
target_include_directories(pangolin
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    extern/freetype2/include
)
target_compile_options(pangolin PRIVATE -Wall -Wextra)
target_compile_features(pangolin PRIVATE cxx_std_20)
target_link_libraries(pangolin 
  PUBLIC
    assimp glfw glad freetype stb_image
)

add_executable(pangolin-demo apps/demo.cpp)
# because pangolin is a static lib, there's no need to link other libs
# what if pangolin is shared ? -> need to fix that
target_link_libraries(pangolin-demo pangolin)

add_subdirectory(doc)

#################
#### INSTALL ####
#################

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/pangolin)

install(TARGETS pangolin glad stb_image
  EXPORT pangolin-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/pangolin/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin)
install(DIRECTORY include/glad/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/glad)

install(EXPORT pangolin-targets
  FILE
    pangolinTargets.cmake
  NAMESPACE
    pangolin::
  DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/pangolin
)

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

#Install the config, configversion and custom find modules
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/pangolinConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/pangolinConfigVersion.cmake
  DESTINATION ${INSTALL_CONFIGDIR}
)

add_executable(testimage tests/testimage.cpp)
target_link_libraries(testimage pangolin)

# option(BUILD_TESTING "Build the tests" ON)
# if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
#   enable_testing()
#   include(GoogleTest)
#   add_subdirectory(tests)
# endif()
