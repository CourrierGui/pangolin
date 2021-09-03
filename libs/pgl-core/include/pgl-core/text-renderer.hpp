#pragma once

#include <map>

#include <glad/glad.h>

#include <pgl-core/texture.hpp>
#include <pgl-core/shader.hpp>

#include <pgl-math/impl/vector.hpp>

namespace pgl::gui {

        /**
         * Holds all state information relevant to a character as loaded using
         * FreeType
         */
        struct Character {
            uint32_t    texture_id; // ID handle of the glyph texture
            pgl::int2   size;       // size of glyph
            pgl::int2   bearing;    // offset from baseline to left/top of glyph
            signed long advance;    // horizontal offset to advance to next glyph
        };

        /**
         * A renderer class for rendering text displayed by a font loaded using the
         * FreeType library. A single font is loaded, processed into a list of
         * Character items for later rendering.
         */
        class TextRenderer {
            public:
                // holds a list of pre-compiled Characters
                std::map<char, Character> characters; 

                // shader used for text rendering
                shader text_shader;

                // constructor
                TextRenderer(unsigned int width, unsigned int height, shader& shader);

                // pre-compiles a list of characters from the given font
                void load(const std::string& font, unsigned int fontSize);

                // renders a string of text using the precompiled list of characters
                void render_text(const std::string& text,
                                 float x, float y, float scale,
                                 pgl::float3 color=pgl::float3{1.0f});

            private:
                // render state
                unsigned int VAO, VBO;
        };

} /* end of namespace pgl::gui */
