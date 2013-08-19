cmake_minimum_required (VERSION 2.8)

project (lib CXX)

set (PUBLIC_HEADERS
  Barcode.h
  BarcodeCepnet.h
  BarcodeCode39Ext.h
  BarcodeCode39.h
  BarcodeEan13.h
  BarcodeOnecode.h
  BarcodeOptions.h
  BarcodePostnet11.h
  BarcodePostnet5.h
  BarcodePostnet9.h
  BarcodePostnet.h
  BarcodeUpcA.h
  BarcodeUpcBase.h
  Constants.h
  Factory.h
  Primitives.h
  RendererDebug.h
  Renderer.h
  RendererSvg.h
)

set (LIB_SOURCES
  Factory.cpp
  Primitives.cpp
  Barcode.cpp
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
  Renderer.cpp
  RendererSvg.cpp
)

add_definitions (
  -DMY_PACKAGE_NAME=\"${Package_Name}\"
  -DMY_PACKAGE_VERSION=\"${Package_Version}\"
  -DMY_PACKAGE_URL=\"${Package_URL}\"
)

add_library (${Lib_Name} SHARED
  ${LIB_SOURCES}
)

install (TARGETS ${Lib_Name} LIBRARY DESTINATION lib)
install (FILES ${PUBLIC_HEADERS} DESTINATION include/${Lib_Name}/glbarcode)