cmake_minimum_required (VERSION 2.8)

project (lib CXX)

add_library(glbarcode-${API_VERSION}
  Factory.cpp
  Primitives.cpp
  Barcode.cpp
  BarcodeCode39.cpp
  Renderer.cpp
  RendererSvg.cpp
  RendererPng.cpp
)