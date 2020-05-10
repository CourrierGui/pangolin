#include <pangolin/sprite-renderer.hpp>

namespace pgl {
  namespace render2D {

SpriteRenderer::SpriteRenderer(resources::Shader& shader) : shader(shader){
  init_render_data();
}

SpriteRenderer::~SpriteRenderer() {
  glDeleteVertexArrays(1, &this->quad_vao);
}

void SpriteRenderer::init_render_data() {
  // configure VAO/VBO
  unsigned int VBO;
  float vertices[] = {
    // pos      // tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };

  glGenVertexArrays(1, &quad_vao);
  glGenBuffers(1, &VBO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(quad_vao);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void SpriteRenderer::draw(
  resources::Texture2D& texture,
  const glm::vec2& position,
  const glm::vec2& size,
  float      rotate,
  const glm::vec3& color)
{
  // prepare transformations
  shader.use();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));

  shader.setMatrix4("model", model);
  shader.setVector3f("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  texture.bind();

  glBindVertexArray(quad_vao);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void SpriteRenderer::draw(
  resources::Texture2D& texture,
  const glm::vec2& position,
  const glm::vec2& size,
  float      rotate)
{
  draw(texture, position, size, rotate, glm::vec3(1.0f));
}

void SpriteRenderer::draw(
  resources::Texture2D& texture,
  const glm::vec2& position,
  const glm::vec2& size)
{
  draw(texture, position, size, 0.0f, glm::vec3(1.0f));
}

void SpriteRenderer::draw(
  resources::Texture2D& texture,
  const glm::vec2& position)
{
  draw(texture, position, glm::vec2(10.0f, 10.0f), 0.0f, glm::vec3(1.0f));
}

  } /* end of namespace render2D */
} /* end of namespace pgl */
