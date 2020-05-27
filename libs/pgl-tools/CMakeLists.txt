add_library(pgl-tools SHARED
	src/logger.cpp
)
add_library(pangolin::pgl-tools ALIAS pgl-tools)
target_include_directories(pgl-tools
	PUBLIC
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	PRIVATE
		src
)
target_link_libraries(pgl-tools
	PRIVATE
		$<BUILD_INTERFACE:target-flags>
)

install(
	TARGETS pgl-tools
	EXPORT pangolin-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)
install(
	DIRECTORY include/pgl-tools
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)

add_executable(logger apps/logger.cpp)
target_link_libraries(logger pgl-tools)
