#include <pgl-gui/glfw-window.hpp>
#include <pgl-core/resource-manager.hpp>
#include <pgl-core/text-renderer.hpp>

#include <array>

int main() {
	constexpr uint32_t width = 600;
	constexpr uint32_t height = 600;

	auto window = pgl::gui::GLFWWindow(width, height, "Pangolin demo");
	pgl::ResourceManager::load_shader(
		"../resources/shader/text.vs",
		"../resources/shader/text.fs",
		"", "text");

	pgl::gui::TextRenderer renderer{width, height, pgl::ResourceManager::get_shader("text")};
	renderer.load("../resources/fonts/ocraext.TTF", 14);
	
	std::string text = "Hello World!";
	float x = width/2.0f;
	float y = height/2.0f;
	float xpos = x;
	float ypos = y;

	window.set_key_cb(
		[&text](pgl::gui::GLFWWindow& window, int key, int, int action, int){
			if (action != GLFW_PRESS) return;

			if (key == GLFW_KEY_ESCAPE) {
				window.close();

			} else if (key == GLFW_KEY_SPACE || (key >= GLFW_KEY_0 && key <= GLFW_KEY_Z)){
				//TODO handle keyboard layout
				//TODO handle modifiers
				text.push_back((char)key);

			} else if (key == GLFW_KEY_BACKSPACE) {
				text.pop_back();

			} else {
				std::clog << key << '\n';
			}
		}
	);

	window.set_mouse_button_cb(
		[&x, &y, &xpos, &ypos](pgl::gui::GLFWWindow& window, int button, int action, int mode)
		-> void
		{
			if (action != GLFW_PRESS) return;

			if (button == GLFW_MOUSE_BUTTON_LEFT) {
				x = xpos;
				y = ypos;
			}
		}
	);

	window.set_cursor_cb(
		[&xpos, &ypos](pgl::gui::GLFWWindow&, float x, float y)
		-> void
		{
			xpos = x;
			ypos = y;
		}
	);

	while (window.is_open()) {
		window.poll_events();
		window.clear(1.0f, 1.0f, 1.0f, 1.0f);

		renderer.render_text(text, x, y, 1.0f, pgl::float3{0.0f, 0.0f, 0.0f});

		window.swap_buffer();
	}

	return 0;
}
