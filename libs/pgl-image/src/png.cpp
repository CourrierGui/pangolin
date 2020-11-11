#include "png.hpp"

#include <iostream>
#include <algorithm>

#include "stream-utils.hpp"

namespace pgl {
  namespace image {
    namespace png {

      IHDR extract_ihdr(std::istream& fstream) {
        IHDR ihdr;
        utils::get_uint32(fstream);

        if (utils::get_type(fstream) != "IHDR")
          throw std::runtime_error("Invalid chunk");

        ihdr.width = utils::get_uint32(fstream);
        ihdr.height = utils::get_uint32(fstream);
        ihdr.bit_depth = utils::get_uint8(fstream);
        ihdr.color_type = utils::get_uint8(fstream);
        ihdr.compression_method = utils::get_uint8(fstream);
        ihdr.filter_method = utils::get_uint8(fstream);
        ihdr.interlace_method = utils::get_uint8(fstream);
        utils::get_uint32(fstream); //read control
        return ihdr;
      }

      using pixel_it = std::back_insert_iterator<std::vector<unsigned char>>;

      void extract_pixels(std::istream& fstream, const IHDR& ihdr, pixel_it& it) {
        char c;
        fstream.get(c);
        switch (ihdr.bit_depth) {
          case 1:
            for (int i=7; i>=0; --i) {
              *it = ((unsigned char)c >> i) & 1;
            }
            break;
          case 2:
            for (int i=3; i>=0; --i) {
              *it = ((unsigned char)c >> 2*i) & 3;
            }
            break;
          case 4:
            for (int i=1; i>=0; --i) {
              *it = ((unsigned char)c >> 4*i) & 15;
            }
            break;
          case 8:
            *it = (unsigned char)c;
            break;
          case 16: //TODO: is this the correct way ?
            *it = (unsigned char)c;
            break;
        }
      }

      void read_idat(
        std::istream& fstream, const uint32_t size,
        const IHDR& ihdr, pixel_it& it)
      {
        uint32_t nb_iter = size;
        switch (ihdr.bit_depth) {
          case  1: nb_iter /= 8; break;
          case  2: nb_iter /= 4; break;
          case  4: nb_iter /= 2; break;
          case  8: break;
          case 16: nb_iter *= 2; break;
        }

        for (uint32_t i=0; i<nb_iter; ++i) {
          extract_pixels(fstream, ihdr, it);
        }
      }

      bool valid_type(const std::string& type) {
        return (std::find(TYPES.begin(), TYPES.end(), type) != TYPES.end());
      }

      //TODO: improve perfomance ?
      void next_chunk(
        std::istream& fstream, uint32_t& size,
        std::string& type)
      {
        std::string current_type = utils::get_type(fstream);
        while (!valid_type(current_type)) {
          char c; fstream.get(c);
          size = ((size & 0x00ff0000) << 8)
               | ((size & 0x0000ff00) << 8)
               | ((size & 0x000000ff) << 8)
               | ((unsigned char)current_type[0]);
          current_type.erase(0, 1);
          current_type.push_back(c);
        }
        type = current_type;
      }

      void skip_chunk(std::istream& fstream, const uint32_t size) {
        fstream.ignore(size+4); //ignore size of chunk + size of control
      }

      bool check_control(std::istream&) {
        /* uint32_t control = utils::get_uint32(fstream); */
        //TODO
        return true;
      }

    } /* end of namespace png */
  } /* end of namespace png */
} /* end of namespace png */

#if 0
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

unsigned short get_sint(Buffer::const_iterator& it) {
  return (*(it++) << 1*8) + *it;
}

unsigned int get_uint(Buffer::const_iterator& it) {
  return (*(it++) << 3*8) + (*(it++) << 2*8) + (*(it++) << 1*8) + *it;
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
  std::string text; // use wstring ?

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

struct PLTE {
  char red, green, blue;
  unsigned int size;

  inline PLTE(const Chunk& chunk) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    red = *(it++);
    green = *(it++);
    blue = *(it++);
  }
};

