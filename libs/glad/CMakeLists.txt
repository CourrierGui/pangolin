add_library(glad SHARED src/glad.c)
add_library(pangolin::glad ALIAS glad)
target_include_directories(glad
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(glad dl)

install(
  TARGETS glad
  EXPORT pangolin-targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/glad
  DESTINATION include/pangolin
)
