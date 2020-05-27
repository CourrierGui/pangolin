add_library(glad SHARED glad/glad.c)
# target_include_directories(glad
#   PUBLIC
#     $<INSTALL_INTERFACE:glad>
#     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/glad>
# )
target_link_libraries(glad dl)

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
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(pangolin 
  PUBLIC
    pangolin::pgl-image
  PRIVATE
    assimp glfw glad Freetype::Freetype
    $<BUILD_INTERFACE:target-flags>
)

install(
  TARGETS pangolin glad
  EXPORT pangolin-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
)
install(
  DIRECTORY include/pangolin
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)
