add_library(math SHARED src/vector.cpp)
add_library(pgl::math ALIAS math)
target_include_directories(math
  PUBLIC
    $<INSTALL_INTERFACE:include/pangolin>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
# precompiled header makes everything magically available even without correct
# linking
# Not sure if that's a good thing...
target_precompile_headers(math
  INTERFACE
    include/pgl-math/vector.hpp
    include/pgl-math/impl/vector.hpp

    include/pgl-math/algorithms.hpp
    include/pgl-math/impl/algorithms.hpp

    include/pgl-math/matrix.hpp
    include/pgl-math/impl/matrix.hpp

    include/pgl-math/quaternion.hpp
)
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
  DIRECTORY include/pgl-math
  DESTINATION include/pangolin
)
