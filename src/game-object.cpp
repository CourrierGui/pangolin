#include <pangolin/game-object.hpp>

namespace pgl {

GameObject::GameObject()
  : position(0.0f, 0.0f), size(1.0f, 1.0f),
  velocity(0.0f), color(1.0f), rotation(0.0f),
  sprite(), is_solid(false), destroyed(false)
{

}

GameObject::GameObject(
  const glm::vec2& pos, const glm::vec2& size,
  resources::Texture2D& sprite, const glm::vec3& color,
  const glm::vec2& velocity)
  :
    position(pos), size(size),
    velocity(velocity), color(color),
    rotation(0.0f), sprite(sprite),
    is_solid(false), destroyed(false) { }

void GameObject::draw(render2D::SpriteRenderer& renderer) {
  renderer.draw(sprite, position, size, rotation, color);
}

} /* end of namespace pgl */
