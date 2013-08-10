cmake_minimum_required (VERSION 2.8)

project (app CXX)


include_directories (
  ${glbarcode_SOURCE_DIR}
)

link_directories (
  ${glbarcode_SOURCE_DIR}/libglbarcode
)

add_executable (glbarcode
  main.cpp
)

target_link_libraries (glbarcode
  glbarcode-${API_VERSION}
)

