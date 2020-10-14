add_executable(demo demo.cpp)
target_link_libraries(demo
	PRIVATE
		pangolin::pangolin
		pangolin::pgl-gui
		pangolin::pgl-math
		target-flags
)

install(
	TARGETS demo
	EXPORT pangolin-targets
	RUNTIME DESTINATION bin
)
