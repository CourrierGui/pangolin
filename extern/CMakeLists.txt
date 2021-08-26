add_library(stb_image SHARED stb_image/stb_image.c)
target_include_directories(stb_image
  PUBLIC
    $<INSTALL_INTERFACE:include/pgl-core/extern>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/stb_image>
)

install(
  TARGETS stb_image
  EXPORT pgl_targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY stb_image
  DESTINATION include/pangolin/extern
  FILES_MATCHING
  PATTERN "*.h"
)
