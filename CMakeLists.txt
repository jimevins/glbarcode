cmake_minimum_required (VERSION 2.8)

project (glbarcode)

set (API_VERSION 4.0)


###################################
# Optional LIBPNG renderer support
###################################
find_package (PNG)
if (PNG_FOUND)
  add_definitions (-DHAVE_LIBPNG)
else (PNG_FOUND)
  message (STATUS "Libpng not found.  Will not build RendererPng.")
endif (PNG_FOUND)


###################################
# Subdirectories
###################################
add_subdirectory (libglbarcode)
add_subdirectory (app)
add_subdirectory (test)
add_subdirectory (doc)

