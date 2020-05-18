#include <pgl-image/image-loader.hpp>

#include <gtest/gtest.h>

TEST(PglImageTest, LoadPNG) {
  const std::string& root = "/home/guillaume/dev/projects/pangolin/";
  pgl::Image image = pgl::image::load_image(root + "resources/awesomeface.png");
}
