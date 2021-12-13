#pragma once

#include <glad/glad.h>

#include <string>
#include <functional>

class GLFWwindow;

namespace pgl {

    enum key {
        escape,
        backspace,
    };

    enum class mouse {
        button_left,
    };
}

namespace pgl::gui {

    class GLFWWindow {
        public:
            using on_click_t = std::function<void(GLFWWindow&, mouse)>;
            using on_cursor_move_t = std::function<void(GLFWWindow&, double, double)>;
            using on_press_t = std::function<void(GLFWWindow&, pgl::key)>;
            using on_character_t = std::function<void(GLFWWindow&, uint32_t)>;

            on_click_t       on_click;
            on_press_t       on_press;
            on_cursor_move_t on_cursor_move;
            on_character_t   on_character;

            GLFWWindow(int width, int height, const std::string& name);
            GLFWWindow(const GLFWWindow&) = delete;
            GLFWWindow& operator=(const GLFWWindow&) = delete;
            ~GLFWWindow();

            bool is_open();
            void close();
            void poll_events();
            void swap_buffer();
            void clear(float r, float g, float b, float a);

        private:
            int _width, _height;
            GLFWwindow* _window;
    };

} /* end of namespace pgl::gui */
