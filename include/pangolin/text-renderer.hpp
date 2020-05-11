#pragma once

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <pangolin/texture.hpp>
#include <pangolin/shader.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace pgl {
  namespace text {

/**
 * Holds all state information relevant to a character as loaded using
 * FreeType
 */
struct Character {
  unsigned int texture_id; // ID handle of the glyph texture
  glm::ivec2   size;       // size of glyph
  glm::ivec2   bearing;    // offset from baseline to left/top of glyph
  FT_Pos       advance;    // horizontal offset to advance to next glyph
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
    resources::Shader text_shader;

    // constructor
    TextRenderer(unsigned int width, unsigned int height);

    // pre-compiles a list of characters from the given font
    void load(const std::string& font, unsigned int fontSize);

    // renders a string of text using the precompiled list of characters
    void render_text(
      const std::string& text,
      float x, float y, float scale,
      glm::vec3 color=glm::vec3(1.0f)
    );

  private:
    // render state
    unsigned int VAO, VBO;
};

  } /* end of namespace text */
} /* end of namespace pgl */
