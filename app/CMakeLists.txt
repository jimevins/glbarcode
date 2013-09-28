cmake_minimum_required (VERSION 2.8)

project (app CXX)


include_directories (
  ${GLBARCODE_PP_SOURCE_DIR}
)

link_directories (
  ${GLBARCODE_PP_SOURCE_DIR}/glbarcode
)

add_executable (glbarcode
  main.cpp
)

target_link_libraries (glbarcode
  ${Lib_Name}
)


install (TARGETS glbarcode RUNTIME DESTINATION bin)
