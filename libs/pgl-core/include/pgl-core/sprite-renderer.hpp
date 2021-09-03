#pragma once

#include <pgl-core/shader.hpp>
#include <pgl-core/texture.hpp>

#include <glad/glad.h>

namespace pgl {
    namespace render2D {

        class SpriteRenderer {
            public:
                SpriteRenderer(shader& shader);
                ~SpriteRenderer();

                void draw(Texture2D& texture, const pgl::float2& position,
                          const pgl::float2& size, float rotate, const pgl::float3& color);

                void draw(Texture2D& texture, const pgl::float2& position,
                          const pgl::float2& size, float rotate);

                void draw(Texture2D& texture, const pgl::float2& position, const pgl::float2& size);
                void draw(Texture2D& texture, const pgl::float2& position);

            private:
                void init_render_data();

                shader       _shader;
                unsigned int _quadvao;
        };

    } /* end of namespace render2D */
} /* end of namespace pgl */
