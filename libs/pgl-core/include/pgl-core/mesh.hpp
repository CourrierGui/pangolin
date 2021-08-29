#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>

#include <pgl-core/shader.hpp>
#include <iostream>

namespace pgl {
    namespace _3D {

        struct vertex {
            pgl::float3 position{};
            pgl::float3 normal{};
            pgl::float2 tex_coords{};
        };

        struct texture {
            unsigned int id = 0;
            enum class _type { diffuse, specular } type;
            std::string name{};
        };

        bool operator==(const texture& a, const texture& b);

        class mesh {
            public:
                std::vector<vertex>       _vertices;
                std::vector<unsigned int> _indices;
                std::vector<texture>      _textures;

                mesh(const std::vector<vertex>&      vertices,
                     const std::vector<unsigned int>& indices,
                     const std::vector<texture>&      textures);
                void draw(Shader& shader);

            private:
                unsigned int VBO, VAO, EBO;
                void setup_mesh();
        };

    } /* end of namespace _3D */
} /* end of namespace pgl */
