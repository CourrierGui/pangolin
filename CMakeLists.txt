cmake_minimum_required(VERSION 3.1)

set(PROFILING ON CACHE BOOL "Enabel profiling functions")
if (${PROFILING})
  add_definitions(-DPROFILING)
endif()

if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()

project(pangolin VERSION 0.1
  DESCRIPTION "Probably one of the worst game engines."
  LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set (CMAKE_CXX_STANDARD 17)

add_subdirectory(extern/glfw)
add_subdirectory(extern/glm)
add_subdirectory(extern/assimp)
add_subdirectory(src)
add_subdirectory(apps)
add_subdirectory(docs)

option(BUILD_TESTING "Build the tests" ON)
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(tests)
endif()
