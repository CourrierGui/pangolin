add_executable(Pgl.test-math test-math.cpp)
target_link_libraries(Pgl.test-math
  PRIVATE
    gtest gtest_main
    pangolin::pgl-math
)

gtest_add_tests(Pgl.test-math "" AUTO)
