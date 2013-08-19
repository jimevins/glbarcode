cmake_minimum_required (VERSION 2.8)

project (test CXX)


include_directories(
  ${GLBARCODE_PP_SOURCE_DIR}
)

link_directories(
  ${GLBARCODE_PP_SOURCE_DIR}/glbarcode
)

add_executable(test-debug-renderer
  test-debug-renderer.cpp
)

target_link_libraries(test-debug-renderer
  ${Lib_Name}
)

add_executable(test-svg-renderer
  test-svg-renderer.cpp
)

target_link_libraries(test-svg-renderer
  ${Lib_Name}
)