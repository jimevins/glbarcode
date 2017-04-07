include_directories (
  ${glbarcodepp_SOURCE_DIR}
)

link_directories (
  ${glbarcodepp_SOURCE_DIR}/glbarcode
)

add_executable (glbarcode
  main.cpp
)

target_link_libraries (glbarcode
  ${Lib_Name}
)


install (TARGETS glbarcode RUNTIME DESTINATION bin)
