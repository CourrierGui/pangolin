#pragma once

#include <pangolin/shader.hpp>
#include <pangolin/texture.hpp>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace pgl {
  namespace render2D {

class SpriteRenderer {
  public:
    SpriteRenderer(loader::Shader& shader);
    ~SpriteRenderer();

    void draw(
      loader::Texture2D& texture, const glm::vec2& position,
      const glm::vec2& size, float rotate, const glm::vec3& color
    );
    void draw(
      loader::Texture2D& texture, const glm::vec2& position,
      const glm::vec2& size, float rotate
    );
    void draw(
      loader::Texture2D& texture, const glm::vec2& position, const glm::vec2& size
    );
    void draw(
      loader::Texture2D& texture, const glm::vec2& position
    );

  private:
    loader::Shader       shader;
    unsigned int quad_vao;

    void init_render_data();
};

  } /* end of namespace render2D */
} /* end of namespace pgl */
