#pragma once

#include <vector>
#include <string>

#include <glad/glad.h>

#include <pangolin/shader.hpp>
#include <iostream>

namespace pgl {
	namespace render3D {

		struct Vertex {
			pgl::float3 position;
			pgl::float3 normal;
			pgl::float2 tex_coords;
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

				Mesh(
					const std::vector<Vertex>&       vertices,
					const std::vector<unsigned int>& indices,
					const std::vector<Texture>&      textures
					);
				void draw(Shader& shader);

			private:
				unsigned int VBO, VAO, EBO;
				void setup_mesh();
		};

	} /* end of namespace render3D */
} /* end of namespace pgl */
