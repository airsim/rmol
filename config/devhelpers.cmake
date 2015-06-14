##
# For the other developers to use that project (${PROJECT_NAME})
#

# Configure helper (e.g., to easily retrieve the version and compilation flags)
set (CFG_SCRIPT ${PROJECT_NAME}-config)
set (CFG_SCRIPT_PATH bin)

# (Debian) Packaging helper
set (PKGCFG_SCRIPT ${PROJECT_NAME}.pc)
set (PKGCFG_SCRIPT_PATH ${LIBDIR}/pkgconfig)

# GNU Autotools helper (M4 macro file)
set (M4_MACROFILE ${PROJECT_NAME}.m4)
set (M4_MACROFILE_PATH share/aclocal)

# Convert the developer script utilities (basically, just replace
# the @<variable>@ variables)
configure_file (${CFG_SCRIPT}.in ${CFG_SCRIPT} @ONLY)
add_custom_target (${CFG_SCRIPT} DEPENDS ${CFG_SCRIPT}.in)
configure_file (${PKGCFG_SCRIPT}.in ${PKGCFG_SCRIPT} @ONLY)
add_custom_target (${PKGCFG_SCRIPT} DEPENDS ${PKGCFG_SCRIPT}.in)
configure_file (${M4_MACROFILE}.in ${M4_MACROFILE} @ONLY)
add_custom_target (${M4_MACROFILE} DEPENDS ${M4_MACROFILE}.in)

#
add_custom_target (devhelpers ALL DEPENDS)
add_dependencies (devhelpers ${CFG_SCRIPT})
add_dependencies (devhelpers ${PKGCFG_SCRIPT})
add_dependencies (devhelpers ${M4_MACROFILE})
