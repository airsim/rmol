# That file is just a wrapper around the standard Fedora/RedHat
# FindPythonLibs.cmake script. Indeed, that latter does not work well on
# EPEL 5, when Python-2.6 is not installed, because only the Python (2.4) 
# static library is found. In that latter case, the following CMake code
# searches for the Python dynamic library, and the PYTHON_LIBRARIES variable
# is re-set accordingly.
#
# Moreover, on EPEL 5 and 6, only PYTHON_INCLUDE_PATH is defined, where as
# PYTHON_INCLUDE_DIRS is expected to be set.
#
if (PYTHON_INCLUDE_PATH AND "${PYTHON_INCLUDE_DIRS}" STREQUAL "")
  set (PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_PATH} PARENT_SCOPE)
  set (PYTHON_INCLUDE_DIRS ${PYTHON_INCLUDE_PATH})
endif ()

#
if ("${PYTHON_LIBRARIES}" MATCHES "libpython[1-9.]*.a")
  # The PythonLibs finder has found only the static library
  message (STATUS "The Python static library has been found by the regular PythonLibs finder: ${PYTHON_LIBRARIES}")
  message (STATUS "  => The dynamic library will be searched instead")

  # Set up the versions we know about, in the order we will search. Always add
  # the user supplied additional versions to the front.
  set(_Python_VERSIONS ${Python_ADDITIONAL_VERSIONS}
	3.10 3.9 3.8 3.7 3.6 3.5 3.4 2.8 2.7 2.6 2.5 2.4 2.3 2.2 2.1 2.0 1.6 1.5)

  foreach (_CURRENT_VERSION ${_Python_VERSIONS})
	string (REPLACE "." "" _CURRENT_VERSION_NO_DOTS ${_CURRENT_VERSION})
	find_library (PYTHON_DYN_LIBRARY
      NAMES python${_CURRENT_VERSION_NO_DOTS} python${_CURRENT_VERSION})
	if (NOT "${PYTHON_DYN_LIBRARY}" STREQUAL "")
	  set (PYTHON_LIBRARIES ${PYTHON_DYN_LIBRARY})
	endif (NOT "${PYTHON_DYN_LIBRARY}" STREQUAL "")
  endforeach (_CURRENT_VERSION ${_Python_VERSIONS})

  # Check the version requirement only
  include (FindPackageHandleStandardArgs)
  if (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
	find_package_handle_standard_args (PythonLibsWrapper
	  REQUIRED_VARS PYTHON_LIBRARIES PYTHON_INCLUDE_PATH
	  VERSION_VAR PYTHONLIBS_VERSION)
  else (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
	find_package_handle_standard_args (PythonLibsWrapper
	  DEFAULT_MSG PYTHON_LIBRARIES PYTHON_INCLUDE_PATH)
  endif (${CMAKE_VERSION} VERSION_GREATER 2.8.1)

  if (PYTHONLIBSWRAPPER_FOUND)
	mark_as_advanced (PYTHONLIBSWRAPPER_FOUND)
  else (PYTHONLIBSWRAPPER_FOUND)
	message (FATAL_ERROR "Could not find the PythonLibs libraries! Please install the development-libraries and headers (e.g., 'pythonlibs-devel' for Fedora/RedHat).")
  endif (PYTHONLIBSWRAPPER_FOUND)

endif ("${PYTHON_LIBRARIES}" MATCHES "libpython[1-9.]*.a")
