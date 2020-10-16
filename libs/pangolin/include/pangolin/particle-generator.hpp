#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

#include <pangolin/shader.hpp>
#include <pangolin/texture.hpp>
#include <pangolin/game-object.hpp>
#include <pgl-math/vector.hpp>

namespace pgl {

	/*
	 * Represents a single particle and its state
	 * */
	struct Particle {
		pgl::float2 position, velocity;
		pgl::float4 color;
		float       life;

		Particle() : position(0.0f), velocity(0.0f), color(1.0f), life(0.0f) { }
	};

	/*
	 * ParticleGenerator acts as a container for rendering a large number of
	 * particles by repeatedly spawning and updating particles and killing
	 * them after a given amount of time.
	 */
	class ParticleGenerator {
		public:
			/* constructor */
			ParticleGenerator(Shader& shader, Texture2D& texture, unsigned int amount);

			/* update all particles */
			void update(
				float dt, GameObject& object, unsigned int new_particles, const pgl::float2& offset
			);

			void update(float dt, GameObject& object, unsigned int new_particles);

			/* render all particles */
			void draw();

		private:
			/* state */
			std::vector<Particle> particles;
			unsigned int          amount;

			/* render state */
			Shader       shader;
			Texture2D    texture;
			unsigned int vao;

			/*
			 * stores the index of the last particle used (for quick access to next
			 * dead particle)
			 */
			static unsigned int last_used_particle;

			/*
			 * initializes buffer and vertex attributes
			 */
			void init();

			/**
			 * returns the first Particle index that's currently unused e.g. Life <=
			 * 0.0f or 0 if no particle is currently inactive
			 */
			unsigned int first_unused_particle();

			/**
			 * respawns particle
			 */
			void respawn_particle(Particle& particle, GameObject& object, const pgl::float2& offset);
			void respawn_particle(Particle& particle, GameObject& object);
	};

} /* end of namespace pgl */
