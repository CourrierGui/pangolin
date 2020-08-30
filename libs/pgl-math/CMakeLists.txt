add_library(pgl-math INTERFACE)
add_library(pangolin::pgl-math ALIAS pgl-math)
target_include_directories(pgl-math
	INTERFACE
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_precompile_headers(pgl-math
	INTERFACE
		include/pgl-math/vector.hpp
		include/pgl-math/matrix.hpp
		include/pgl-math/quaternion.hpp
)

add_subdirectory(tests)

install(
  TARGETS pgl-math
  EXPORT pangolin-targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/pgl-math
  DESTINATION include/pangolin
)
