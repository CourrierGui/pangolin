#include <pgl-gui/window.hpp>

#include <functional>
#include <iostream>

using namespace std::placeholders;

namespace pgl {
	namespace ui {

		Window::Window(int height, int width)
			: height(height), width(width)
		{
		}

	} /* end of namespace ui */
} /* end of namespace pgl */