std::ostream& operator<<(std::ostream& os, const PLTE& plte) {
  os << "Type: PLTE\n"
    << "Size: " << plte.size << '\n'
    << "Red: " << plte.red << '\n'
    << "Green: " << plte.green << '\n'
    << "Blue: " << plte.blue << '\n';
  return os;
}

struct sBIT {
  unsigned int size;
  char greyscale;
  char red, green, blue;
  char alpha;

  inline sBIT(const Chunk& chunk, char color_type) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    if ((int) color_type == 1) {
      greyscale = *(it);
    } else if ((int)color_type == 2 || (int)color_type == 3) {
      red = *(it++);
      green = *(it++);
      blue = *it;
    } else if ((int)color_type == 4) {
      greyscale = *(it++);
      alpha = *it;
    } else if ((int)color_type == 6) {
      red = *(it++);
      green = *(it++);
      blue = *(it++);
      alpha = *it;
    }
  }
};

std::ostream& operator<<(std::ostream& os, const sBIT& sbit) {
  os << "Type: sBIT\n"
    << "Size: " << sbit.size << '\n'
    << "Gray scale: " << sbit.greyscale << '\n'
    << "Red: " << sbit.red << '\n'
    << "Green: " << sbit.green << '\n'
    << "Blue: " << sbit.blue << '\n'
    << "Alpha: " << sbit.alpha << '\n';
  return os;
}

struct gAMA {
  unsigned int size;
  unsigned int gamma;

  inline gAMA(const Chunk& chunk) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    gamma = get_uint(it);
  }
};

std::ostream& operator<<(std::ostream& os, const gAMA& gama) {
  os << "Type: gAMA\n"
    << "Size: " << gama.size << '\n'
    << "Gamma: " << gama.gamma << '\n';
  return os;
}

struct zTXt {
  unsigned int size;
  char compression_method;
  std::string keyword;
  std::string text;

  inline zTXt(const Chunk& chunk) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    auto end = chunk.data.cend();

    get_string(it, keyword);
    ++it;
    compression_method = *(it++);
    get_string(it, end, text);
  }
};

std::ostream& operator<<(std::ostream& os, const zTXt& ztxt) {
  os << "Type: zTXT\n"
    << "Size: " << ztxt.size << '\n'
    << "Keyword: " << ztxt.keyword << '\n'
    << "Compression method: " << (int)ztxt.compression_method << '\n'
    << "Text size: " << ztxt.text.size() << '\n';
  return os;
}

struct bKDG {
  unsigned int size;
  unsigned short grayscale;
  unsigned short red, green, blue;
  char palette_index;

  inline bKDG(const Chunk& chunk, char color_type) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    if ((int)color_type == 0 || (int)color_type == 4) {
      grayscale = get_sint(it);
    } else if ((int)color_type == 2 || (int)color_type == 6) {
      red = get_sint(it); ++it;
      green = get_sint(it); ++it;
      blue = get_sint(it);
    } else if ((int)color_type == 3) {
      palette_index = *it;
    }
  }
};

std::ostream& operator<<(std::ostream& os, const bKDG& bkdg) {
  os << "Type: bKDG\n"
    << "Size: " << bkdg.size << '\n';
  return os;
}

struct hIST {
  unsigned int size;
  std::vector<unsigned short> frequencies;

  inline hIST(const Chunk& chunk) {
    auto it = chunk.data.cbegin();
    frequencies.reserve(size/2);
    for (unsigned int i=0; i<size/2; ++i) {
      frequencies.push_back(get_sint(it));
      ++it;
    }
  }
};

std::ostream& operator<<(std::ostream& os, const hIST& hist) {
  os << "Type: hIST\n"
    << "Size: " << hist.size << '\n'
    << "Frequencies: ";
  for (auto f: hist.frequencies) {
    os << f << ", ";
  }
  os << '\n';
  return os;
}

struct tRNS {
  unsigned int size;
  unsigned short grey_sample;
  unsigned short red_sample, blue_sample, green_sample;
  std::vector<char> alpha_palette;

