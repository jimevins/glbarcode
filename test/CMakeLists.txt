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
  glbarcode-${API_VERSION}
)

add_executable(test-svg-renderer
  test-svg-renderer.cpp
)

target_link_libraries(test-svg-renderer
  glbarcode-${API_VERSION}
)

if (PNG_FOUND)

  include_directories(
    ${PNG_INCLUDE_DIRS}
  )

  add_executable(test-png-renderer
    test-png-renderer.cpp
  )

  target_link_libraries(test-png-renderer
    glbarcode-${API_VERSION}
    ${PNG_LIBRARIES}
  )

endif (PNG_FOUND)

