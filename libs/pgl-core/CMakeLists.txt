add_library(core SHARED
	src/camera.cpp
  src/game-object.cpp
  src/mesh.cpp
  src/particle-generator.cpp
  src/post-processor.cpp
  src/shader.cpp
  src/sprite-renderer.cpp
  src/text-renderer.cpp
  src/texture.cpp
  src/resource-manager.cpp
  # src/model.cpp
)
add_library(pgl::core ALIAS core)

target_include_directories(core
  PUBLIC
    $<INSTALL_INTERFACE:include/pgl-core>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(core
  PUBLIC
    pgl::image
		pgl::math
  PRIVATE
    assimp glfw pgl::glad Freetype::Freetype
		compilation_flags
)

install(
  TARGETS core
  EXPORT pgl_targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/pgl-core
  DESTINATION include/pangolin
)
