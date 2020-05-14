#pragma once

#include <iostream>

#include "stream_utils.hpp"

class CRC32 {
  private:
    unsigned long table[256];
    unsigned long crc;

    void inline make_table() {
      unsigned long c;
      int n, k;

      for (n = 0; n < 256; n++) {
        c = (unsigned long)n;
        for (k = 0; k < 8; k++) {
          if (c & 1)
            c = 0xedb88320UL ^ (c >> 1);
          else
            c = c >> 1;
        }
        table[n] = c;
      }
    }

  public:
    CRC32() : table(), crc(0xffffffffUL) {
      make_table();
    }

    /**
     * Update a running CRC with the bytes buf[0..len-1]--the CRC should be
     * initialized to all 1's, and the transmitted value is the 1's complement of
     * the final running CRC (see the crc() routine below).
     */
    unsigned int next(const Buffer& buf) {
      unsigned int c = crc;
      for (unsigned int n=0; n<buf.size(); n++) {
        c = table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
      }
      crc = c ^ 0xffffffffUL;
      return crc;
    }
};
