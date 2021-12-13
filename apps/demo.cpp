#include <pgl-gui/glfw-window.hpp>
#include <pgl-core/resource-manager.hpp>
#include <pgl-core/text-renderer.hpp>
#include <pgl-math/vector.hpp>
#include <pgl-tools/logger.hpp>

#include <array>
#include <iostream>

void press_event(std::string& text, pgl::gui::GLFWWindow& window, pgl::key key)
{
    if (key == pgl::key::escape)
        window.close();
    else if (key == pgl::key::backspace && !text.empty())
        text.pop_back();
    else
        std::clog << key << '\n';
}

int main() {
    constexpr uint32_t width = 600;
    constexpr uint32_t height = 600;

    pgl::entry();

    auto window = pgl::gui::GLFWWindow(width, height, "Pangolin demo");
    pgl::load_shader("text",
                     "../resources/shader/text.vs",
                     "../resources/shader/text.fs");

    pgl::gui::TextRenderer renderer{
        width, height,
            pgl::get_shader("text")};
    renderer.load("../resources/fonts/ocraext.TTF", 14);

    std::string text = "Hello World!";
    pgl::float2 pos{width/2.0f, height/2.0f};
    pgl::float2 cursorPos = pos;

    window.on_character = [&text](pgl::gui::GLFWWindow&, uint32_t codepoint)
    {
        // FIXME handle UTF-8 properly
        text.push_back((char)codepoint);
    };

    window.on_press = [&text](
        pgl::gui::GLFWWindow& window, pgl::key key)
    {
        press_event(text, window, key);
    };

    window.on_click = [&pos, &cursorPos](
        pgl::gui::GLFWWindow&, pgl::mouse event)
    {
        if (event == pgl::mouse::button_left)
            pos = cursorPos;
    };

    window.on_cursor_move = [&cursorPos](pgl::gui::GLFWWindow&, float x, float y)
        -> void
    {
        cursorPos = {x, y};
    };

    while (window.is_open()) {
        window.poll_events();
        window.clear(1.0f, 1.0f, 1.0f, 1.0f);

        renderer.render_text(text, pos.x, pos.y, 1.0f, pgl::float3{0.0f, 0.0f, 0.0f});

        window.swap_buffer();
    }

    return 0;
}
