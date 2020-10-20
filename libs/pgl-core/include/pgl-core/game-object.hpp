#pragma once

#include <glad/glad.h>

#include <pgl-core/texture.hpp>
#include <pgl-core/sprite-renderer.hpp>

#include <pgl-math/vector.hpp>

namespace pgl {

	/**
	 * Container object for holding all state relevant for a single
	 * game object entity. Each object in the game likely needs the
	 * minimal of state as described within GameObject.
	 */
	class GameObject {
		public:
			// object state
			pgl::float2 position, size, velocity;
			pgl::float3 color;
			float       rotation;
			bool        is_solid;
			bool        destroyed;

			// render state
			Texture2D   sprite;

			// constructor(s)
			GameObject();

			GameObject(
				const pgl::float2& pos, const pgl::float2& size, Texture2D& sprite,
				const pgl::float3& color=pgl::float3(1.0f),
				const pgl::float2& velocity=pgl::float2(0.0f, 0.0f)
			);

			virtual ~GameObject();

			// draw sprite
			virtual void draw(render2D::SpriteRenderer& renderer);
	};

} /* end of namespace pgl */
