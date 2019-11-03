# Find SOCI includes and library.
#
#  SOCI_VERSION        - The SOCI version, e.g, 300100
#  SOCI_LIB_VERSION    - The SOCI library version, e.g., 3_1_0
#  SOCI_HUMAN_VERSION  - The SOCI human-readable version, e.g., 3.1.0
#  SOCI_INCLUDE_DIR    - Where to find soci.h, etc.
#  SOCI_LIBRARIES      - List of libraries when using SOCI.
#  SOCI_FOUND          - Whether SOCI has been found

# Check for SOCI main header.
find_path (_soci_incdir
	NAMES soci/soci.h
)
set (SOCI_INCLUDE_DIR "${_soci_incdir}")

# Extract version information from version.h
if (SOCI_INCLUDE_DIR)
  # Extract SOCI_VERSION and SOCI_LIB_VERSION from version.h
  # Read the whole file:
  set (SOCI_VERSION 0)
  set (SOCI_LIB_VERSION "")
  file (READ "${SOCI_INCLUDE_DIR}/soci/version.h" _soci_VERSION_HPP_CONTENTS)
  if (SOCI_DEBUG)
    message (STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
      "location of soci/version.h: ${SOCI_INCLUDE_DIR}/soci/version.h")
  endif (SOCI_DEBUG)
  
  string (REGEX REPLACE ".*#define SOCI_VERSION ([0-9]+).*" "\\1" SOCI_VERSION
	"${_soci_VERSION_HPP_CONTENTS}")
  string (REGEX REPLACE ".*#define SOCI_LIB_VERSION \"([0-9_]+)\".*" "\\1"
	SOCI_LIB_VERSION "${_soci_VERSION_HPP_CONTENTS}")
  
  set (SOCI_LIB_VERSION ${SOCI_LIB_VERSION} 
	CACHE INTERNAL "The library version string for SOCI libraries")
  set (SOCI_VERSION ${SOCI_VERSION} 
	CACHE INTERNAL "The version number for SOCI libraries")
  
  if (NOT "${SOCI_VERSION}" STREQUAL "0")
    math (EXPR SOCI_MAJOR_VERSION "${SOCI_VERSION} / 100000")
    math (EXPR SOCI_MINOR_VERSION "${SOCI_VERSION} / 100 % 1000")
    math (EXPR SOCI_SUBMINOR_VERSION "${SOCI_VERSION} % 100")
	
    set (SOCI_ERROR_REASON
      "${SOCI_ERROR_REASON}SOCI version: ${SOCI_MAJOR_VERSION}.${SOCI_MINOR_VERSION}.${SOCI_SUBMINOR_VERSION}\nSOCI include path: ${SOCI_INCLUDE_DIR}")
  endif (NOT "${SOCI_VERSION}" STREQUAL "0")

  #
  set (SOCI_HUMAN_VERSION
	"${SOCI_MAJOR_VERSION}.${SOCI_MINOR_VERSION}.${SOCI_SUBMINOR_VERSION}")

  if (SOCI_DEBUG)
    message (STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
      "version.h reveals SOCI ${SOCI_HUMAN_VERSION}")
  endif (SOCI_DEBUG)

else (SOCI_INCLUDE_DIR)
  set (SOCI_ERROR_REASON
    "${SOCI_ERROR_REASON}Unable to find the SOCI header files. Please set SOCI_ROOT to the root directory containing SOCI or SOCI_INCLUDEDIR to the directory containing SOCI's headers.")
endif (SOCI_INCLUDE_DIR)


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
if (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
  find_package_handle_standard_args (SOCI 
	REQUIRED_VARS SOCI_LIBRARIES SOCI_INCLUDE_DIR
	VERSION_VAR SOCI_HUMAN_VERSION)
else (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
  find_package_handle_standard_args (SOCI 
	DEFAULT_MSG SOCI_LIBRARIES SOCI_INCLUDE_DIR)
endif (${CMAKE_VERSION} VERSION_GREATER 2.8.1)

if (SOCI_FOUND)
  mark_as_advanced (SOCI_FOUND SOCI_LIBRARIES SOCI_INCLUDE_DIR)
else (SOCI_FOUND)
  message (FATAL_ERROR "Could not find the SOCI libraries! Please install the development-libraries and headers (e.g., 'soci-devel' for Fedora/RedHat).")
endif (SOCI_FOUND)

