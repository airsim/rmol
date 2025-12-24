# 
# Find SOCI includes and library for core and PostgreSQL.
# Following are the variables defined by the FindSOCI*.cmake macros:
#  SOCI_VERSION          - The SOCI version, e.g, 300100
#  SOCI_LIB_VERSION      - The SOCI library version, e.g., 3_1_0
#  SOCI_HUMAN_VERSION    - The SOCI human-readable version, e.g., 3.1.0
#  SOCI_INCLUDE_DIR      - Where to find soci.h, etc.
#  SOCI_LIBRARIES        - List of libraries when using SOCI.
#  SOCI_FOUND            - Whether SOCI has been found
#  SOCIPostgreSQL_INCLUDE_DIR - Where to find soci-postgresql.h, etc.
#  SOCIPostgreSQL_LIBRARIES   - List of libraries when using SOCI PostgreSQL.
#  SOCIPostgreSQL_FOUND       - Whether the SOCI PostgreSQL library has been found
#
# Note: it is assumed that the _required_version variable be set before 
# calling 'find_package (SOCIPostgreSQL)'

# First, check for SOCI core
find_package (SOCI ${_required_version} REQUIRED)

# Check for SOCI PostgreSQL main header.
set (CHECK_HEADERS soci/postgresql/soci-postgresql.h)
if (SOCIPostgreSQL_INCLUDE_DIR)
  find_path (SOCIPostgreSQL_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATHS ${SOCI_POSTGRESQL_INCLUDE_DIR}
    NO_DEFAULT_PATH)
else (SOCIPostgreSQL_INCLUDE_DIR)
  find_path (SOCIPostgreSQL_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATHS ${SOCI_INCLUDE_DIR})
endif (SOCIPostgreSQL_INCLUDE_DIR)

# Check for SOCI PostgreSQL library
set (CHECK_LIBRARIES soci_postgresql soci_postgresql-gcc-3_0)
if (SOCIPostgreSQL_LIBRARY_DIR)
  find_library (SOCIPostgreSQL_LIBRARIES
    NAMES ${CHECK_LIBRARIES}
    PATHS ${SOCIPostgreSQL_LIBRARY_DIR}
    NO_DEFAULT_PATH)
else (SOCIPostgreSQL_LIBRARY_DIR)
  find_library (SOCIPostgreSQL_LIBRARIES
    NAMES ${CHECK_LIBRARIES}
    PATH_SUFFIXES soci)
endif (SOCIPostgreSQL_LIBRARY_DIR)

#
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SOCIPostgreSQL 
  REQUIRED_VARS SOCIPostgreSQL_LIBRARIES SOCIPostgreSQL_INCLUDE_DIR
  VERSION_VAR SOCI_HUMAN_VERSION)

if (SOCIPostgreSQL_FOUND)
  mark_as_advanced (SOCIPostgreSQL_FOUND SOCIPostgreSQL_LIBRARIES SOCIPostgreSQL_INCLUDE_DIR)
else (SOCIPostgreSQL_FOUND)
  message (FATAL_ERROR "Could not find the SOCI PostgreSQL libraries! Please install the development-libraries and headers (e.g., 'soci-postgresql-devel' for Fedora/RedHat).")
endif (SOCIPostgreSQL_FOUND)

