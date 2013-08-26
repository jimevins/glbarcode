cmake_minimum_required (VERSION 2.8)

project (examples CXX)


include_directories(
  ${GLBARCODE_PP_SOURCE_DIR}
)

link_directories(
  ${GLBARCODE_PP_SOURCE_DIR}/glbarcode
)


add_executable(generate-examples
  generate-examples.cpp
)

target_link_libraries(generate-examples
  ${Lib_Name}
)


add_executable(usage-example-1
  usage-example-1.cpp
)

target_link_libraries(usage-example-1
  ${Lib_Name}
)

