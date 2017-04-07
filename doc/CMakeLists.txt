# add a target to generate API documentation with Doxygen
find_package (Doxygen)
if (DOXYGEN_FOUND)

  configure_file (glbarcode.doxy.in ${CMAKE_CURRENT_BINARY_DIR}/glbarcode.doxy @ONLY)

  add_custom_target (doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/glbarcode.doxy
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
  )

else (DOXYGEN_FOUND)

  message (STATUS "Doxygen not found.  API documentation will not be generated.")

endif (DOXYGEN_FOUND)
