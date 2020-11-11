<<<<<<< HEAD
add_library(pgl-math SHARED src/vector.cpp)
add_library(pangolin::pgl-math ALIAS pgl-math)
target_include_directories(pgl-math
  PUBLIC
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
# target_precompile_headers(pgl-math
# 	INTERFACE
# 		include/pgl-math/vector.hpp
# 		include/pgl-math/impl/matrix.hpp
# 		include/pgl-math/impl/vector.hpp
# 		include/pgl-math/impl/algorithms.hpp
# 		include/pgl-math/matrix.hpp
# 		include/pgl-math/quaternion.hpp
# )
target_link_libraries(pgl-math
  PRIVATE
    target-flags
)

add_subdirectory(tests)

install(
  TARGETS math
  EXPORT pgl_targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/pgl-math
  DESTINATION include/pangolin
)
