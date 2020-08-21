add_library(pangolin SHARED
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
add_library(pangolin::pangolin ALIAS pangolin)

target_include_directories(pangolin
  PUBLIC
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(pangolin
  PUBLIC
    pangolin::pgl-image
  PRIVATE
    assimp glfw pangolin::glad Freetype::Freetype
    $<BUILD_INTERFACE:target-flags>
)

install(
  TARGETS pangolin
  EXPORT pangolin-targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/pangolin
  DESTINATION include/pangolin
)
