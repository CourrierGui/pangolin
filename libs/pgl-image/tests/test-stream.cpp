#include "../src/stream-utils.hpp"

#include <sstream>
#include <string>

#include <gtest/gtest.h>

TEST(PglImageStream, GetChar) {
  std::stringstream ss;
  ss << "Hello";

  ASSERT_EQ('H', pgl::image::utils::get_char(ss));
  ASSERT_EQ('e', pgl::image::utils::get_char(ss));
  ASSERT_EQ('l', pgl::image::utils::get_char(ss));
  ASSERT_EQ('l', pgl::image::utils::get_char(ss));
  ASSERT_EQ('o', pgl::image::utils::get_char(ss));
}

TEST(PglImageStream, GetUint8) {
  std::stringstream ss;
  uint8_t tests[4] = {
    0x4f, 0x0A, 0x33, 0x14
  };
  for (auto t: tests) {
    ss << t;
  }

  int i=0;
  for (auto t: tests) {
    ASSERT_EQ(t, pgl::image::utils::get_uint8(ss)) << "i=" << i;
    ++i;
  }
}

TEST(PglImageStream, GetUint16) {
  uint16_t tests[4] = {
    0xff04, 0x130a, 0x33fe, 0x14ab
  };
  std::string str = {
    (char)0xff, (char)0x04,
    (char)0x13, (char)0x0a,
    (char)0x33, (char)0xfe,
    (char)0x14, (char)0xab,
  };
  std::stringstream ss(str);

  int i=0;
  for (auto t: tests) {
    ASSERT_EQ(t, pgl::image::utils::get_uint16(ss)) << "i=" << i;
    ++i;
  }
}

TEST(PglImageStream, GetUint32) {
  uint32_t tests[4] = {
    0x10abff04, 0x40ff130a, 0xeefa33fe, 0xabcd14ab
  };
  std::string str = {
    (char)0x10, (char)0xab, (char)0xff, (char)0x04,
    (char)0x40, (char)0xff, (char)0x13, (char)0x0a,
    (char)0xee, (char)0xfa, (char)0x33, (char)0xfe,
    (char)0xab, (char)0xcd, (char)0x14, (char)0xab,
  };
  std::stringstream ss(str);

  int i=0;
  for (auto t: tests) {
    ASSERT_EQ(t, pgl::image::utils::get_uint32(ss)) << "i=" << i;
    ++i;
  }
}
