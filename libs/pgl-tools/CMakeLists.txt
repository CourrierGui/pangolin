add_library(tools SHARED
	src/logger.cpp
	src/profile.cpp
)
add_library(pgl::tools ALIAS tools)
target_include_directories(tools
	PUBLIC
		$<INSTALL_INTERFACE:include/pangolin>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		src
)
target_link_libraries(tools
	PRIVATE
		compilation_flags
)

install(
	TARGETS tools
	EXPORT pgl_targets
	LIBRARY DESTINATION lib/pangolin
	ARCHIVE DESTINATION lib/pangolin
)
install(
	DIRECTORY include/pgl-tools
	DESTINATION include/pangolin
)

add_subdirectory(tests)
