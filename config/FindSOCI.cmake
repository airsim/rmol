##
##  Copyright 2009 MERETHIS
##  This file is part of CentreonBroker.
##  See http://svn.centreon.com/trunk/centreon-broker/build/CMake/SOCIConfig.cmake
##
##  CentreonBroker is free software: you can redistribute it and/or modify it
##  under the terms of the GNU General Public License as published by the Free
##  Software Foundation, either version 2 of the License, or (at your option)
##  any later version.
##
##  CentreonBroker is distributed in the hope that it will be useful, but
##  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
##  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
##  for more details.
##
##  You should have received a copy of the GNU General Public License along
##  with CentreonBroker.  If not, see <http://www.gnu.org/licenses/>.
##
##  For more information : contact@centreon.com
##

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
if (SOCI_INCLUDE_DIR)
  message (STATUS "Found SOCI headers in ${SOCI_INCLUDE_DIR}")
else (SOCI_INCLUDE_DIR)
  message (FATAL_ERROR "Could not find SOCI headers")
endif (SOCI_INCLUDE_DIR)

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
	set (SOCI_VERSION ${MY_TMP})
  endif (SOCI_CONFIG)
endif (UNIX)

# Determine whether the headers are buried
if (EXISTS "${SOCI_INCLUDE_DIR}/core")
  # The SOCI headers are buried
  message (STATUS "SOCI headers are buried")
  add_definitions (-DSOCI_HEADERS_BURIED -DSOCI_MYSQL_HEADERS_BURIED)
else (EXISTS "${SOCI_INCLUDE_DIR}/core")
  # The SOCI headers are not buried
  message (STATUS "SOCI headers are not buried")
endif (EXISTS "${SOCI_INCLUDE_DIR}/core")

# Check for SOCI library.
set (CHECK_LIBRARIES soci_core soci_core-gcc-3_0)
if (SOCI_LIBRARY_DIR)
  find_library(SOCI_LIBRARIES
    NAMES ${CHECK_LIBRARIES}
    PATHS ${SOCI_LIBRARY_DIR}
    NO_DEFAULT_PATH)
else (SOCI_LIBRARY_DIR)
  find_library(SOCI_LIBRARIES
    NAMES ${CHECK_LIBRARIES})
endif (SOCI_LIBRARY_DIR)

if (SOCI_LIBRARIES)
  message(STATUS "Found SOCI library ${SOCI_LIBRARIES}")
else (SOCI_LIBRARIES)
  message(FATAL_ERROR "Could not find SOCI library")
endif (SOCI_LIBRARIES)

#
set (SOCI_FOUND true)
mark_as_advanced (SOCI_FOUND)
