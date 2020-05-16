#pragma once

#include <fstream>
#include <vector>

using Buffer = std::vector<char>;

Buffer inline read_buf(std::ifstream& fstream, unsigned int size) {
  Buffer buffer;
  buffer.reserve(size);
  char c;
  for (unsigned int i=0; i<size; ++i) {
    fstream.get(c);
    buffer.push_back(c);
  }
  return buffer;
}

unsigned int inline read_uint(std::ifstream& fstream) {
  unsigned int res=0;
  char c;
  for (int i=3; i>=0; --i) {
    fstream.get(c);
    res += (c << 8*i);
  }
  return res;
}

short int inline read_short(std::ifstream& fstream) {
  short int res = 0;
  char c;
  fstream.get(c);
  res += (c << 8);
  fstream.get(c);
  res += c;
  return res;
}
