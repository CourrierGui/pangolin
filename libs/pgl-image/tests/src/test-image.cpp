#include <pgl-image/image-loader.hpp>

int main() {
  pgl::loader::load_png("../tests/resources/awesomeface.png");
  pgl::loader::load_png("../tests/resources/paddle.png");
}
