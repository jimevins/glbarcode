cmake_minimum_required (VERSION 2.8)

project (libglbarcode CXX)

add_library(glbarcode
  Factory.cpp
  Primitive.cpp
  Barcode.cpp
  BarcodeCode39.cpp
  Renderer.cpp
  RendererDebug.cpp
  RendererSvg.cpp
)