add_library(stb_image STATIC stb_image/stb_image.cpp)

add_executable(Pgl.test-stream test-stream.cpp)
target_link_libraries(Pgl.test-stream
  PRIVATE
    gtest gtest_main
    pgl-image
)

add_executable(Pgl.test-image src/test-image.cpp)
target_link_libraries(Pgl.test-image
  PRIVATE
    gtest gtest_main
    stb_image pgl-image
    pangolin::pangolin
)

gtest_add_tests(Pgl.test-stream "" AUTO)
gtest_add_tests(Pgl.test-image "" AUTO)
