cmake_minimum_required (VERSION 2.8)

project (test CXX)


include_directories(
  ${glbarcode_SOURCE_DIR}
)

link_directories(
  ${glbarcode_SOURCE_DIR}/libglbarcode
)

add_executable(test-debug-renderer
  test-debug-renderer.cpp
)

target_link_libraries(test-debug-renderer
  glbarcode
)