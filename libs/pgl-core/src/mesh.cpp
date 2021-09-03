#include <pgl-core/mesh.hpp>

namespace pgl {
    namespace _3D {

        mesh::mesh(const std::vector<vertex>&       vertices,
                   const std::vector<unsigned int>& indices,
                   const std::vector<texture>&      textures) :
            _vertices{vertices}, _indices{indices}, _textures{textures}
        {
            setup_mesh();
        }

        void mesh::setup_mesh()
        {
            glGenVertexArrays(1, &VAO);
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(vertex),
                         &_vertices[0], GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int),
                         &_indices[0], GL_STATIC_DRAW);

            //vertex position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);

            // vertex normals
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                                  sizeof(vertex),
                                  (void*)offsetof(vertex, normal));

            // vertex texture coords
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                                  sizeof(vertex),
                                  (void*)offsetof(vertex, tex_coords));
            glBindVertexArray(0);
        }

        void mesh::draw(shader& shader)
        {
            std::size_t diffuse_index = 1;
            std::size_t specular_index = 1;

            for (std::size_t i = 0; i < _textures.size(); ++i) {
                glActiveTexture(GL_TEXTURE0 + i);
                std::string name;

                if (_textures[i].type == texture::_type::diffuse)
                    name = "texture_diffuse" + std::to_string(diffuse_index++);
                if (_textures[i].type == texture::_type::diffuse)
                    name = "texture_specular" + std::to_string(specular_index++);

                shader.setvalue(("material." + name).c_str(), (float)i);
                glBindTexture(GL_TEXTURE_2D, _textures[i].id);
            }

            glActiveTexture(GL_TEXTURE0);

            // draw mesh
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        }

    } /* end of namespace _3D */
} /* end of namespace pgl */
