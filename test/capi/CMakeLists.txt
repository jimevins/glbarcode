cmake_minimum_required (VERSION 2.8)

project (test C)


include_directories(
  ${GLBARCODE_PP_SOURCE_DIR}
)

link_directories(
  ${GLBARCODE_PP_SOURCE_DIR}/glbarcode
  ${GLBARCODE_PP_SOURCE_DIR}/glbarcode/capi
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

