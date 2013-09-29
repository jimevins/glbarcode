cmake_minimum_required (VERSION 2.8)

project (lib CXX)

set (PUBLIC_HEADERS
  Factory.h
  Barcode.h
  Barcode1dBase.h
  Barcode2dBase.h
  BarcodeCepnet.h
  BarcodeCode39Ext.h
  BarcodeCode39.h
  BarcodeDataMatrix.h
  BarcodeEan13.h
  BarcodeOnecode.h
  BarcodePostnet11.h
  BarcodePostnet5.h
  BarcodePostnet9.h
  BarcodePostnet.h
  BarcodeUpcA.h
  BarcodeUpcBase.h
  BarcodeQrcode.h
  Constants.h
  DrawingPrimitives.h
  Matrix.h
  Renderer.h
  RendererSvg.h
  RendererEps.h
  RendererDebug.h
  ${CMAKE_CURRENT_BINARY_DIR}/Version.h
)

set (LIB_SOURCES
  Factory.cpp
  Barcode.cpp
  Barcode1dBase.cpp
  Barcode2dBase.cpp
  BarcodeCode39.cpp
  BarcodeCode39Ext.cpp
  BarcodeUpcBase.cpp
  BarcodeUpcA.cpp
  BarcodeEan13.cpp
  BarcodePostnet.cpp
  BarcodePostnet5.cpp
  BarcodePostnet9.cpp
  BarcodePostnet11.cpp
  BarcodeCepnet.cpp
  BarcodeOnecode.cpp
  BarcodeDataMatrix.cpp
  BarcodeQrcode.cpp
  DrawingPrimitives.cpp
  Renderer.cpp
  RendererSvg.cpp
  RendererEps.cpp
  RendererDebug.cpp
)

include_directories (
  ${CMAKE_CURRENT_BINARY_DIR}
  ${LIBQRENCODE_INCLUDE_DIR}
)

add_library (${Lib_Name} SHARED
  ${LIB_SOURCES}
)

target_link_libraries (${Lib_Name}
  ${LIBQRENCODE_LIBRARIES}
)


configure_file (Version.h.in ${CMAKE_CURRENT_BINARY_DIR}/Version.h @ONLY)
configure_file (${Unique_Package_Name}.pc.in ${CMAKE_CURRENT_BINARY_DIR}/${Unique_Package_Name}.pc @ONLY)


install (TARGETS ${Lib_Name} LIBRARY DESTINATION lib)
install (FILES ${PUBLIC_HEADERS} DESTINATION include/${Unique_Package_Name}/glbarcode)
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${Unique_Package_Name}.pc DESTINATION lib/pkgconfig)