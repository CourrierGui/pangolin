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
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
)
install(
  DIRECTORY include/glad
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)
