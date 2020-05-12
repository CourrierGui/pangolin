#include <pangolin/game-object.hpp>
#include <pangolin/text-renderer.hpp>
#include <pangolin/resource-manager.hpp>

int main() {
  pgl::GameObject go;
  pgl::loader::Shader shader
    = pgl::loader::ResourceManager::load_shader("", "", "", "");
  return 0;
}
