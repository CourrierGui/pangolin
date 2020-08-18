#include <pangolin/mesh.hpp>

namespace pgl {
	namespace render3D {

		Mesh::Mesh(
			const std::vector<Vertex>&       vertices,
			const std::vector<unsigned int>& indices,
			const std::vector<Texture>&      textures)
			: vertices(vertices), indices(indices), textures(textures)
		{
			setup_mesh();
		}

		void Mesh::setup_mesh() {
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glGenBuffers(1, &EBO);

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int),
									 &indices[0], GL_STATIC_DRAW);

			//vertex position
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
			// vertex normals
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
														sizeof(Vertex), (void*)offsetof(Vertex, normal));
			// vertex texture coords
			glEnableVertexAttribArray(2);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
														sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
			glBindVertexArray(0);
		}

		void Mesh::draw(Shader& shader) {
			unsigned int diffuse_index;
			unsigned int specular_index;

			for (unsigned int i=0; i<textures.size(); ++i) {
				glActiveTexture(GL_TEXTURE0 + i);
				std::string name = textures[i].type;

				if (name == "texture_diffuse")
					name += std::to_string(diffuse_index++);
				if (name == "texture_specular")
					name += std::to_string(specular_index++);

				shader.setFloat(("material." + name).c_str(), (float)i);
				glBindTexture(GL_TEXTURE_2D, textures[i].id);
			}
			glActiveTexture(GL_TEXTURE0);

			// draw mesh
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

	} /* end of namespace render3d */
} /* end of namespace pgl */
