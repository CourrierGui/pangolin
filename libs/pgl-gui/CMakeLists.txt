add_library(gui SHARED
	src/window.cpp
	src/glfw-window.cpp
)
add_library(pgl::gui ALIAS gui)
target_include_directories(gui
	PUBLIC
		$<INSTALL_INTERFACE:include/pangolin>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		src
)
target_link_libraries(gui
	PUBLIC
		glfw
	PRIVATE
		pgl::glad compilation_flags
)

install(
	TARGETS gui
	EXPORT pgl_targets
	LIBRARY DESTINATION lib/pangolin
	ARCHIVE DESTINATION lib/pangolin
)
install(
	DIRECTORY include/pgl-gui
	DESTINATION include/pangolin
)

# add_subdirectory(tests)
# add_subdirectory(apps)
