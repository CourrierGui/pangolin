add_library(glad STATIC glad/glad.c)
target_link_libraries(glad dl)

add_library(pangolin STATIC
  src/game-object.cpp
  src/mesh.cpp
  # src/model.cpp
  src/particle-generator.cpp
  src/post-processor.cpp
  # src/resource-manager.cpp
  src/shader.cpp
  src/sprite-renderer.cpp
  src/text-renderer.cpp
  src/texture.cpp
)
target_include_directories(pangolin
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  PRIVATE
    extern/freetype2/include
)
target_compile_options(pangolin PRIVATE -Wall -Wextra)
target_compile_features(pangolin PRIVATE cxx_std_20)
target_link_libraries(pangolin 
  PUBLIC
    assimp glfw glad Freetype::Freetype
)

