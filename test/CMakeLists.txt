include_directories(
  ${glbarcodepp_SOURCE_DIR}
)

link_directories(
  ${glbarcodepp_SOURCE_DIR}/glbarcode
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


add_executable(test-datamatrix
  test-datamatrix.cpp
)

target_link_libraries(test-datamatrix
  ${Lib_Name}
)
