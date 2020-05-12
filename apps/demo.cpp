#include <pangolin/game-object.hpp>
#include <pangolin/text-renderer.hpp>
#include <pangolin/resource-manager.hpp>

int main() {
  pgl::GameObject go;
  pgl::resources::Shader shader
    = pgl::resources::ResourceManager::load_shader("", "", "", "");
  return 0;
}
