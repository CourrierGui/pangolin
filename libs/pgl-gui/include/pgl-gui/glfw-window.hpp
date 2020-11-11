#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <any>
#include <string>
#include <functional>

namespace pgl {
  namespace gui {

		class GLFWWindow;

		class GLFWCallbacks {
			public:
				std::function<void(GLFWWindow&,int,int,int)>     _mouseButtonCb;
				std::function<void(GLFWWindow&,double,double)>   _cursorPosCb;
				std::function<void(GLFWWindow&,int,int,int,int)> _keyCb;

				void (*_framebufferSizeCb)(GLFWwindow*,int,int);
		};

    class GLFWWindow {
			public:
				GLFWWindow(int width, int height, const std::string& name);
				bool is_open();
				void close();
				void poll_events();
				void swap_buffer();
				void clear(float r, float g, float b, float a);

				void set_cursor_cb(const std::function<void(GLFWWindow&,double, double)>& fun);
				void set_key_cb(const std::function<void(GLFWWindow&,int, int, int, int)>& fun);
				void set_mouse_button_cb(const std::function<void(GLFWWindow&,int,int,int)>& fun);

				auto mousePositionCallback() -> std::function<void(GLFWWindow&,double,double)>&;
				auto keyCallback()           -> std::function<void(GLFWWindow&,int,int,int,int)>&;
				auto mouseButtonCallback()   -> std::function<void(GLFWWindow&,int,int,int)>&;

				~GLFWWindow();

			private:
				int width, height;
				static GLFWwindow* window;
				GLFWCallbacks      _callbacks;

				void key_callback(
					GLFWwindow* window,
					int key, int scancode,
					int action, int mode
				);

				void framebuffer_size_callback(
					GLFWwindow* window,
					int width, int height
				);

				void cursor_position_callback(
					GLFWwindow* window,
					double xpos, double ypos
				);
    };

  } /* end of namespace gui */
} /* end of namespace pgl */
