include_directories (
  ${glbarcodepp_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

set (PUBLIC_HEADERS
  gbc_factory.h
  gbc_barcode.h
  gbc_renderer.h
  gbc_renderer_debug.h
  gbc_renderer_eps.h
  gbc_renderer_svg.h
  ${CMAKE_CURRENT_BINARY_DIR}/gbc_version.h
)

set (LIB_SOURCES
  gbc_factory.cpp
  gbc_barcode.cpp
  gbc_renderer.cpp
  gbc_renderer_debug.cpp
  gbc_renderer_eps.cpp
  gbc_renderer_svg.cpp
)

add_library (${CAPI_Lib_Name} SHARED
  ${LIB_SOURCES}
)

configure_file (gbc_version.h.in ${CMAKE_CURRENT_BINARY_DIR}/gbc_version.h @ONLY)
configure_file (${Unique_CAPI_Package_Name}.pc.in ${CMAKE_CURRENT_BINARY_DIR}/${Unique_CAPI_Package_Name}.pc @ONLY)

install (TARGETS ${CAPI_Lib_Name} LIBRARY DESTINATION lib)
install (FILES ${PUBLIC_HEADERS} DESTINATION include/${Unique_Package_Name}/glbarcode/capi)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${Unique_CAPI_Package_Name}.pc DESTINATION lib/pkgconfig)
