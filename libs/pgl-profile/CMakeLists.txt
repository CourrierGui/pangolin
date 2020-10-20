add_library(profile SHARED
	src/profile.cpp
)
target_include_directories(profile
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_}include/pgl-profile>
)
target_link_libraries(profile
	PRIVATE
		compilation_flags
)

install(
	TARGETS profile
	EXPORT pgl_targets
	LIBRARY DESTINATION lib/pangolin
	ARCHIVE DESTINATION lib/pangolin
)
install(
	DIRECTORY include/pgl-profile
	DESTINATION include/pangolin
)
