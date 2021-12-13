#include <pgl-gui/glfw-window.hpp>

#include <functional>
#include <iostream>

#include <GLFW/glfw3.h>

using namespace std::placeholders;

namespace pgl::gui {

    void c_on_new_framebuffer(GLFWwindow *, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void c_on_press(GLFWwindow* gwindow, int key, int, int action, int)
    {
        if (action != GLFW_PRESS)
            return;

        auto *userdata = glfwGetWindowUserPointer(gwindow);
        auto *window = reinterpret_cast<GLFWWindow*>(userdata);
        pgl::key k;

        switch (key) {
            case GLFW_KEY_ESCAPE:
                k = key::escape;
                break;
            case GLFW_KEY_BACKSPACE:
                k = key::backspace;
                break;
            default:
                return;
        }

        if (window)
            window->on_press(*window, k);
    }

    void c_on_cursor_move(GLFWwindow* gwindow, double xpos, double ypos)
    {
        auto* userdata = glfwGetWindowUserPointer(gwindow);
        auto* window = reinterpret_cast<GLFWWindow*>(userdata);

        if (window)
            window->on_cursor_move(*window, xpos, ypos);
    }

    void c_on_click(GLFWwindow *gwindow, int button, int action, int)
    {
        auto *userdata = glfwGetWindowUserPointer(gwindow);
        auto *window = reinterpret_cast<GLFWWindow*>(userdata);

        if (action != GLFW_PRESS)
            return;

        if (window && button == GLFW_MOUSE_BUTTON_LEFT)
            window->on_click(*window, mouse::button_left);
    }

    void c_on_character(GLFWwindow *gwindow, unsigned int codepoint)
    {
        auto *userdata = glfwGetWindowUserPointer(gwindow);
        auto *window = reinterpret_cast<GLFWWindow *>(userdata);

        if (window)
            window->on_character(*window, static_cast<uint32_t>(codepoint));
    }

    GLFWWindow::GLFWWindow(int width, int height, const std::string& name) :
        on_click{}, on_press{}, on_cursor_move{}, on_character{},
        _width{width}, _height{height}, _window{nullptr}
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_RESIZABLE, false);

        _window = glfwCreateWindow(_width, _height,
                                  name.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(_window);
        glfwSetWindowUserPointer(_window, reinterpret_cast<void*>(this));

        /* glad: load all OpenGL function pointers */
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
            throw std::runtime_error("Failed to initialize GLAD");

        /* setup glfw callbacks */
        glfwSetFramebufferSizeCallback(_window, c_on_new_framebuffer);
        glfwSetMouseButtonCallback(_window, c_on_click);
        glfwSetKeyCallback(_window, c_on_press);
        glfwSetCursorPosCallback(_window, c_on_cursor_move);
        glfwSetCharCallback(_window, c_on_character);

        /* OpenGL configuration */
        glViewport(0, 0, _width, _height);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    bool GLFWWindow::is_open()
    {
        return !glfwWindowShouldClose(_window);
    }

    void GLFWWindow::close()
    {
        glfwSetWindowShouldClose(_window, true);
    }

    GLFWWindow::~GLFWWindow()
    {
        glfwTerminate();
    }

    void GLFWWindow::clear(float r, float g, float b, float a)
    {
        glClearColor(r, g, b, a);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void GLFWWindow::poll_events()
    {
        glfwPollEvents();
    }

    void GLFWWindow::swap_buffer()
    {
        glfwSwapBuffers(_window);
    }

} /* end of namespace pgl::gui */
