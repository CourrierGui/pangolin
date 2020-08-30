#include <pgl-gui/window.hpp>

#include <functional>
#include <iostream>

using namespace std::placeholders;

namespace pgl {
	namespace gui {

		Window::Window(int height, int width)
			: height(height), width(width)
		{
		}

	} /* end of namespace gui */
} /* end of namespace pgl */
