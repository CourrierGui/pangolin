add_executable(Pgl.test main.cpp)
target_link_libraries(Pgl.test
	PRIVATE
		pangolin::pgl-test
)
