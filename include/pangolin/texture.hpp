#pragma once

/*******************************************************************
 ** This code is part of Breakout.
 **
 ** Breakout is free software: you can redistribute it and/or modify
 ** it under the terms of the CC BY 4.0 license as published by
 ** Creative Commons, either version 4 of the License, or (at your
 ** option) any later version.
 ******************************************************************/

#include <glad/glad.h>

/* Texture2D is able to store and configure a texture in OpenGL.
 * It also hosts utility functions for easy management.
 */
class Texture2D {
  public:
    // holds the ID of the texture object,
    // used for all texture operations to reference to this particlar texture
    unsigned int ID;

    // texture image dimensions
    unsigned int m_width, m_height; // width and height of loaded image in pixels

    // texture Format
    unsigned int m_internal_format; // format of texture object
    unsigned int m_image_format; // format of loaded image

    // texture configuration
    unsigned int m_wrap_S; // wrapping mode on S axis
    unsigned int m_wrap_T; // wrapping mode on T axis
    unsigned int m_filter_min; // filtering mode if texture pixels < screen pixels
    unsigned int m_filter_max; // filtering mode if texture pixels > screen pixels

    // constructor (sets default texture modes)
    Texture2D();
    // generates texture from image data
    void generate(unsigned int width, unsigned int height, unsigned char* data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void bind() const;
};
