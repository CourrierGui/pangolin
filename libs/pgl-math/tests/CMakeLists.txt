add_executable(Pgl.test-math test-math.cpp)
target_link_libraries(Pgl.test-math
  PRIVATE
    gtest gtest_main
    pangolin::pgl-math target-flags
)
gtest_add_tests(Pgl.test-math "" AUTO)

add_executable(Pgl.test-matrix test-matrix.cpp)
target_link_libraries(Pgl.test-matrix
	PRIVATE
		gtest gtest_main
		pangolin::pgl-math target-flags
)
gtest_add_tests(Pgl.test-matrix "" AUTO)
