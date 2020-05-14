#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#include "stream_utils.hpp"
#include "crc.hpp"

struct Chunk {
  std::string type;
  Buffer data;
  unsigned int control;

  inline Chunk(const Buffer& buf, const unsigned int control)
    : data(buf.begin()+4,buf.end()), control(control)
  {
    for (auto it=buf.begin(); it!= buf.begin()+4; ++ it) {
      type.push_back(*it);
    }
  }
};

unsigned int get_uint(Buffer::const_iterator& it) {
  return (*(it++) << 3*8) +(*(it++) << 2*8) +(*(it++) << 1*8) + *it;
}

void get_string(Buffer::const_iterator& it, std::string& str) {
  while (*it != '\0') {
    str.push_back(*(it++));
  }
}

void get_string(
  Buffer::const_iterator& it,
  Buffer::const_iterator& end,
  std::string& str)
{
  while (it != end) {
    str.push_back(*(it++));
  }
}

struct IHDR {
  unsigned int width, height, size;
  char bit_depth, color_type;
  char compression_method;
  char filter_method, interlace_method;

  inline IHDR(const Chunk& chunk) {
    auto it = chunk.data.begin();
    size = chunk.data.size();
    width = get_uint(it); ++it;
    height = get_uint(it); ++it;

    bit_depth = *(it++);
    color_type = *(it++);
    compression_method = *(it++);
    filter_method = *(it++);
    interlace_method = *it;
  }
};

std::ostream& operator<<(std::ostream& os, const IHDR& ihdr) {
  os << "Type: IHDR\n"
    << "Size: "               << ihdr.size << '\n'
    << "Width: "              << ihdr.width << '\n'
    << "Height: "             << ihdr.height << '\n'
    << "Bit depth: "          << (int)ihdr.bit_depth << '\n'
    << "Color type: "         << (int)ihdr.color_type << '\n'
    << "Compression method: " << (int)ihdr.compression_method << '\n'
    << "Filter method: "      << (int)ihdr.filter_method << '\n'
    << "Interlace mode: "     << (int)ihdr.interlace_method << '\n';
  return os;
}

struct iTXt {
  std::string keyword;
  unsigned int size;
  char compression_flag, compression_method;
  std::string language_tag;
  std::string translated_keyword;
  std::string text;

  inline iTXt(const Chunk& chunk) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    auto end = chunk.data.cend();
    get_string(it, keyword);
    compression_flag = *(it++);
    compression_method = *(it++);
    get_string(it, language_tag);
    get_string(it, translated_keyword);
    get_string(it, end, text);
  }
};

std::ostream& operator<<(std::ostream& os, const iTXt& itxt) {
  os << "Type: iTXt" << '\n'
    << "Size: "               << itxt.size << '\n'
    << "Keyword: " << itxt.keyword << '\n'
    << "Compression flag: " << itxt.compression_flag << '\n'
    << "Compression method: " << itxt.compression_method << '\n'
    << "Translate keyword: " << itxt.translated_keyword << '\n'
    << "Language tag: " << itxt.language_tag << '\n'
    << "Text: " << itxt.text.size() << '\n';
  return os;
}

struct tEXt {
  std::string keyword;
  std::string text;
  unsigned int size;

  inline tEXt(const Chunk& chunk) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    auto end = chunk.data.cend();
    get_string(it, keyword);
    get_string(it, end, text);
  }
};

std::ostream& operator<<(std::ostream& os, const tEXt& text) {
  os << "Type: tTXt\n"
    << "Size: " << text.size << '\n'
    << "Keyword: " << text.keyword << '\n'
    << "Text: " << text.text.size() << '\n';
  return os;
}

struct tIME {
  unsigned short year;
  char month, day, hour, minute, second;
  unsigned int size;

  inline tIME(const Chunk& chunk) {
    auto it = chunk.data.cbegin();
    size = chunk.data.size();
    year = (*(it++) << 8) + *(it++);
    month = *(it++);
    day = *(it++);
    hour = *(it++);
    minute = *(it++);
    second = *it;
  }
};

