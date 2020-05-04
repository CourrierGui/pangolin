#include <iostream>

#include <pangolin/texture.hpp>


Texture2D::Texture2D()
  : m_width(0), m_height(0),
  m_internal_format(GL_RGB),
  m_image_format(GL_RGB), m_wrap_S(GL_REPEAT),
  m_wrap_T(GL_REPEAT), m_filter_min(GL_LINEAR),
  m_filter_max(GL_LINEAR)
{
  glGenTextures(1, &this->ID);
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned char* data) {
  m_width = width;
  m_height = height;

  // create Texture
  glBindTexture(GL_TEXTURE_2D, ID);
  glTexImage2D(GL_TEXTURE_2D, 0, m_internal_format,
               width, height, 0, m_image_format,
               GL_UNSIGNED_BYTE, data);

  // set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrap_S);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrap_T);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filter_min);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filter_max);

  // unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const {
  glBindTexture(GL_TEXTURE_2D, ID);
}


