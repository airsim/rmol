##
# For the other developers to use the StdAir project
#

# Configure helper (e.g., to easily retrieve the version and compilation flags)
set (CFG_SCRIPT ${CPACK_PACKAGE_NAME}-config)
set (CFG_SCRIPT_PATH bin)

# (Debian) Packaging helper
set (PKGCFG_SCRIPT ${CPACK_PACKAGE_NAME}.pc)
set (PKGCFG_SCRIPT_PATH ${LIBDIR}/pkgconfig)

# GNU Autotools helper (M4 macro file)
set (M4_MACROFILE ${CPACK_PACKAGE_NAME}.m4)
set (M4_MACROFILE_PATH "share/aclocal")

# Convert the developer script utilities (basically, just replace
# the @<variable>@ variables).
configure_file (${CFG_SCRIPT}.in ${CFG_SCRIPT} @ONLY)
configure_file (${PKGCFG_SCRIPT}.in ${PKGCFG_SCRIPT} @ONLY)
configure_file (${M4_MACROFILE}.in ${M4_MACROFILE} @ONLY)

#
add_custom_target (devhelpers ALL DEPENDS)
add_dependencies (devhelpers ${CFG_SCRIPT})
add_dependencies (devhelpers ${PKGCFG_SCRIPT})
add_dependencies (devhelpers ${M4_MACROFILE})

# Install the development helpers
install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${CFG_SCRIPT} 
  DESTINATION ${CFG_SCRIPT_PATH})
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${PKGCFG_SCRIPT}
  DESTINATION ${PKGCFG_SCRIPT_PATH})
install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${M4_MACROFILE}
  DESTINATION ${M4_MACROFILE_PATH})
