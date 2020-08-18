#pragma once

#include <glad/glad.h>
#include <pgl-image/image-loader.hpp>

namespace pgl {


    /* Texture2D is able to store and configure a texture in OpenGL.
     * It also hosts utility functions for easy management.
     */
    class Texture2D {
      public:
        // holds the ID of the texture object,
        // used for all texture operations to reference to this particlar texture
        unsigned int id;

        // texture image dimensions
        unsigned int width, height; // width and height of loaded image in pixels

        // texture Format
        unsigned int internal_format; // format of texture object
        unsigned int image_format; // format of loaded image

        // texture configuration
        unsigned int wrap_S; // wrapping mode on S axis
        unsigned int wrap_T; // wrapping mode on T axis
        unsigned int filter_min; // filtering mode if texture pixels < screen pixels
        unsigned int filter_max; // filtering mode if texture pixels > screen pixels

        // constructor (sets default texture modes)
        Texture2D();
        // generates texture from image data
        void generate(const Image& image);
        // binds the texture as the current active GL_TEXTURE_2D texture object
        void bind() const;
    };

} /* end of namespace pgl */
