# That file is just wrapper around the standard Fedora/RedHat FindDoxygen.cmake
# script. Indeed, that latter does not do version comparison. So, we just
# use here standard CMake mechanism to enforce the Doxygen required version.
# 

# Extract the version information
if (DOXYGEN_FOUND STREQUAL "YES")
  execute_process (
	COMMAND ${DOXYGEN_EXECUTABLE} --version
	OUTPUT_VARIABLE MY_TMP
	OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set (DOXYGEN_VERSION ${MY_TMP})

  # Check the version requirement only
  include (FindPackageHandleStandardArgs)
  if (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
	find_package_handle_standard_args (DoxygenWrapper
	  REQUIRED_VARS DOXYGEN_EXECUTABLE
	  VERSION_VAR DOXYGEN_VERSION)
  else (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
	find_package_handle_standard_args (DoxygenWrapper
	  DEFAULT_MSG DOXYGEN_EXECUTABLE)
  endif (${CMAKE_VERSION} VERSION_GREATER 2.8.1)

endif (DOXYGEN_FOUND STREQUAL "YES")

if (DOXYGENWRAPPER_FOUND)
  mark_as_advanced (DOXYGENWRAPPER_FOUND DOXYGEN_VERSION DOXYGEN_EXECUTABLE)
  message (STATUS "Found Doxygen version: ${DOXYGEN_VERSION}")
else (DOXYGENWRAPPER_FOUND)
  message (FATAL_ERROR "Could not find the Doxygen utilities! Please install them (e.g., 'doxygen' for Fedora/RedHat).")
endif (DOXYGENWRAPPER_FOUND)

