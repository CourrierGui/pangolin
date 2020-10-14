add_executable(Pgl.test-checker test-checker.cpp)
target_link_libraries(Pgl.test-checker
	PRIVATE
		pangolin::pgl-test target-flags
)
# add_executable(Pgl.test main.cpp)
# target_link_libraries(Pgl.test
# 	PRIVATE
# 		pangolin::pgl-test
# )
