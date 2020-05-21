add_library(pgl-ui SHARED
  window.cpp
)
add_library(pangolin::pgl-ui ALIAS pgl-ui)
target_include_directories(pgl-ui
  PUBLIC
    ../include
  PRIVATE
    ../src
)
