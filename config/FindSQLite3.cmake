#
# Find the SQLite3 client includes and library
# 

# This module defines
# SQLITE3_VERSION     - The SQLite3 version
# SQLITE3_INCLUDE_DIR - Where to find sqlite3.h
# SQLITE3_LIBRARIES   - The libraries to link against to connect to SQLite3
# SQLITE3_LIBRARY     - Where to find the SQLite3 library (not for general use).
# SQLITE3_FOUND       - If false, SQLite3 cannot be used.

# Search for the sqlite3 command-line program
find_program (SQLITE3 sqlite3)
if (NOT SQLITE3)
  message (FATAL_ERROR "Could not find the sqlite3 command-line program! Please install it (e.g., 'sqlite3-devel' for Fedora/RedHat/CentOS).")
else (NOT SQLITE3)
  exec_program (sqlite3 ARGS --version OUTPUT_VARIABLE MY_TMP)
  string (REGEX REPLACE "([0-9.]+) .*" "\\1" SQLITE3_VERSION
	"${MY_TMP}")
  message (STATUS "Found SQLite3 version: ${SQLITE3_VERSION}")
endif (NOT SQLITE3)

# Search for the SQLite3 C/C++ header file
find_path (SQLITE3_INCLUDE_DIR sqlite3.h)

# Search for the SQLite3 library
find_library (SQLITE3_LIBRARY NAMES sqlite3)

##
# Check that the just (above) defined variables are valid paths:
#  - SQLITE3_LIBRARY
#  - SQLITE3_INCLUDE_DIR
# In that case, SQLITE3_FOUND is set to True.

# Given the way those variables have been calculated, they should
# either be defined or correspond to valid paths. We use the
# find_package_handle_standard_args() CMake macro to have a standard behaviour.
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (SQLite3
	REQUIRED_VARS SQLITE3_LIBRARY SQLITE3_INCLUDE_DIR
	VERSION_VAR SQLITE3_VERSION)

if (SQLITE3_FOUND)
  set (SQLITE3_LIBRARIES ${SQLITE3_LIBRARY})
  mark_as_advanced (SQLITE3_FOUND SQLITE3_LIBRARY SQLITE3_LIBRARIES
	SQLITE3_EXTRA_LIBRARIES SQLITE3_INCLUDE_DIR)
  message (STATUS "Found SQLite3 version: ${SQLITE3_VERSION}")
else (SQLITE3_FOUND)
  message (FATAL_ERROR "Could not find the SQLite3 libraries! Please install the development-libraries and headers (e.g., 'sqlite3-devel' for Fedora/RedHat/CentOS).")
endif (SQLITE3_FOUND)
