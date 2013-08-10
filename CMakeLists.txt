cmake_minimum_required (VERSION 2.8)

project (glbarcode)

set (API_VERSION 4.0)

add_subdirectory (libglbarcode)
add_subdirectory (app)
add_subdirectory (test)
add_subdirectory (doc)

