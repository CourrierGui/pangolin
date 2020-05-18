#include "../src/png.hpp"

#include <string>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

TEST(PglImagePng, ReadPixel) {
  std::vector<unsigned char> pixels;
  auto it = std::back_inserter(pixels);

  pgl::image::png::IHDR ihdr;
  ihdr.bit_depth = 1;

  std::array<unsigned char, 16> expected = {
    0, 1, 0, 0, 1, 1, 0, 0,
    0, 1, 1, 0, 0, 1, 0, 1
  };

  std::stringstream ss;
  for (int i=0; i<4; ++i) {
    ss.clear();
    pixels.clear();
    ss << (char)0b01001100;
    ss << (char)0b01100101;

    for (int j=0; j<expected.size()/8; ++j) {
      pgl::image::png::extract_pixels(ss, ihdr, it);
    }

    auto expected_it = expected.begin();
    int j = 0;
    for (auto c: pixels) {
      unsigned char e = 0;
      for (int k=ihdr.bit_depth-1; k>=0; --k) {
        e |= (*(expected_it++) << k);
      }
      ASSERT_EQ((int)e, (int)c) << "j=" << j << "\nbit depth=" << (int)ihdr.bit_depth;
      ++j;
    }
    ihdr.bit_depth *= 2;
  }

  ihdr.bit_depth = 16;
  pixels.clear();
  ss.clear();
  ss << (char)0b01001100;
  ss << (char)0b01100101;

  for (int j=0; j<expected.size()/8; ++j) {
    pgl::image::png::extract_pixels(ss, ihdr, it);
  }

  uint16_t e = 0b0100110001100101;
  uint16_t res = (pixels[0] << 8) | pixels[1];
  ASSERT_EQ(e, res) << "bit depth=" << ihdr.bit_depth;
}

TEST(PglImagePng, ValidType) {
  const std::array<std::string, 18> types = {
    "IDAT", "PLTE", "cHRM", "gAMA", "iCCP",
    "sBIT", "sRGB", "bKGD", "hIST", "tRNS",
    "pHYs", "sPLT", "tIME", "iTXt", "tEXt",
    "zTXt", "IEND", "IHDR"
  };

  for (auto type: types) {
    ASSERT_TRUE(pgl::image::png::valid_type(type)) << "type=" << type;
  }
  ASSERT_FALSE(pgl::image::png::valid_type("toto")) << "type=toto";
}
