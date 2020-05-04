#include <pangolin/particle-generator.hpp>

ParticleGenerator::ParticleGenerator(
  Shader&      shader,
  Texture2D&   texture,
  unsigned int amount) :
  shader(shader),
  texture(texture),
  amount(amount)
{
  init();
}

void ParticleGenerator::update(
  float dt, GameObject &object,
  unsigned int new_particles,
  glm::vec2& offset)
{
  // add new particles
  for (unsigned int i = 0; i < new_particles; ++i) {
    int unused_particle = first_unused_particle();
    respawn_particle(particles[unused_particle], object, offset);
  }
  // update all particles
  for (unsigned int i = 0; i < amount; ++i) {
    Particle& p = particles[i];
    p.life -= dt; // reduce life
    if (p.life > 0.0f) { // particle is alive, thus update
      p.position -= p.velocity * dt;
      p.color.a -= dt * 2.5f;
    }
  }
}

void ParticleGenerator::update(
  float dt, GameObject &object,
  unsigned int new_particles)
{
  // add new particles
  for (unsigned int i = 0; i < new_particles; ++i) {
    int unused_particle = first_unused_particle();
    respawn_particle(particles[unused_particle], object);
  }
  // update all particles
  for (unsigned int i = 0; i < amount; ++i) {
    Particle& p = particles[i];
    p.life -= dt; // reduce life
    if (p.life > 0.0f) { // particle is alive, thus update
      p.position -= p.velocity * dt;
      p.color.a -= dt * 2.5f;
    }
  }
}

void ParticleGenerator::draw() {
  // use additive blending to give it a 'glow' effect
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);
  shader.use();
  for (Particle particle : particles) {
    if (particle.life > 0.0f) {
      shader.setVector2f("offset", particle.position);
      shader.setVector4f("color", particle.color);
      texture.bind();

      glBindVertexArray(vao);
      glDrawArrays(GL_TRIANGLES, 0, 6);
      glBindVertexArray(0);
    }
  }
  // don't forget to reset to default blending mode
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void ParticleGenerator::init() {
  // set up mesh and attribute properties
  unsigned int vbo;
  float particle_quad[] = {
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f,

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
  };
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glBindVertexArray(vao);
  // fill mesh buffer
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
  // set mesh attributes
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindVertexArray(0);

  // create this->amount default particle instances
  for (unsigned int i = 0; i < amount; ++i)
    particles.push_back(Particle());
}

unsigned int ParticleGenerator::last_used_particle = 0;

unsigned int ParticleGenerator::first_unused_particle() {
  // first search from last used particle, this will usually return almost
  // instantly
  for (unsigned int i = last_used_particle; i < amount; ++i) {
    if (particles[i].life <= 0.0f){
      last_used_particle = i;
      return i;
    }
  }
  // otherwise, do a linear search
  for (unsigned int i = 0; i < last_used_particle; ++i){
    if (particles[i].life <= 0.0f){
      last_used_particle = i;
      return i;
    }
  }

  // all particles are taken, override the first one (note that if it
  // repeatedly hits this case, more particles should be reserved)
  last_used_particle = 0;
  return 0;
}

void ParticleGenerator::respawn_particle(
  Particle&   particle,
  GameObject& object,
  glm::vec2&  offset)
{
  float random = ((rand() % 100) - 50) / 10.0f;
  float color = 0.5f + ((rand() % 100) / 100.0f);
  particle.position = object.position + random + offset;
  particle.color = glm::vec4(color, color, color, 1.0f);
  particle.life = 1.0f;
  particle.velocity = object.velocity * 0.1f;
}

void ParticleGenerator::respawn_particle(
  Particle&   particle,
  GameObject& object)
{
  float random = ((rand() % 100) - 50) / 10.0f;
  float color = 0.5f + ((rand() % 100) / 100.0f);

  particle.position = object.position + random;
  particle.color = glm::vec4(color, color, color, 1.0f);
  particle.life = 1.0f;
  particle.velocity = object.velocity * 0.1f;
}