std::ostream& operator<<(std::ostream& os, const tIME& time) {
  os << "Type: tIME\n"
    << "Size: " << time.size << '\n'
    << "Date: " << (int)time.day << '/'
    << (int)time.month << '/' << time.year << '\n'
    << "Time: " << (int)time.hour << ':'
    << (int)time.minute << ':' << (int)time.second << '\n';
  return os;
}

struct pHYs {
  unsigned int size;
  char unit_spec;
  unsigned int unitx, unity;

  inline pHYs(const Chunk& chunk) {
    auto it = chunk.data.cbegin();
    unitx = get_uint(it);
    ++it;
    unity = get_uint(it);
    ++it;
    unit_spec = *it;
  }
};

std::ostream& operator<<(std::ostream& os, const pHYs& phys) {
  os << "Type pHYs\n"
    << "Size: " << phys.size << '\n'
    << "Unit X: " << phys.unitx << '\n'
    << "Unit Y: " << phys.unity << '\n'
    << "Unit specifier: " << (int)phys.unit_spec << '\n';
  return os;
}

struct sRGB {
  unsigned int size;
  char rendering_intent;

  inline sRGB(const Chunk& chunk) {
    size = chunk.data.size();
    rendering_intent = chunk.data.front();
  }
};

std::ostream& operator<<(std::ostream& os, const sRGB& srgb) {
  os << "Type: sRGB\n"
    << "Size: " << srgb.size << '\n'
    << "Rendering intent: " << (int)srgb.rendering_intent << '\n';
  return os;
}

struct IDAT {
  unsigned int size;
  inline IDAT(const Chunk& chunk) {
    size = chunk.data.size();
  }
};

std::ostream& operator<<(std::ostream& os, const IDAT& idat) {
  os << "Type: IDAT\n"
    << "Size: " << idat.size << '\n';
  return os;
}

struct iCCP {
  unsigned int size;
  std::string profile_name;
  char compression_method;
  std::string compressed_profile;

  inline iCCP(const Chunk& chunk) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    auto end = chunk.data.cend();
    get_string(it, profile_name);
    *(it++);
    compression_method = *(it++);
    get_string(it, end, compressed_profile);
  }
};

std::ostream& operator<<(std::ostream& os, const iCCP& iccp) {
  os << "Type: iCCP\n"
    << "Size: " << iccp.size << '\n'
    << "Profile name: " << iccp.profile_name << '\n'
    << "Compression method: " << (int)iccp.compression_method << '\n'
    << "Compression profile: " << iccp.compressed_profile.size() << '\n';
  return os;
}

struct cHRM {
  unsigned int size;
  unsigned int whitex, whitey;
  unsigned int redx,   redy;
  unsigned int greenx, greeny;
  unsigned int bluex,  bluey;

  inline cHRM(const Chunk& chunk) {
    auto it = chunk.data.cbegin();
    size    = chunk.data.size();
    whitex  = get_uint(it);
    whitey  = get_uint(it);
    redx    = get_uint(it);
    redy    = get_uint(it);
    greenx  = get_uint(it);
    greeny  = get_uint(it);
    bluex   = get_uint(it);
    bluey   = get_uint(it);
  }
};

std::ostream& operator<<(std::ostream& os, const cHRM& chrm) {
  os << "Type: cHRM\n"
    << "Size: " << chrm.size << '\n'
    << "White x: " << chrm.whitex << '\n'
    << "White y: " << chrm.whitey << '\n'
    << "Red x: " << chrm.redx << '\n'
    << "Red y: " << chrm.redy << '\n'
    << "Green x: " << chrm.greenx << '\n'
    << "Green y: " << chrm.greeny << '\n'
    << "Blue x: " << chrm.bluex << '\n'
    << "Blue y: " << chrm.bluey << '\n';
  return os;
}

class PNG {
  private:
    std::vector<Chunk> chunks;
    CRC32 crc32;

