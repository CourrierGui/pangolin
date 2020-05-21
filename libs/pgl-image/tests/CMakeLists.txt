add_library(stb_image STATIC stb_image/stb_image.cpp)
target_include_directories(stb_image PUBLIC stb_image)
set_property(TARGET stb_image PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable(Pgl.test-stream test-stream.cpp)
target_link_libraries(Pgl.test-stream
  PRIVATE
    gtest gtest_main
    pgl-image
)

add_executable(Pgl.test-png test-png.cpp)
target_link_libraries(Pgl.test-png
  PRIVATE
    gtest gtest_main
    pgl-image
)

add_executable(Pgl.test-image test-image.cpp)
target_link_libraries(Pgl.test-image
  PRIVATE
    gtest gtest_main
    stb_image pgl-image
)

gtest_add_tests(Pgl.test-stream "" AUTO)
gtest_add_tests(Pgl.test-image  "" AUTO)
gtest_add_tests(Pgl.test-png    "" AUTO)
