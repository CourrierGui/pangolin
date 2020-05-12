#include <pangolin/game-object.hpp>
#include <pangolin/text-renderer.hpp>
#include <pangolin/resource-manager.hpp>

int main() {
  pgl::GameObject go;
  pgl::text::TextRenderer tr(400, 800);
  tr.load("", 10);
  pgl::resources::Shader shader
    = pgl::resources::ResourceManager::load_shader("", "", "", "");
  return 0;
}
