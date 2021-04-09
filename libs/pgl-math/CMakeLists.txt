add_library(math SHARED src/vector.cpp)
add_library(pgl::math ALIAS math)
target_include_directories(math
  PUBLIC
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
# target_precompile_headers(math
# 	INTERFACE
# 		include/math/vector.hpp
# 		include/math/impl/matrix.hpp
# 		include/math/impl/vector.hpp
# 		include/math/impl/algorithms.hpp
# 		include/math/matrix.hpp
# 		include/math/quaternion.hpp
# )
target_link_libraries(math
  PRIVATE
    compilation_flags
)

add_subdirectory(tests)

install(
  TARGETS math
  EXPORT pgl_targets
  LIBRARY DESTINATION lib/pangolin
  ARCHIVE DESTINATION lib/pangolin
)
install(
  DIRECTORY include/math
  DESTINATION include/pangolin
)
