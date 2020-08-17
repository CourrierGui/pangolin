add_library(pgl-gui SHARED
	src/window.cpp
	src/glfw-window.cpp
)
add_library(pangolin::pgl-gui ALIAS pgl-gui)
target_include_directories(pgl-gui
	PUBLIC
		$<INSTALL_INTERFACE:include/pangolin>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		src
)
target_link_libraries(pgl-gui
	PUBLIC
		pangolin::glad
	PRIVATE
		$<BUILD_INTERFACE:target-flags>
)

install(
	TARGETS pgl-gui
	EXPORT pangolin-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)
install(
	DIRECTORY include/pgl-gui
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)

add_subdirectory(tests)
add_subdirectory(apps)
