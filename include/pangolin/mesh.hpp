#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glad/glad.h>

#include <pangolin/shader.hpp>
#include <iostream>

namespace pgl {
  namespace render3D {

struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 tex_coords;
};

struct Texture {
  unsigned int id;
  std::string type; //TODO: use enum type instead
  std::string name;
};

bool operator==(const Texture& a, const Texture& b);

class Mesh {
  public:
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(const std::vector<Vertex>&       vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<Texture>&      textures
    );
    void draw(resources::Shader& shader);

  private:
    unsigned int VBO, VAO, EBO;
    void setup_mesh();
};

  } /* end of namespace render3D */
} /* end of namespace pgl */