  inline tRNS(const Chunk& chunk, char color_type) {
    size = chunk.data.size();

    auto it = chunk.data.cbegin();
    if ((int)color_type == 0) {
      grey_sample = get_sint(it);
    } else if ((int)color_type == 2) {
      red_sample = get_sint(it); ++it;
      blue_sample = get_sint(it); ++it;
      green_sample = get_sint(it);
    } else if ((int)color_type == 3) {
      for (unsigned int i=0; i<size; ++i) {
        alpha_palette.push_back(*(it++));
      }
    }
  }
};

std::ostream& operator<<(std::ostream& os, const tRNS& trns) {
  os << "Type: tRNS\n"
    << "Size: " << trns.size << '\n'
    << "Grey sample: " << trns.grey_sample << '\n'
    << "Red sample: " << trns.red_sample << '\n'
    << "Blue sample: " << trns.blue_sample << '\n'
    << "Green sample: " << trns.green_sample << '\n'
    << "Alpha palette: ";
  for (auto a: trns.alpha_palette) {
    std::clog << (int)a << ' ';
  }
  std::clog << '\n';
  return os;
}

struct PaletEntry {
  unsigned short red, green, blue;
  unsigned short alpha, frequency;
};

struct sPLT {
  unsigned int size;
  std::string palette_name;
  char sample_depth;
  std::vector<PaletEntry> palet_entries;

  inline sPLT(const Chunk& chunk) {
    size = chunk.data.size();
    auto it = chunk.data.cbegin();
    get_string(it, palette_name);
    sample_depth = *(it++);

    unsigned int left = size - 1 - palette_name.size();
    PaletEntry pe;
    if (sample_depth == 8 && left % 6 == 0) {
      left /= 6;
      for (unsigned int i=0; i<left; ++i) {
        pe.red       = *(it++);
        pe.green     = *(it++);
        pe.blue      = *(it++);
        pe.alpha     = *(it++);
        pe.frequency = get_sint(it); ++it;
        palet_entries.push_back(pe);
      }
    } else if (sample_depth == 16 && left % 10 == 0) {
      left /= 10;
      for (unsigned int i=0; i<left; ++i) {
        pe.red       = get_sint(it); ++it;
        pe.green     = get_sint(it); ++it;
        pe.blue      = get_sint(it); ++it;
        pe.alpha     = get_sint(it); ++it;
        pe.frequency = get_sint(it); ++it;
        palet_entries.push_back(pe);
      }
    }
  }
};

std::ostream& operator<<(std::ostream& os, const sPLT& splt) {
  os << "Type: sPLT\n"
    << "Size: " << splt.size << '\n'
    << "Palette name: " << splt.palette_name << '\n'
    << "Sample depth: " << (int)splt.sample_depth << '\n'
    << "Palette entries: ";
  for (auto pe: splt.palet_entries) {
    std::clog
      << '['
      << pe.red << ','
      << pe.green << ','
      << pe.blue << ','
      << pe.alpha << ','
      << pe.frequency << "], ";
  }
  std::clog << '\n';
  return os;
}

class PNG {
  private:
    std::vector<Chunk> chunks;
    CRC32 crc32;
    char color_type;

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
          color_type = ihdr.color_type;
          std::clog << ihdr << '\n';

        } else if (chunk.type == "IDAT") {
          IDAT idat(chunk);
          std::clog << idat << '\n';

        } else if (chunk.type == "PLTE") {
          PLTE plte(chunk);
          std::clog << plte << '\n';

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
          sBIT sbit(chunk, color_type);
          std::clog << sbit << '\n';

        } else if (chunk.type == "gAMA") {
          gAMA gama(chunk);
          std::clog << gama << '\n';

        } else if (chunk.type == "zTXt") {
          zTXt ztxt(chunk);
          std::clog << ztxt << '\n';

        } else if (chunk.type == "bKDG") {
          bKDG bkdg(chunk, color_type);
          std::clog << bkdg << '\n';

        } else if (chunk.type == "hIST") {
          hIST hist(chunk);
          std::clog << hist << '\n';

        } else if (chunk.type == "tRNS") {
          tRNS trns(chunk, color_type);
          std::clog << trns << '\n';

        } else if (chunk.type == "sPLT") {
          sPLT splt(chunk);
          std::clog << splt << '\n';

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
#endif
