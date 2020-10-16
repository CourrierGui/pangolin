#pragma once

#include <pangolin/shader.hpp>
#include <pangolin/texture.hpp>

#include <glad/glad.h>

namespace pgl {
	namespace render2D {

		class SpriteRenderer {
			public:
				SpriteRenderer(Shader& shader);
				~SpriteRenderer();

				void draw(
					Texture2D& texture, const pgl::float2& position,
					const pgl::float2& size, float rotate, const pgl::float3& color
				);
				void draw(
					Texture2D& texture, const pgl::float2& position,
					const pgl::float2& size, float rotate
				);
				void draw(
					Texture2D& texture, const pgl::float2& position, const pgl::float2& size
				);
				void draw(
					Texture2D& texture, const pgl::float2& position
				);

			private:
				void init_render_data();

				Shader       shader;
				unsigned int quad_vao;
		};

	} /* end of namespace render2D */
} /* end of namespace pgl */
