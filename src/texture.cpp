#include <iostream>

#include <pangolin/texture.hpp>

namespace pgl {
  namespace resources {

Texture2D::Texture2D()
  : width(0), height(0),
  internal_format(GL_RGB),
  image_format(GL_RGB), wrap_S(GL_REPEAT),
  wrap_T(GL_REPEAT), filter_min(GL_LINEAR),
  filter_max(GL_LINEAR)
{
  glGenTextures(1, &id);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data) {
  width = width;
  height = height;

  // create Texture
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, internal_format,
               width, height, 0, image_format,
               GL_UNSIGNED_BYTE, data);

  // set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_S);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_T);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter_min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter_max);

  // unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {
  glBindTexture(GL_TEXTURE_2D, id);
}

  } /* end of namespace resources */
} /* end of namespace pgl */
