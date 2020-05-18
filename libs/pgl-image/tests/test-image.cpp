#include "../src/image-utils.hpp"
#include <pgl-image/image-loader.hpp>
#include <stb_image.h>

#include <gtest/gtest.h>

struct PglImageUtils : testing::Test {

  std::ifstream fstream;
  int width, height, nb_channels;
  unsigned char* data;

  void SetUp() override {
    const std::string filepath = "../resources/awesomeface.png";
    fstream.open(filepath);
    data = stbi_load(filepath.c_str(), &width, &height, &nb_channels, 0);
  }
  void TearDown() override {
    fstream.close();
  }
};

TEST_F(PglImageUtils, PngOpened) {
  ASSERT_TRUE(fstream.is_open());
}

TEST_F(PglImageUtils, PngSignature) {
  ASSERT_TRUE(pgl::image::is_png(fstream));
}

TEST_F(PglImageUtils, PngData) {
  pgl::Image image = pgl::image::extract_png(fstream);
  ASSERT_EQ(width,        image.width);
  ASSERT_EQ(height,       image.height);
  ASSERT_EQ(nb_channels,  image.depth);
  //TODO: assert equal data
}
