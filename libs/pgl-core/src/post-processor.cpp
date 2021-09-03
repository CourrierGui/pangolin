#include <pgl-core/post-processor.hpp>
#include <pgl-tools/logger.hpp>

namespace pgl {

    PostProcessor::PostProcessor(shader& shader, unsigned int width,
                                 unsigned int height) :
        _shader{shader}, _texture(), _width{width},
        _height{height}, confuse{false},
        chaos{false}, shake{false},
        _MSFBO{}, _FBO{}, _RBO{}, _VAO{}
    {
        // initialize renderbuffer/framebuffer object
        glGenFramebuffers(1, &_MSFBO);
        glGenFramebuffers(1, &_FBO);
        glGenRenderbuffers(1, &_RBO);

        // initialize renderbuffer storage with a multisampled color buffer (don't
        // need a depth/stencil buffer)
        glBindFramebuffer(GL_FRAMEBUFFER, _MSFBO);
        glBindRenderbuffer(GL_RENDERBUFFER, _RBO);

        // allocate storage for render buffer object
        glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_RGB, width, height);

        // attach MS render buffer object to framebuffer
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                  GL_RENDERBUFFER, _RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            pgl::error() << "Post Processor: failed to initialize MSFBO\n";

        // also initialize the FBO/texture to blit multisampled color-buffer to; used
        // for shader operations (for postprocessing effects)
        glBindFramebuffer(GL_FRAMEBUFFER, _FBO);
        //TODO: correct this with Image class
        /* texture.generate(width, height, nullptr); */

        // attach texture to framebuffer as its color attachment
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                               GL_TEXTURE_2D, _texture.id, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            pgl::error() << "Post Processor: failed to initialize FBO\n";

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        // initialize render data and uniforms
        init_render_data();
        _shader.use();
        _shader.setvalue("scene", 0);

        float offset = 1.0f / 300.0f;
        float offsets[9][2] = {
            { -offset,  offset  },  // top-left
            {  0.0f,    offset  },  // top-center
            {  offset,  offset  },  // top-right
            { -offset,  0.0f    },  // center-left
            {  0.0f,    0.0f    },  // center-center
            {  offset,  0.0f    },  // center - right
            { -offset, -offset  },  // bottom-left
            {  0.0f,   -offset  },  // bottom-center
            {  offset, -offset  }   // bottom-right
        };

        glUniform2fv(
            glGetUniformLocation(_shader.id, "offsets"),
            9, (float*)offsets
            );

        int edge_kernel[9] = {
            -1, -1, -1,
            -1,  8, -1,
            -1, -1, -1
        };

        glUniform1iv(glGetUniformLocation(_shader.id, "edge_kernel"), 9, edge_kernel);
        float blur_kernel[9] = {
            1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
            2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
            1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
        };
        glUniform1fv(glGetUniformLocation(_shader.id, "blur_kernel"), 9, blur_kernel);
    }

    void PostProcessor::begin_render() {
        glBindFramebuffer(GL_FRAMEBUFFER, _MSFBO);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void PostProcessor::end_render() {
        // now resolve multisampled color-buffer into intermediate FBO to store to
        // texture
        //
        glBindFramebuffer(GL_READ_FRAMEBUFFER, _MSFBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _FBO);
        glBlitFramebuffer(0, 0, _width, _height, 0, 0, _width, _height,
                          GL_COLOR_BUFFER_BIT, GL_NEAREST);

        // binds both READ and WRITE framebuffer to default framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void PostProcessor::render(float time) {
        // set uniforms/options
        _shader.use();
        _shader.setvalue("time", time);
        _shader.setvalue("confuse", confuse);
        _shader.setvalue("chaos", chaos);
        _shader.setvalue("shake", shake);
        // render textured quad
        glActiveTexture(GL_TEXTURE0);
        _texture.bind();
        glBindVertexArray(_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void PostProcessor::init_render_data() {
        // configure VAO/VBO
        float vertices[] = {
            // pos        // tex
            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f,  1.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f,

            -1.0f, -1.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 1.0f, 0.0f,
            1.0f,  1.0f, 1.0f, 1.0f
        };
        unsigned int VBO;
        glGenVertexArrays(1, &_VAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(_VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

} /* end of namespace pgl */
