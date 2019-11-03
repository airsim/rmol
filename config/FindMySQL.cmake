#
# Find the MySQL client includes and library
# 

# This module defines
# MYSQL_VERSION     - The MySQL version
# MYSQL_INCLUDE_DIR - Where to find mysql.h
# MYSQL_LIBRARIES   - The libraries to link against to connect to MySQL
# MYSQL_LIBRARY     - Where to find the MySQL library (not for general use).
# MYSQL_FOUND       - If false, you cannot build anything that requires MySQL.

if (UNIX)
  set (MYSQL_CONFIG_PREFER_PATH "$ENV{MYSQL_HOME}/bin" CACHE FILEPATH
    "preferred path to MySQL (mysql_config)")

  find_program (MYSQL_CONFIG mysql_config
    ${MYSQL_CONFIG_PREFER_PATH}
    /usr/local/mysql/bin/
    /usr/local/bin/
    /usr/bin/
    /usr/local/opt/mysql-client/bin)

  if (MYSQL_CONFIG)
    message (STATUS "Using mysql-config: ${MYSQL_CONFIG}")
    # Set VERSION
    exec_program (${MYSQL_CONFIG} ARGS --version OUTPUT_VARIABLE MY_TMP)
	set (MYSQL_VERSION ${MY_TMP})

    # Set INCLUDE_DIR
    exec_program (${MYSQL_CONFIG} ARGS --include OUTPUT_VARIABLE MY_TMP)

    string (REGEX REPLACE "-I([^ ]*)( .*)?" "\\1" MY_TMP "${MY_TMP}")
    set (MYSQL_ADD_INCLUDE_PATH ${MY_TMP} CACHE FILEPATH INTERNAL)
    #message("[DEBUG] MYSQL ADD_INCLUDE_PATH : ${MYSQL_ADD_INCLUDE_PATH}")
    # set LIBRARY_DIR
    exec_program (${MYSQL_CONFIG} ARGS --libs_r OUTPUT_VARIABLE MY_TMP)

    set (MYSQL_ADD_LIBRARIES "")
    string (REGEX MATCHALL "-l[^ ]*" MYSQL_LIB_LIST "${MY_TMP}")
    foreach (LIB ${MYSQL_LIB_LIST})
      string (REGEX REPLACE "[ ]*-l([^ ]*)" "\\1" LIB "${LIB}")
      list (APPEND MYSQL_ADD_LIBRARIES "${LIB}")
      #message("[DEBUG] MYSQL ADD_LIBRARIES : ${MYSQL_ADD_LIBRARIES}")
    endforeach (LIB ${MYSQL_LIB_LIST})

    set (MYSQL_ADD_LIBRARIES_PATH "")
    string (REGEX MATCHALL "-L[^ ]*" MYSQL_LIBDIR_LIST "${MY_TMP}")
    foreach (LIB ${MYSQL_LIBDIR_LIST})
      string (REGEX REPLACE "[ ]*-L([^ ]*)" "\\1" LIB "${LIB}")
      list (APPEND MYSQL_ADD_LIBRARIES_PATH "${LIB}")
      #message("[DEBUG] MYSQL ADD_LIBRARIES_PATH : ${MYSQL_ADD_LIBRARIES_PATH}")
    endforeach (LIB ${MYSQL_LIBS})

  else (MYSQL_CONFIG)
    set (MYSQL_ADD_LIBRARIES "")
    list (APPEND MYSQL_ADD_LIBRARIES "mysqlclient_r")
  endif (MYSQL_CONFIG)
endif (UNIX)

find_path (MYSQL_INCLUDE_DIR
  NAMES
    mysql.h
  PATHS
    ${MYSQL_ADD_INCLUDE_PATH}
    /usr/include
    /usr/include/mysql
    /usr/local/include
    /usr/local/include/mysql
    /usr/local/mysql/include
    "C:/Program Files/MySQL/include"
    "C:/Program Files/MySQL/MySQL Server 5.0/include"
    "C:/Program Files/MySQL/MySQL Server 5.1/include"
    "C:/MySQL/include"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.0;Location]/include"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.1;Location]/include"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.0;Location]/include"
    "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.1;Location]/include"
    "c:/msys/local/include"
  DOC
    "Specify the directory containing mysql.h.")

if (UNIX)
foreach (LIB ${MYSQL_ADD_LIBRARIES})
  find_library (MYSQL_LIBRARY 
    NAMES
      mysql libmysql ${LIB}
    PATHS
      ${MYSQL_ADD_LIBRARIES_PATH}
      /usr/lib
      /usr/lib/mysql
      /usr/local/lib
      /usr/local/lib/mysql
      /usr/local/mysql/lib
    DOC "Specify the location of the mysql library here.")
endforeach (LIB ${MYSQL_ADD_LIBRARY})
endif (UNIX)

if (WIN32)
  find_library (MYSQL_LIBRARY 
    NAMES
      mysql libmysql ${LIB}
    PATHS
      ${MYSQL_ADD_LIBRARIES_PATH}
      "C:/Program Files/MySQL/lib"
      "C:/Program Files/MySQL/MySQL Server 5.0/lib/opt"
      "C:/Program Files/MySQL/MySQL Server 5.1/lib/opt"
      "C:/MySQL/lib/debug"
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.0;Location]/lib/opt"
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\MySQL AB\\MySQL Server 5.1;Location]/lib/opt"
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.0;Location]/lib/opt"
      "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Wow6432Node\\MySQL AB\\MySQL Server 5.1;Location]/lib/opt"
      "c:/msys/local/include"
    DOC "Specify the location of the mysql library here.")
endif (WIN32)

# On Windows you typically don't need to include any extra libraries
# to build MYSQL stuff.

if (NOT WIN32)
  find_library (MYSQL_EXTRA_LIBRARIES
    NAMES z zlib
    PATHS /usr/lib /usr/local/lib
    DOC "If more libraries are necessary to link with a MySQL client (typically zlib), specify them here.")
else (NOT WIN32)
  unset (MYSQL_EXTRA_LIBRARIES)
endif (NOT WIN32)

##
# Check that the just (above) defined variables are valid paths:
#  - MYSQL_LIBRARY
#  - MYSQL_INCLUDE_DIR
# In that case, MYSQL_FOUND is set to True.

# Given the way those variables have been calculated, they should
# either be defined or correspond to valid paths. We use the
# find_package_handle_standard_args() CMake macro to have a standard behaviour.
include (FindPackageHandleStandardArgs)
if (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
  find_package_handle_standard_args (MySQL
	REQUIRED_VARS MYSQL_LIBRARY MYSQL_INCLUDE_DIR
	VERSION_VAR MYSQL_VERSION)
else (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
  find_package_handle_standard_args (MySQL
	DEFAULT_MSG MYSQL_LIBRARY MYSQL_INCLUDE_DIR)
endif (${CMAKE_VERSION} VERSION_GREATER 2.8.1)

if (MYSQL_FOUND)
  set (MYSQL_LIBRARIES ${MYSQL_LIBRARY})
  mark_as_advanced (MYSQL_FOUND MYSQL_LIBRARY MYSQL_LIBRARIES
	MYSQL_EXTRA_LIBRARIES MYSQL_INCLUDE_DIR)
  message (STATUS "Found MySQL version: ${MYSQL_VERSION}")
else (MYSQL_FOUND)
  message (FATAL_ERROR "Could not find the MYSQL libraries! Please install the development-libraries and headers (e.g., 'mysql-devel' for Fedora/RedHat).")
endif (MYSQL_FOUND)
