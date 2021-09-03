#include <pgl-core/particle-generator.hpp>

namespace pgl {

    ParticleGenerator::ParticleGenerator(shader&      shader,
                                         Texture2D&   texture,
                                         unsigned int amount) :
        _particles{}, _amount(amount),
        _shader(shader), _texture(texture), _vao{}
    {
        init();
    }

    void ParticleGenerator::update(float dt, GameObject &object,
                                   unsigned int new_particles,
                                   const pgl::float2& offset)
    {
        // add new particles
        for (unsigned int i = 0; i < new_particles; ++i) {
            int unused_particle = first_unused_particle();
            respawn_particle(_particles[unused_particle], object, offset);
        }
        // update all particles
        for (unsigned int i = 0; i < _amount; ++i) {
            Particle& p = _particles[i];
            p.life -= dt; // reduce life
            if (p.life > 0.0f) { // particle is alive, thus update
                p.position -= p.velocity * dt;
                p.color.x -= dt * 2.5f; //TODO p.color.a
            }
        }
    }

    void ParticleGenerator::update(float dt, GameObject &object,
                                   unsigned int new_particles)
    {
        // add new particles
        for (unsigned int i = 0; i < new_particles; ++i) {
            int unused_particle = first_unused_particle();
            respawn_particle(_particles[unused_particle], object);
        }
        // update all particles
        for (unsigned int i = 0; i < _amount; ++i) {
            Particle& p = _particles[i];
            p.life -= dt; // reduce life
            if (p.life > 0.0f) { // particle is alive, thus update
                p.position -= p.velocity * dt;
                p.color.x -= dt * 2.5f; //TODO p.color.a
            }
        }
    }

    void ParticleGenerator::draw() {
        // use additive blending to give it a 'glow' effect
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
        _shader.use();
        for (Particle particle : _particles) {
            if (particle.life > 0.0f) {
                _shader.setvalue("offset", particle.position);
                _shader.setvalue("color", particle.color);
                _texture.bind();

                glBindVertexArray(_vao);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);
            }
        }
        // don't forget to reset to default blending mode
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void ParticleGenerator::init()
    {
        // set up mesh and attribute properties
        float particle_quad[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };
        unsigned int vbo;

        glGenVertexArrays(1, &_vao);
        glGenBuffers(1, &vbo);
        glBindVertexArray(_vao);

        // fill mesh buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);

        // set mesh attributes
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glBindVertexArray(0);

        // create this->amount default particle instances
        for (unsigned int i = 0; i < _amount; ++i)
            _particles.push_back(Particle());
    }

    unsigned int ParticleGenerator::last_used_particle = 0;

    unsigned int ParticleGenerator::first_unused_particle()
    {
        // first search from last used particle, this will usually return almost
        // instantly
        for (unsigned int i = last_used_particle; i < _amount; ++i) {
            if (_particles[i].life <= 0.0f){
                last_used_particle = i;
                return i;
            }
        }

        // otherwise, do a linear search
        for (unsigned int i = 0; i < last_used_particle; ++i){
            if (_particles[i].life <= 0.0f){
                last_used_particle = i;
                return i;
            }
        }

        // all particles are taken, override the first one (note that if it
        // repeatedly hits this case, more particles should be reserved)
        last_used_particle = 0;
        return 0;
    }

    void ParticleGenerator::respawn_particle(Particle&   particle,
                                             GameObject& object,
                                             const pgl::float2&  offset)
    {
        float random      = ((rand() % 100) - 50) / 10.0f;
        float color       = 0.5f + ((rand() % 100) / 100.0f);

        particle.position = object.position + random + offset;
        particle.color    = pgl::float4(color, color, color, 1.0f);
        particle.life     = 1.0f;
        particle.velocity = object.velocity * 0.1f;
    }

    void ParticleGenerator::respawn_particle(Particle&   particle,
                                             GameObject& object)
    {
        float random = ((rand() % 100) - 50) / 10.0f;
        float color = 0.5f + ((rand() % 100) / 100.0f);

        particle.position = object.position + random;
        particle.color    = pgl::float4(color, color, color, 1.0f);
        particle.life     = 1.0f;
        particle.velocity = object.velocity * 0.1f;
    }

} /* end of namespace pgl */
