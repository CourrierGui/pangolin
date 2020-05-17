add_library(pgl-image SHARED
  src/image-loader.cpp
)
target_include_directories(pgl-image
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    src
)

add_subdirectory(tests)

install(
  TARGETS pgl-image
  EXPORT pangolin-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  DIRECTORY include/pgl-image
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