    Chunk read_chunk(std::ifstream& fstream) {
      unsigned int size = read_uint(fstream);
      if (size == 14472) size = 14728; // putain mais pourquoi j'ai des png tout pété?
      if (size == 3051) size = 3307;
      if (size == 13789) size = 14045;
      Buffer buf = read_buf(fstream, size+4);
      unsigned int control = read_uint(fstream);

      unsigned long crc = crc32.next(buf);
      if (control != crc) {
        std::clog
          << "Control not matching: " << std::hex
          << control << " != " << crc << '\n'
          << std::dec;
      }

      return {buf, control};
    }

    bool check_signature(std::ifstream& fstream) {
      char c;
      fstream.get(c); if ((int)(unsigned char)c != 137) return false;
      fstream.get(c); if ((int)(unsigned char)c !=  80) return false;
      fstream.get(c); if ((int)(unsigned char)c !=  78) return false;
      fstream.get(c); if ((int)(unsigned char)c !=  71) return false;
      fstream.get(c); if ((int)(unsigned char)c !=  13) return false;
      fstream.get(c); if ((int)(unsigned char)c !=  10) return false;
      fstream.get(c); if ((int)(unsigned char)c !=  26) return false;
      fstream.get(c); if ((int)(unsigned char)c !=  10) return false;
      return true;
    }

  public:
    PNG(std::ifstream& fstream) : crc32() {
      if (!check_signature(fstream)) {
        std::clog << "Wrong signature !\n";
        throw std::runtime_error("Invalid PNG signature.");
      }
      int i = 0;
      while (true) {
      /* for (int i=0; i<7; ++i) { */
        Chunk chunk = read_chunk(fstream);
        ++i;
        std::clog << "Chunk number " << i << '\n';

        if (chunk.type == "IHDR") {
          IHDR ihdr(chunk);
          std::clog << ihdr << '\n';

        } else if (chunk.type == "IDAT") {
          IDAT idat(chunk);
          std::clog << idat << '\n';

        } else if (chunk.type == "PLTE") {

        } else if (chunk.type == "IEND") {
          std::clog << "Type: IEND\n";
          std::clog << "Finished\n";
          break;

        } else if (chunk.type == "sRGB") {
          sRGB srgb(chunk);
          std::clog << srgb << '\n';

        } else if (chunk.type == "pHYs") {
          pHYs phys(chunk);
          std::clog << phys << '\n';

        } else if (chunk.type == "tIME") {
          tIME time(chunk);
          std::clog << time << '\n';

        } else if (chunk.type == "tEXt") {
          tEXt text(chunk);
          std::clog << text << '\n';

        } else if (chunk.type == "iTXt") {
          iTXt itxt(chunk);
          std::clog << itxt << '\n';

        } else if (chunk.type == "cHRM") {
          cHRM chrm(chunk);
          std::clog << chrm << '\n';

        } else if (chunk.type == "iCCP") {
          iCCP iccp(chunk);
          std::clog << iccp << '\n';

        } else if (chunk.type == "sBIT") {
        } else if (chunk.type == "gAMA") {
        } else if (chunk.type == "zTXt") {
        } else if (chunk.type == "bKDG") {
        } else if (chunk.type == "hIST") {
        } else if (chunk.type == "tRNS") {
        } else if (chunk.type == "sPLT") {
        } else {
          std::clog << chunk.type << '\n';
        }
        chunks.push_back(chunk);
      }

      /* char c; */
      /* unsigned int size = read_uint(fstream); */
      /* fstream.get(c); std::clog << c; */
      /* fstream.get(c); std::clog << c; */
      /* fstream.get(c); std::clog << c; */
      /* fstream.get(c); std::clog << c; */
      /* std::clog << '\n' << size << '\n'; */
      /* unsigned int j = 1; */
      /* bool cont = true; */
      /* while (cont) { */
      /*   fstream.get(c); */
      /*   ++j; */
      /*   if (c == 'I') { */
      /*     fstream.get(c); */
      /*     ++j; */
      /*     if (c == 'E') { */
      /*       cont = false; */
      /*     } */
      /*   } */
      /* } */
      /* std::clog << j << '\n'; */
    }
};
