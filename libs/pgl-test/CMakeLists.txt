add_library(pgl-test INTERFACE)
add_library(pgl::test ALIAS pgl-test)
target_include_directories(pgl-test
	INTERFACE
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_subdirectory(tests)

install(
  TARGETS pgl-test
  EXPORT pgl_targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/pgl-test
  DESTINATION include/pangolin
)
