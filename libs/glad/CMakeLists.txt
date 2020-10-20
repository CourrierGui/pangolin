add_library(glad SHARED src/glad.c)
add_library(pgl::glad ALIAS glad)
target_include_directories(glad
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(glad dl)

install(
  TARGETS glad
  EXPORT pgl_targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/glad
  DESTINATION include/pangolin
)
