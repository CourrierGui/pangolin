add_executable(demo demo.cpp)
target_link_libraries(demo PRIVATE pangolin::pangolin pangolin::pgl-gui target-flags)
