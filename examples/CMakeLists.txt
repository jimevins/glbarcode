cmake_minimum_required (VERSION 2.8)

project (examples CXX)


include_directories(
  ${GLBARCODE_PP_SOURCE_DIR}
)

link_directories(
  ${GLBARCODE_PP_SOURCE_DIR}/glbarcode
)


add_executable(generate-samples
  generate-samples.cpp
)

target_link_libraries(generate-samples
  ${Lib_Name}
)


add_executable(usage-example-1
  usage-example-1.cpp
)

target_link_libraries(usage-example-1
  ${Lib_Name}
)

add_executable(mybarcode-example
  MyBarcode/main.cpp
  MyBarcode/MyBarcode.cpp
)

target_link_libraries(mybarcode-example
  ${Lib_Name}
)

