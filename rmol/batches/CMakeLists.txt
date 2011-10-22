##
# Assembling
add_executable (${MODULE_NAME} ${MODULE_NAME}.cpp)
target_link_libraries (${MODULE_NAME}
  ${PROJ_DEP_LIBS_FOR_BIN} ${MODULE_LIB_TARGET} ${_intermodule_dependencies})

##
# Install binaries
install (TARGETS ${MODULE_NAME} 
  EXPORT ${LIB_DEPENDENCY_EXPORT}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT runtime)
