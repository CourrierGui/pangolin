#include <iostream>

#include <pgl-core/text-renderer.hpp>
#include <pgl-core/resource-manager.hpp>
#include <pgl-math/impl/algorithms.hpp>
#include <pgl-tools/logger.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H


namespace pgl::gui {

        TextRenderer::TextRenderer(unsigned int width,
                                   unsigned int height,
                                   shader& shader) :
            text_shader(shader)
        {

            text_shader.use();
            text_shader.setvalue("projection",
                                 pgl::ortho(0.0f, static_cast<float>(width),
                                            static_cast<float>(height), 0.0f)
                                );
            text_shader.setvalue("text", 0);

            // configure VAO/VBO for texture quads
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void TextRenderer::load(const std::string& font,
                                unsigned int fontSize)
        {
            // first clear the previously loaded characters
            characters.clear();

            // then initialize and load the FreeType library
            FT_Library ft;

            // all functions return a value different than 0 whenever an error occurred
            if (FT_Init_FreeType(&ft))
                pgl::error() << "Could not init FreeType library\n";

            // load font as face
            FT_Face face;
            if (FT_New_Face(ft, font.c_str(), 0, &face))
                pgl::error() << "Failed to load font\n";

            // set size to load glyphs as
            FT_Set_Pixel_Sizes(face, 0, fontSize);

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // then for the first 128 ASCII characters, pre-load/compile their characters
            // and store them
            for (GLubyte c = 0; c < 128; c++) {
                // load character glyph
                if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                    pgl::error() << "Failed to load Glyph\n";
                    continue;
                }

                // generate texture
                unsigned int texture;
                glGenTextures(1, &texture);
                glBindTexture(GL_TEXTURE_2D, texture);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RED,
                             face->glyph->bitmap.width,
                             face->glyph->bitmap.rows,
                             0, GL_RED, GL_UNSIGNED_BYTE,
                             face->glyph->bitmap.buffer);

                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                // now store character for later use
                Character character = {
                    texture,
                    pgl::int2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    pgl::int2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    face->glyph->advance.x
                };
                characters.insert({ c, character });
            }
            glBindTexture(GL_TEXTURE_2D, 0);
            // destroy FreeType once we're finished
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
        }

        void TextRenderer::render_text(const std::string& text,
                                       float x, float y, float scale,
                                       pgl::float3 color)
        {
            // activate corresponding render state
            text_shader.use();
            text_shader.setvalue("textColor", color);
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(VAO);

            // iterate through all characters
            std::string::const_iterator c;
            for (c = text.begin(); c != text.end(); c++) {
                Character ch = characters[*c];

                float xpos = x + ch.bearing.x * scale;
                float ypos = y + (characters['H'].bearing.y - ch.bearing.y) * scale;

                float w = ch.size.x * scale;
                float h = ch.size.y * scale;
                // update VBO for each character
                float vertices[6][4] = {
                    { xpos,     ypos + h,   0.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 0.0f },
                    { xpos,     ypos,       0.0f, 0.0f },

                    { xpos,     ypos + h,   0.0f, 1.0f },
                    { xpos + w, ypos + h,   1.0f, 1.0f },
                    { xpos + w, ypos,       1.0f, 0.0f }
                };
                // render glyph texture over quad
                glBindTexture(GL_TEXTURE_2D, ch.texture_id);

                // update content of VBO memory
                glBindBuffer(GL_ARRAY_BUFFER, VBO);

                // be sure to use glBufferSubData and not glBufferData
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                // render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);

                // now advance cursors for next glyph
                // bitshift by 6 to get value in pixels (1/64th times 2^6 = 64)
                x += (ch.advance >> 6) * scale;
            }
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

} /* end of namespace pgl::gui */
