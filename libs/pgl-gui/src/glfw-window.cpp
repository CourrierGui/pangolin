#include <pgl-gui/glfw-window.hpp>

#include <functional>
#include <iostream>

using namespace std::placeholders;

namespace pgl {
  namespace gui {

    GLFWWindow::GLFWWindow(int width, int height, const std::string& name)
      : width(width), height(height), _callbacks{}
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
      glfwSetWindowUserPointer(window, reinterpret_cast<void*>(this));

      /* glad: load all OpenGL function pointers */
      if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD\n");
      }

      _callbacks._framebufferSizeCb = [](GLFWwindow*, int width, int height)
        -> void
        {
          glViewport(0, 0, width, height);
        };
      glfwSetFramebufferSizeCallback(window, _callbacks._framebufferSizeCb);

      /* OpenGL configuration */
      glViewport(0, 0, width, height);
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    bool GLFWWindow::is_open() {
      return !glfwWindowShouldClose(window);
    }

    void GLFWWindow::close() {
      glfwSetWindowShouldClose(window, true);
    }

    GLFWWindow::~GLFWWindow() {
      glfwTerminate();
    }

    void GLFWWindow::clear(float r, float g, float b, float a) {
      glClearColor(r, g, b, a);
      glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLFWWindow::poll_events() {
      glfwPollEvents();
    }

    void GLFWWindow::swap_buffer() {
      glfwSwapBuffers(window);
    }

    void GLFWWindow::set_key_cb(
      const std::function<void(GLFWWindow&,int,int,int,int)>& fun)
    {
      _callbacks._keyCb = fun;
      auto cb = [](GLFWwindow* window,int key, int scancode, int action, int mods)
        -> void
        {
          GLFWWindow* _window = reinterpret_cast<GLFWWindow*>(
            glfwGetWindowUserPointer(window));
          if (_window) {
            _window->keyCallback()(*_window, key, scancode, action, mods);
          }
        };
      glfwSetKeyCallback(window, cb);
    }

    void GLFWWindow::set_cursor_cb(
      const std::function<void(GLFWWindow&,double,double)>& fun)
    {
      _callbacks._cursorPosCb = fun;
      auto cb = [](GLFWwindow* window, double xpos, double ypos)
        -> void
        {
          GLFWWindow* _window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
          if (_window) {
            _window->mousePositionCallback()(*_window, xpos, ypos);
          }
        };
      glfwSetCursorPosCallback(window, cb);
    }

    void GLFWWindow::set_mouse_button_cb(
      const std::function<void(GLFWWindow&,int,int,int)>& fun)
    {
      _callbacks._mouseButtonCb = fun;
      auto cb = [](GLFWwindow* window, int button, int action, int mods)
        -> void
        {
          GLFWWindow* _window = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
          if (_window) {
            _window->mouseButtonCallback()(*_window, button, action, mods);
          }
        };
      glfwSetMouseButtonCallback(window, cb);
    }

    GLFWwindow* GLFWWindow::window = nullptr;

    auto GLFWWindow::mousePositionCallback()
      -> std::function<void(GLFWWindow&,double,double)>&
      {
        return _callbacks._cursorPosCb;
      }

    auto GLFWWindow::keyCallback()
      -> std::function<void(GLFWWindow&,int,int,int,int)>&
      {
        return _callbacks._keyCb;
      }

    auto GLFWWindow::mouseButtonCallback()
      -> std::function<void(GLFWWindow&,int,int,int)>&
      {
        return _callbacks._mouseButtonCb;
      }

  } /* end of namespace gui */
} /* end of namespace pgl */
