# 
# Find SOCI includes and library for core and SQLite.
# Following are the variables defined by the FindSOCI*.cmake macros:
#  SOCI_VERSION           - The SOCI version, e.g, 300100
#  SOCI_LIB_VERSION       - The SOCI library version, e.g., 3_1_0
#  SOCI_HUMAN_VERSION     - The SOCI human-readable version, e.g., 3.1.0
#  SOCI_INCLUDE_DIR       - Where to find soci.h, etc.
#  SOCI_LIBRARIES         - List of libraries when using SOCI.
#  SOCI_FOUND             - Whether SOCI has been found
#  SOCISQLITE_INCLUDE_DIR - Where to find soci-sqlite3.h, etc.
#  SOCISQLITE_LIBRARIES   - List of libraries when using SOCI SQLite.
#  SOCISQLITE_FOUND       - Whether the SOCI SQLite library has been found
#
# Note: it is assumed that the _required_version variable be set before 
# calling 'find_package (SOCISQLite)'

# First, check for SOCI core
find_package (SOCI ${_required_version} REQUIRED)

# Check for SOCI SQLite main header.
set (CHECK_HEADERS soci/sqlite3/soci-sqlite3.h)
if (SOCISQLITE_INCLUDE_DIR)
  find_path (SOCISQLITE_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATHS ${SOCI_SQLITE_INCLUDE_DIR}
    NO_DEFAULT_PATH)
else (SOCISQLITE_INCLUDE_DIR)
  find_path (SOCISQLITE_INCLUDE_DIR
    NAMES ${CHECK_HEADERS}
    PATHS ${SOCI_INCLUDE_DIR})
endif (SOCISQLITE_INCLUDE_DIR)

# Check for SOCI SQLite library
set (CHECK_LIBRARIES soci_sqlite3 soci_sqlite3-gcc-3_0)
if (SOCISQLITE_LIBRARY_DIR)
  find_library (SOCISQLITE_LIBRARIES
    NAMES ${CHECK_LIBRARIES}
    PATHS ${SOCISQLITE_LIBRARY_DIR}
    NO_DEFAULT_PATH)
else (SOCISQLITE_LIBRARY_DIR)
  find_library (SOCISQLITE_LIBRARIES
    NAMES ${CHECK_LIBRARIES})
endif (SOCISQLITE_LIBRARY_DIR)

#
include (FindPackageHandleStandardArgs)
if (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
  find_package_handle_standard_args (SOCISQLite 
	REQUIRED_VARS SOCISQLITE_LIBRARIES SOCISQLITE_INCLUDE_DIR
	VERSION_VAR SOCI_HUMAN_VERSION)
else (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
  find_package_handle_standard_args (SOCISQLite 
	DEFAULT_MSG SOCISQLITE_LIBRARIES SOCISQLITE_INCLUDE_DIR)
endif (${CMAKE_VERSION} VERSION_GREATER 2.8.1)

if (SOCISQLITE_FOUND)
  mark_as_advanced (SOCISQLITE_FOUND SOCISQLITE_LIBRARIES SOCISQLITE_INCLUDE_DIR)
else (SOCISQLITE_FOUND)
  message (FATAL_ERROR "Could not find the SOCI SQLite libraries! Please install the development-libraries and headers (e.g., 'soci-sqlite3-devel' for Fedora/RedHat).")
endif (SOCISQLITE_FOUND)

