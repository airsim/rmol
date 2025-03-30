# 
# Find SOCI includes and library for core and MySQL.
# Following are the variables defined by the FindSOCI*.cmake macros:
#  SOCI_VERSION          - The SOCI version, e.g, 300100
#  SOCI_LIB_VERSION      - The SOCI library version, e.g., 3_1_0
#  SOCI_HUMAN_VERSION    - The SOCI human-readable version, e.g., 3.1.0
#  SOCI_INCLUDE_DIR      - Where to find soci.h, etc.
#  SOCI_LIBRARIES        - List of libraries when using SOCI.
#  SOCI_FOUND            - Whether SOCI has been found
#  SOCIMYSQL_INCLUDE_DIR - Where to find soci-mysql.h, etc.
#  SOCIMYSQL_LIBRARIES   - List of libraries when using SOCI MySQL.
#  SOCIMYSQL_FOUND       - Whether the SOCI MySQL library has been found
#
# Note: it is assumed that the _required_version variable be set before 
# calling 'find_package (SOCIMySQL)'

# First, check for SOCI core
find_package (SOCI ${_required_version} REQUIRED)

# Check for SOCI MySQL main header.
set (CHECK_HEADERS soci/mysql/soci-mysql.h)
if (SOCIMYSQL_INCLUDE_DIR)
  find_path (SOCIMYSQL_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATHS ${SOCI_MYSQL_INCLUDE_DIR}
    NO_DEFAULT_PATH)
else (SOCIMYSQL_INCLUDE_DIR)
  find_path (SOCIMYSQL_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATHS ${SOCI_INCLUDE_DIR})
endif (SOCIMYSQL_INCLUDE_DIR)

# Check for SOCI MySQL library
set (CHECK_LIBRARIES soci_mysql soci_mysql-gcc-3_0)
if (SOCIMYSQL_LIBRARY_DIR)
  find_library (SOCIMYSQL_LIBRARIES
    NAMES ${CHECK_LIBRARIES}
    PATHS ${SOCIMYSQL_LIBRARY_DIR}
    NO_DEFAULT_PATH)
else (SOCIMYSQL_LIBRARY_DIR)
  find_library (SOCIMYSQL_LIBRARIES
    NAMES ${CHECK_LIBRARIES})
    #PATH_SUFFIXES soci)
endif (SOCIMYSQL_LIBRARY_DIR)

#
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SOCIMySQL 
  REQUIRED_VARS SOCIMYSQL_LIBRARIES SOCIMYSQL_INCLUDE_DIR
  VERSION_VAR SOCI_HUMAN_VERSION)

if (SOCIMYSQL_FOUND)
  mark_as_advanced (SOCIMYSQL_FOUND SOCIMYSQL_LIBRARIES SOCIMYSQL_INCLUDE_DIR)
else (SOCIMYSQL_FOUND)
  message (FATAL_ERROR "Could not find the SOCI MySQL libraries! Please install the development-libraries and headers (e.g., 'soci-mysql-devel' for Fedora/RedHat).")
endif (SOCIMYSQL_FOUND)

