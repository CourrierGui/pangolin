add_library(stb_image STATIC stb_image/stb_image.cpp)

add_executable(test-image-bin src/test-image.cpp)
target_link_libraries(test-image-bin PRIVATE stb_image pgl-image gtest)

add_test(
  NAME test-image
  COMMAND test-image-bin
)
