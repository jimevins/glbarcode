include_directories(
  ${glbarcodepp_SOURCE_DIR}
)

link_directories(
  ${glbarcodepp_SOURCE_DIR}/glbarcode
  ${glbarcodepp_SOURCE_DIR}/glbarcode/capi
)


add_executable(capi-test-svg-renderer
  capi-test-svg-renderer.c
)

target_link_libraries(capi-test-svg-renderer
  ${CAPI_Lib_Name}
  ${Lib_Name}
)


add_executable(capi-test-factory
  capi-test-factory.c
)

target_link_libraries(capi-test-factory
  ${CAPI_Lib_Name}
  ${Lib_Name}
)

