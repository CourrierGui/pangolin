#pragma once

#include <pgl-core/texture.hpp>
#include <pgl-core/sprite-renderer.hpp>
#include <pgl-core/shader.hpp>

#include <iostream>

namespace pgl {

    class PostProcessor {
        public:
            // state
            shader    _shader;
            Texture2D _texture;
            unsigned int _width, _height;
            // options
            bool confuse, chaos, shake;
            // constructor
            PostProcessor(shader& s, unsigned int width, unsigned int height);
            // prepares the postprocessor's framebuffer operations before rendering the game
            void begin_render();
            // should be called after rendering the game, so it stores all the
            // rendered data into a texture object
            void end_render();
            // renders the PostProcessor texture quad (as a screen-encompassing large sprite)
            void render(float time);

        private:
            // render state
            // MSFBO = Multisampled FBO. FBO is regular,
            // used for blitting MS color-buffer to texture
            unsigned int _MSFBO, _FBO;
            unsigned int _RBO; // _RBO is used for multisampled color buffer
            unsigned int _VAO;

            // initialize quad for rendering postprocessing texture
            void init_render_data();
    };

} /* end of namespace pgl */
