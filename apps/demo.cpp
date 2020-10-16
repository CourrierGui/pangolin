#include <pgl-gui/glfw-window.hpp>

int main() {
	auto& window = pgl::gui::GLFWWindow::make_window(600, 400, "Pangolin demo");

	while (window.is_open()) {
		window.poll_events();
		window.clear();

		window.swap_buffer();
	}

  return 0;
}
