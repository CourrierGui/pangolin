#include <pgl-core/sprite-renderer.hpp>
#include <pgl-math/algorithms.hpp>

namespace pgl {
	namespace render2D {

		SpriteRenderer::SpriteRenderer(Shader& shader) : shader(shader){
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
			Texture2D& texture,
			const pgl::float2& position,
			const pgl::float2& size,
			float              rotate,
			const pgl::float3& color)
		{
			// prepare transformations
			shader.use();
			pgl::float44 model = pgl::float44{1.0f};
			model = pgl::translate(model, pgl::float3(position, 0.0f));

			model = pgl::translate(model, pgl::float3(0.5f * size, 0.0f));
			model = pgl::rotate(model, pgl::radians(rotate), pgl::float3(0.0f, 0.0f, 1.0f));
			model = pgl::translate(model, pgl::float3(-0.5f * size, 0.0f));

			model = pgl::scale(model, pgl::float3(size, 1.0f));

			shader.setMatrix4("model", model);
			shader.setVector3f("spriteColor", color);

			glActiveTexture(GL_TEXTURE0);
			texture.bind();

			glBindVertexArray(quad_vao);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}

		void SpriteRenderer::draw(
			Texture2D&         texture,
			const pgl::float2& position,
			const pgl::float2& size,
			float              rotate)
		{
			draw(texture, position, size, rotate, pgl::float3(1.0f));
		}

		void SpriteRenderer::draw(
			Texture2D& texture,
			const pgl::float2& position,
			const pgl::float2& size)
		{
			draw(texture, position, size, 0.0f, pgl::float3(1.0f));
		}

		void SpriteRenderer::draw(
			Texture2D& texture,
			const pgl::float2& position)
		{
			draw(texture, position, pgl::float2(10.0f, 10.0f), 0.0f, pgl::float3(1.0f));
		}

	} /* end of namespace render2D */
} /* end of namespace pgl */
