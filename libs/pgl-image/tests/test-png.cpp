#include "../src/png.hpp"
#include "../src/stream-utils.hpp"

#include <string>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

TEST(PglImagePng, ExtractPixels) {
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

    for (size_t j=0; j<expected.size()/8; ++j) {
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

  for (size_t j=0; j<expected.size()/8; ++j) {
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

TEST(PglImagePng, NextChunk) {
  std::stringstream ss;
  ss << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)10
    << "IHDR"
    << (char)0xfa
    << (char)0xfa
    << (char)0xfa
    << (char)0xfa
    << (char)0xfa
    << (char)0xfa
    << (uint32_t)0xabcdef10
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)5
    << "sRGB";

  uint32_t size = pgl::image::utils::get_uint32(ss);
  std::string type = pgl::image::utils::get_type(ss);
  ASSERT_EQ(10, size);
  ASSERT_EQ("IHDR", type);
  pgl::image::png::next_chunk(ss, size, type);
  ASSERT_EQ(5, size);
  ASSERT_EQ("sRGB", type);
}

TEST(PglImagePng, SkipChunk) {
  std::stringstream ss;
  ss
    //size
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)2
    //type
    << "IHDR"
    //data
    << (char)0xfa
    << (char)0xfa
    //control
    << (unsigned char)0xab
    << (unsigned char)0xcd
    << (unsigned char)0xef
    << (unsigned char)0x10
    //size
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)5
    //type
    << "sRGB";

  uint32_t size = pgl::image::utils::get_uint32(ss);
  std::string type = pgl::image::utils::get_type(ss);
  ASSERT_EQ(2, size);
  ASSERT_EQ("IHDR", type);

  pgl::image::png::skip_chunk(ss, size);

  size = pgl::image::utils::get_uint32(ss);
  type = pgl::image::utils::get_type(ss);

  ASSERT_EQ(5, size);
  ASSERT_EQ("sRGB", type);
}

TEST(PglImagePng, ExtractIhrd) {
  pgl::image::png::IHDR ihdr;
  std::stringstream ss;

  ss
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)13
    << "IHDR"
    //width 512
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)2
    << (unsigned char)0
    //Height 256
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)1
    << (unsigned char)0
    //Bit depth
    << (unsigned char)8
    //Color type
    << (unsigned char)4
    //Compression method
    << (unsigned char)0
    //Filter method
    << (unsigned char)1
    //Interlace method
    << (unsigned char)1
    //Control
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)17;

  ASSERT_NO_THROW({
    ihdr = pgl::image::png::extract_ihdr(ss);
  });

  ASSERT_EQ(512, ihdr.width             );
  ASSERT_EQ(256, ihdr.height            );
  ASSERT_EQ(8,   ihdr.bit_depth         );
  ASSERT_EQ(4,   ihdr.color_type        );
  ASSERT_EQ(0,   ihdr.compression_method);
  ASSERT_EQ(1,   ihdr.filter_method     );
  ASSERT_EQ(1,   ihdr.interlace_method  );

  ss.clear();
  ss
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)0
    << (unsigned char)13
    << "IDAT";
  ASSERT_THROW(
    ihdr = pgl::image::png::extract_ihdr(ss),
    std::runtime_error
  );
}

TEST(PglImagePng, ReadIdat) {

}

TEST(PglImagePng, CheckControl) {

}
