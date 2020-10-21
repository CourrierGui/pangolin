#include <pgl-gui/glfw-window.hpp>

#include <array>

int main() {
	auto window = pgl::gui::GLFWWindow(600, 400, "Pangolin demo");

	std::array<float,4> backgroundColor = {0.4f, 0.4f, 0.4f, 1.0f};

	window.set_key_cb(
		[&backgroundColor](pgl::gui::GLFWWindow& window, int key, int, int action, int){
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				window.close();

			} else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
				backgroundColor = { 0.6f, 0.3f, 0.3f, 1.0f };
			}
		}
	);

	while (window.is_open()) {
		window.poll_events();
		window.clear(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);

		window.swap_buffer();
	}

	return 0;
}
