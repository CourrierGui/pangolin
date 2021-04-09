file(GLOB
  test_files

  test-stream.cpp
  test-png.cpp
  test-image.cpp
)

foreach(source_file "${test_files}")

  get_filename_component(binary_file "${source_file}" NAME_WE)

  add_executable(Pgl.${binary_file} ${source_file})
  target_link_libraries(Pgl.${binary_file}
    PRIVATE
    gtest gtest_main
    pgl::image compilation_flags
    stdc++fs stb_image
  )

  gtest_add_tests(Pgl.${binary_file} "" AUTO)
endforeach(source_file)
