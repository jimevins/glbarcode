cmake_minimum_required (VERSION 2.8)

project (doc)

# add a target to generate API documentation with Doxygen
find_package (Doxygen)
if(DOXYGEN_FOUND)

  configure_file(glbarcode.doxy.in ${CMAKE_CURRENT_BINARY_DIR}/glbarcode.doxy @ONLY)

  add_custom_target(doc ALL
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/glbarcode.doxy
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )

endif(DOXYGEN_FOUND)
