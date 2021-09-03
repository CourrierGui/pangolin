#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace pgl {
  namespace gui {

    class Window {
      private:
        int height, width;

        Window(int height, int width);
    };

  } /* end of namespace ui */
} /* end of namespace pgl */
