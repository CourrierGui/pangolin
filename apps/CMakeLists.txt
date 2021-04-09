add_executable(demo demo.cpp)
target_link_libraries(demo
  PRIVATE
    pgl::core pgl::gui pgl::math pgl::glad
    compilation_flags
)

install(
  TARGETS demo
    EXPORT pangolin-targets
    RUNTIME DESTINATION bin
)
