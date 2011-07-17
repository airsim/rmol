##
# Required libraries
set (CMAKE_REQUIRED_LIBRARIES ${BOOST_LIBS_FOR_BIN} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES})

##
# Assembling
add_executable (${LOCAL_PROJECT_NAME} ${LOCAL_PROJECT_NAME}.cpp)
target_link_libraries (${LOCAL_PROJECT_NAME} 
  ${LOCAL_LIB_TARGET}
  ${Boost_PROGRAM_OPTIONS_LIBRARY} ${CMAKE_REQUIRED_LIBRARIES})

##
# Install binaries
install (TARGETS ${LOCAL_PROJECT_NAME} 
  EXPORT ${LIB_DEPENDENCY_EXPORT}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin)

##
# Add the binary target to the build-tree export set.
# Note that the binary target has been set within the batches sub-directory.
# While several "install (TARGETS myBinary)" may be called, 
# the "export (TARGETS myBinary)" must be called only once.
export (TARGETS ${LOCAL_PACKAGE}
  ${EXTRA_LIBS} ${RMOL_UICL_LIB_TARGET}
  FILE "${PROJECT_BINARY_DIR}/${LIB_DEPENDENCY_EXPORT}.cmake")
