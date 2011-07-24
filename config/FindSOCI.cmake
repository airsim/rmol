# Find SOCI includes and library.
#
#  SOCI_VERSION     - The SOCI version
#  SOCI_INCLUDE_DIR - Where to find soci.h, etc.
#  SOCI_LIBRARIES   - List of libraries when using SOCI.
#  SOCI_FOUND       - Whether SOCI has been found

# Check for SOCI main header.
set (CHECK_HEADERS soci.h)
set (CHECK_SUFFIXES "" soci)
if (SOCI_INCLUDE_DIR)
  find_path (SOCI_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATHS ${SOCI_INCLUDE_DIR}
    PATH_SUFFIXES ${CHECK_SUFFIXES}
    NO_DEFAULT_PATH)
else (SOCI_INCLUDE_DIR)
  find_path (SOCI_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATH_SUFFIXES ${CHECK_SUFFIXES})
endif (SOCI_INCLUDE_DIR)

#
if (UNIX)
  set (SOCI_CONFIG_PREFER_PATH "$ENV{SOCI_HOME}/bin" CACHE FILEPATH
    "preferred path to SOCI (soci-config)")

  find_program (SOCI_CONFIG soci-config
    ${SOCI_CONFIG_PREFER_PATH}
    /usr/local/soci/bin/
    /usr/local/bin/
    /usr/bin/)

  if (SOCI_CONFIG)
    message (STATUS "Using soci-config: ${SOCI_CONFIG}")

	# Version
	exec_program (${SOCI_CONFIG} ARGS --version OUTPUT_VARIABLE MY_TMP)
	#string (REGEX REPLACE "([0-9]+.[0-9]+)(.[0-9]*)?$" "\\1" SOCI_VERSION "${MY_TMP}")
	set (SOCI_VERSION ${MY_TMP})
  endif (SOCI_CONFIG)
endif (UNIX)

# Determine whether the headers are buried
if (EXISTS ${SOCI_INCLUDE_DIR}/core)
  # The SOCI headers are buried
  message (STATUS "SOCI headers are buried")
  add_definitions (-DSOCI_HEADERS_BURIED -DSOCI_MYSQL_HEADERS_BURIED)
else (EXISTS ${SOCI_INCLUDE_DIR}/core)
  # The SOCI headers are not buried
  message (STATUS "SOCI headers are not buried")
endif (EXISTS ${SOCI_INCLUDE_DIR}/core)

# Check for SOCI library.
set (CHECK_LIBRARIES soci_core soci_core-gcc-3_0)
if (SOCI_LIBRARY_DIR)
  find_library (SOCI_LIBRARIES
    NAMES ${CHECK_LIBRARIES}
    PATHS ${SOCI_LIBRARY_DIR}
    NO_DEFAULT_PATH)
else (SOCI_LIBRARY_DIR)
  find_library (SOCI_LIBRARIES
    NAMES ${CHECK_LIBRARIES})
endif (SOCI_LIBRARY_DIR)

##
# Check that the just (above) defined variables are valid paths:
#  - SOCI_LIBRARIES
#  - SOCI_INCLUDE_DIR
# In that case, SOCI_FOUND is set to True.

# Given the way those variables have been calculated, they should
# either be defined or correspond to valid paths. We use the
# find_package_handle_standard_args() CMake macro to have a standard behaviour.
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SOCI 
  REQUIRED_VARS SOCI_LIBRARIES SOCI_INCLUDE_DIR
  VERSION_VAR SOCI_VERSION)

if (SOCI_FOUND)
  mark_as_advanced (SOCI_FOUND SOCI_LIBRARIES SOCI_INCLUDE_DIR)
else (SOCI_FOUND)
  message (FATAL_ERROR "Could not find the SOCI libraries! Please install the development-libraries and headers (e.g., 'soci-devel' for Fedora/RedHat).")
endif (SOCI_FOUND)
