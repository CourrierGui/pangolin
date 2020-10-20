#include <pgl-gui/glfw-window.hpp>

#include <functional>
#include <iostream>

using namespace std::placeholders;

namespace pgl {
	namespace gui {

		auto GLFWWindow::make_window(
			int width, int height,
			const char* name)
			-> GLFWWindow&
		{
			static GLFWWindow window(width, height, name);
			return window;
		}

		GLFWWindow::GLFWWindow(int width, int height, const std::string& name)
			: width(width), height(height)
		{
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_RESIZABLE, false);

			window = glfwCreateWindow(
				width, height,
				name.c_str(), nullptr, nullptr
			);
			glfwMakeContextCurrent(window);

			/* glad: load all OpenGL function pointers */
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				throw std::runtime_error("Failed to initialize GLAD\n");
			}
			glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

			/* OpenGL configuration */
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

		void GLFWWindow::clear(float r, float g, float b, float a) {
			//TODO: add background color
			glClearColor(r, g, b, a);
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
