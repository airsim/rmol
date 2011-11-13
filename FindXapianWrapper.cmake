# That file is just a wrapper around the standard Fedora/RedHat 
# xapian-config.cmake script. Indeed, that latter does not do version
# comparison. So, we just use here standard CMake mechanism to enforce the
# Xapian required version.
# 

# Extract the version information
if (XAPIAN_FOUND)

  # Extract version information from version.h
  if (XAPIAN_INCLUDE_DIR)
	# Extract XAPIAN_VERSION from version.h
	# Read the whole file:
	set (XAPIAN_VERSION "")
	set (XAPIAN_MAJOR_VERSION "")
	set (XAPIAN_MINOR_VERSION "")
	set (XAPIAN_REVISION "")
	file (READ "${XAPIAN_INCLUDE_DIR}/xapian/version.h"
	  _xapian_VERSION_HPP_CONTENTS)
	if (XAPIAN_DEBUG)
      message (STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
		"location of version.h: ${XAPIAN_INCLUDE_DIR}/xapian/version.h")
	endif (XAPIAN_DEBUG)
  
	string (REGEX REPLACE ".*#define XAPIAN_VERSION \"([0-9.]+)\".*" "\\1"
	  XAPIAN_VERSION "${_xapian_VERSION_HPP_CONTENTS}")
	set (XAPIAN_VERSION ${XAPIAN_VERSION} 
	  CACHE INTERNAL "The version number for Xapian")

	#
	if (XAPIAN_DEBUG)
      message (STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
		"version.h reveals Xapian ${XAPIAN_VERSION}")
	endif (XAPIAN_DEBUG)
	
  else (XAPIAN_INCLUDE_DIR)
	set (XAPIAN_ERROR_REASON
      "${XAPIAN_ERROR_REASON}Unable to find the XAPIAN header files. Please set XAPIAN_ROOT to the root directory containing XAPIAN or XAPIAN_INCLUDE_DIR to the directory containing Xapian's headers.")
  endif (XAPIAN_INCLUDE_DIR)

  # Check the version requirement only
  include (FindPackageHandleStandardArgs)
  if (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
	find_package_handle_standard_args (XapianWrapper
	  REQUIRED_VARS XAPIAN_INCLUDE_DIR XAPIAN_LIBRARIES
	  VERSION_VAR XAPIAN_VERSION)
  else (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
	find_package_handle_standard_args (XapianWrapper
	  DEFAULT_MSG XAPIAN_INCLUDE_DIR XAPIAN_LIBRARIES)
  endif (${CMAKE_VERSION} VERSION_GREATER 2.8.1)

endif (XAPIAN_FOUND)

if (XAPIANWRAPPER_FOUND)
  mark_as_advanced (XAPIANWRAPPER_FOUND XAPIAN_VERSION
	XAPIAN_INCLUDE_DIR XAPIAN_LIBRARIES)
  message (STATUS "Found Xapian version: ${XAPIAN_VERSION}")
else (XAPIANWRAPPER_FOUND)
  message (FATAL_ERROR "Could not find the Xapian utilities! Please install them (e.g., 'xapian-core-devel' for Fedora/RedHat).")
endif (XAPIANWRAPPER_FOUND)

