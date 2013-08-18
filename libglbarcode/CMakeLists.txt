cmake_minimum_required (VERSION 2.8)

project (lib CXX)

add_library(glbarcode-${API_VERSION}
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