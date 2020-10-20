#include <pgl-gui/glfw-window.hpp>

#include <functional>
#include <iostream>

using namespace std::placeholders;

namespace pgl {
	namespace gui {

		GLFWWindow& GLFWWindow::make_window(
			int width, int height,
			const char* name)
		{
			static GLFWWindow window(width, height, name);
			return window;
		}

		GLFWWindow::GLFWWindow(int width, int height, const char* name)
			: width(width), height(height)
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			glfwWindowHint(GLFW_RESIZABLE, false);

			window = glfwCreateWindow(
				width, height,
				name, nullptr, nullptr
			);
			glfwMakeContextCurrent(window);

			// glad: load all OpenGL function pointers
			// ---------------------------------------
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cerr << "Failed to initialize GLAD\n";
			}

			set_key_cb(
				[](GLFWwindow* window, int key, int, int action, int){
					if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
						glfwSetWindowShouldClose(window, true);
				}
			);
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

			// OpenGL configuration
			// --------------------
			glViewport(0, 0, width, height);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}

		bool GLFWWindow::is_open() {
			return !glfwWindowShouldClose(window);
		}

		GLFWWindow::~GLFWWindow() {
			glfwTerminate();
		}

		void GLFWWindow::clear() {
			//TODO: add background color
			glClearColor(0.4f, 0.4f, 0.4f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		void GLFWWindow::framebuffer_size_callback(
			GLFWwindow*,
			int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void GLFWWindow::poll_events() {
			glfwPollEvents();
		}

		void GLFWWindow::swap_buffer() {
			glfwSwapBuffers(window);
		}

		void GLFWWindow::set_key_cb(
			void (*fun)(GLFWwindow*, int, int, int, int))
		{
			glfwSetKeyCallback(window, fun);
		}

		void GLFWWindow::set_cursor_cb(
			void (*fun)(GLFWwindow*, double, double))
		{
			glfwSetCursorPosCallback(window, fun);
		}

		void GLFWWindow::set_mouse_button_cb(
			void (*fun)(GLFWwindow* window, int button, int action, int mods))
		{
			glfwSetMouseButtonCallback(window, fun);
		}

		void GLFWWindow::set_user_pointer(std::any ptr) {
			glfwSetWindowUserPointer(window, std::any_cast<void*>(ptr));
		}

		GLFWwindow* GLFWWindow::window = nullptr;

	} /* end of namespace gui */
} /* end of namespace pgl */
