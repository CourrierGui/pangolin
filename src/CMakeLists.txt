add_library(glad STATIC glad.cpp)
target_include_directories(glad PUBLIC ${pangolin_SOURCE_DIR}/include)

add_library(stb_image STATIC stb_image.cpp)
target_include_directories(stb_image PUBLIC ${pangolin_SOURCE_DIR}/include)

set(
  pangolin_src
  shader.cpp
  mesh.cpp
  model.cpp
  texture.cpp
  resource-manager.cpp
)

add_library(pangolin STATIC ${pangolin_src})
target_include_directories(pangolin PUBLIC ${pangolin_SOURCE_DIR}/include)
target_include_directories(pangolin PUBLIC ${pangolin_SOURCE_DIR}/extern/glm)
target_include_directories(pangolin PUBLIC ${pangolin_SOURCE_DIR}/extern/assimp)
target_link_libraries(pangolin glad glm)
