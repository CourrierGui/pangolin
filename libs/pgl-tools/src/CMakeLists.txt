add_library(pgl-gui SHARED
  window.cpp
)
add_library(pangolin::pgl-gui ALIAS pgl-gui)
target_include_directories(pgl-gui
  PUBLIC
    ../include
  PRIVATE
    ../src
)

install(
	TARGETS pgl-gui
	EXPORT pangolin-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pangolin
)
install(
	DIRECTORY include/pgl-gui
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pangolin
)
