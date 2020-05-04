#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <pangolin/texture.hpp>
#include <pangolin/sprite-renderer.hpp>


/**
 * Container object for holding all state relevant for a single
 * game object entity. Each object in the game likely needs the
 * minimal of state as described within GameObject.
 */

class GameObject {
  public:
    // object state
    glm::vec2   m_position, m_size, m_velocity;
    glm::vec3   m_color;
    float       m_rotation;
    bool        m_isSolid;
    bool        m_destroyed;

    // render state
    Texture2D   m_sprite;	

    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite,
               glm::vec3 color=glm::vec3(1.0f), glm::vec2 velocity=glm::vec2(0.0f, 0.0f));
    // draw sprite
    virtual void draw(SpriteRenderer &renderer);
};
