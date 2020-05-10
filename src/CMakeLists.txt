add_library(glad STATIC glad.cpp)
target_include_directories(glad PUBLIC ${pangolin_SOURCE_DIR}/include)
target_link_libraries(glad dl)

add_library(stb_image STATIC stb_image.cpp)
target_include_directories(stb_image PUBLIC ${pangolin_SOURCE_DIR}/include)

set(
  pangolin_src

  game-object.cpp
  mesh.cpp
  model.cpp
  particle-generator.cpp
  post-processor.cpp
  resource-manager.cpp
  shader.cpp
  sprite-renderer.cpp
  # text-renderer.cpp
  texture.cpp
  profile.cpp
)

# add_library(freetype SHARED IMPORTED)
# set_target_properties(freetype PROPERTIES
#   IMPORTED_LOCATION "${pangolin_SOURCE_DIR}/extern/freetype2/objs/.libs/libfreetype.so")

add_library(pangolin STATIC ${pangolin_src})
target_include_directories(pangolin PUBLIC "${pangolin_SOURCE_DIR}/include"                 )
target_include_directories(pangolin PUBLIC "${pangolin_SOURCE_DIR}/extern/glm"              )
target_include_directories(pangolin PUBLIC "${pangolin_SOURCE_DIR}/extern/glfw/include"     )
target_include_directories(pangolin PUBLIC "${pangolin_SOURCE_DIR}/extern/assimp/include"   )
target_include_directories(pangolin PUBLIC "${pangolin_SOURCE_DIR}/extern/freetype2/include")
target_link_libraries(pangolin glad glm) # freetype)
