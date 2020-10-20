#include <pgl-gui/glfw-window.hpp>

int main() {
	auto& window = pgl::gui::GLFWWindow::make_window(600, 400, "Pangolin demo");

	//TODO make this independant of GLFW
	window.set_key_cb(
		[](GLFWwindow* window, int key, int, int action, int){
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
				glfwSetWindowShouldClose(window, true);
		}
	);

	while (window.is_open()) {
		window.poll_events();
		window.clear(0.4f, 0.4f, 0.4f, 1.0f);

		window.swap_buffer();
	}

	return 0;
}
