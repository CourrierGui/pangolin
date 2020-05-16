add_library(stb_image STATIC stb_image/stb_image.cpp)

add_executable(test-image src/test-image.cpp)
target_link_libraries(test-image PRIVATE stb_image pgl-image)
