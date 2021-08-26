add_library(image SHARED
  src/image-loader.cpp
  src/image-utils.cpp
  src/stream-utils.cpp
  src/png.cpp
)
add_library(pgl::image ALIAS image)
target_include_directories(image
  PUBLIC
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    src
)
target_link_libraries(image
  PRIVATE
    $<BUILD_INTERFACE:compilation_flags>
    stb_image
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(tests)
endif()

install(
  TARGETS image
  EXPORT pgl_targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/pgl-image
  DESTINATION include/pangolin
)
