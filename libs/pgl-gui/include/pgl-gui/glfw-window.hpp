#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <any>
#include <string>

namespace pgl {
  namespace gui {

    class GLFWWindow {
			public:
				static auto make_window(
					int width, int height,
					const char* name
				) -> GLFWWindow&;
				bool is_open();
				void poll_events();
				void swap_buffer();
				void clear(float r, float g, float b, float a);

				static void set_user_pointer(std::any ptr);
				static void set_cursor_cb(void (*fun)(GLFWwindow*, double, double));
				static void set_key_cb(void (*fun)(GLFWwindow*, int, int, int, int));
				static void set_mouse_button_cb(
					void (*fun)(GLFWwindow* window, int button, int action, int mods)
				);
				~GLFWWindow();

			private:
				int width, height;
				static GLFWwindow* window;

				static void key_callback(
					GLFWwindow* window,
					int key, int scancode,
					int action, int mode
				);

				static void framebuffer_size_callback(
					GLFWwindow* window,
					int width, int height
				);

				static void cursor_position_callback(
					GLFWwindow* window,
					double xpos, double ypos
				);
				GLFWWindow(int width, int height, const std::string& name);
    };

  } /* end of namespace gui */
} /* end of namespace pgl */
