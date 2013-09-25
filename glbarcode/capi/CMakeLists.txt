cmake_minimum_required (VERSION 2.8)

project (lib CXX)

include_directories (
  ${GLBARCODE_PP_SOURCE_DIR}
)

set (PUBLIC_HEADERS
  glb_barcode_factory.h
  glb_barcode.h
  glb_renderer.h
  glb_renderer_debug.h
  glb_renderer_eps.h
  glb_renderer_svg.h
)

set (LIB_SOURCES
  glb_barcode_factory.cpp
  glb_barcode.cpp
  glb_renderer.cpp
  glb_renderer_debug.cpp
  glb_renderer_eps.cpp
  glb_renderer_svg.cpp
)

add_definitions (
  -DMY_PACKAGE_NAME=\"${Package_Name}\"
  -DMY_PACKAGE_VERSION=\"${Package_Version}\"
  -DMY_PACKAGE_URL=\"${Package_URL}\"
)

add_library (${CAPI_Lib_Name} SHARED
  ${LIB_SOURCES}
)

install (TARGETS ${CAPI_Lib_Name} LIBRARY DESTINATION lib)
install (FILES ${PUBLIC_HEADERS} DESTINATION include/${Lib_Name}/glbarcode/capi)