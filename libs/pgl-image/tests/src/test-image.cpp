#include <pgl-image/image-loader.hpp>
#include <gtest/gtest.h>

TEST(PglImageTest, LoadPNG) {
  pgl::loader::load_png("../tests/resources/awesomeface.png");
  pgl::loader::load_png("../tests/resources/paddle.png");
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
