##
# RMOL manual pages, generated with Doxygen.
#

# Define the substitutes for the variables present in the Doxygen
# configuration files. Note that PACKAGE, PACKAGE_NAME and PACKAGE_VERSION
# are defined in the main CMakeLists.txt (of the top root directory).
set (OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"     )
set (top_srcdir       "${CMAKE_SOURCE_DIR}"             )
set (srcdir           "${CMAKE_CURRENT_SOURCE_DIR}"     )

set (man1_DIR         "${CMAKE_CURRENT_BINARY_DIR}/man1")
set (man3_DIR         "${CMAKE_CURRENT_BINARY_DIR}/man3")

# Convert the Doxygen configuration files (basically, just replace
# the @<variable>@ variables).
set (DOXYGEN_CFG1_SRC doxygen_man1.cfg.in)
set (DOXYGEN_CFG1 ${CMAKE_CURRENT_BINARY_DIR}/doxygen_man1.cfg)
configure_file (${DOXYGEN_CFG1_SRC} ${DOXYGEN_CFG1} @ONLY)
set (DOXYGEN_CFG3_SRC doxygen_man3.cfg.in)
set (DOXYGEN_CFG3 ${CMAKE_CURRENT_BINARY_DIR}/doxygen_man3.cfg)
configure_file (${DOXYGEN_CFG3_SRC} ${DOXYGEN_CFG3} @ONLY)

## Manual page sources
# Section 1 (general commands)
set (man1_SOURCES rmol.doc rmol-config.doc)
# Section 3 (development)
set (man3_SOURCES rmol-library.doc)

# Add the build rule for Doxygen for section 1 manual pages
set (DOXYGEN_OUTPUT1 ${man1_DIR}/rmol-config.1)
add_custom_command (OUTPUT ${DOXYGEN_OUTPUT1}
  COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${DOXYGEN_CFG1}
  DEPENDS ${DOXYGEN_CFG1} ${man1_SOURCES}
  COMMENT "Generating section 1 manual pages with Doxygen, from '${DOXYGEN_CFG1}'...")
# Add the build rule for Doxygen for section 3 manual pages
set (DOXYGEN_OUTPUT3 ${man3_DIR}/rmol-library.3)
add_custom_command (OUTPUT ${DOXYGEN_OUTPUT3}
  COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${DOXYGEN_CFG3}
  DEPENDS ${DOXYGEN_CFG3} ${man3_SOURCES}
  COMMENT "Generating section 3 manual pages with Doxygen, from '${DOXYGEN_CFG3}'...")
# Add the 'man' target, depending on the generated manual page documentation
add_custom_target (man ALL DEPENDS ${DOXYGEN_OUTPUT1} ${DOXYGEN_OUTPUT3})

# Clean-up $build/man1 and $build/man3 on 'make clean'
set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
  ${man1_DIR} ${man3_DIR})

# Installation of the manual pages
set (MAN_PATH "share/man")
install (DIRECTORY "${man1_DIR}" DESTINATION ${MAN_PATH})
install (DIRECTORY "${man3_DIR}" DESTINATION ${MAN_PATH})
