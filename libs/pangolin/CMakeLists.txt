add_library(glad STATIC glad/glad.c)
# target_include_directories(glad PUBLIC glad/glad.h)
target_link_libraries(glad dl)

add_library(pangolin STATIC
  src/game-object.cpp
  src/mesh.cpp
  src/particle-generator.cpp
  src/post-processor.cpp
  src/shader.cpp
  src/sprite-renderer.cpp
  src/text-renderer.cpp
  src/texture.cpp

  # src/model.cpp
  # src/resource-manager.cpp
)

target_include_directories(pangolin
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_options(pangolin PRIVATE -Wall -Wextra)
target_compile_features(pangolin PRIVATE cxx_std_20)
target_link_libraries(pangolin 
  PRIVATE
    assimp glfw glad Freetype::Freetype
)

install(
  TARGETS pangolin glad
  EXPORT pangolin-targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
  DIRECTORY include/pangolin
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
