add_library(pgl-math INTERFACE)
add_library(pangolin::pgl-math ALIAS pgl-math)
target_include_directories(pgl-math
	INTERFACE
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(pgl-image
  PRIVATE
		$<BUILD_INTERFACE:target-flags> stb_image # TODO why?
)

add_subdirectory(tests)

install(
  TARGETS pgl-math
  EXPORT pangolin-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
)
install(
  DIRECTORY include/pgl-math
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)
