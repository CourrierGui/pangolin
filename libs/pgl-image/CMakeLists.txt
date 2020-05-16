add_library(pgl-image SHARED
  src/image-loader.cpp
)
target_include_directories(pgl-image
  PUBLIC
    include
  PRIVATE
    src
)

add_subdirectory(tests)
# TODO: install targets
