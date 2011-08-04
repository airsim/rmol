# - Try to find ZeroMQ headers and libraries
#
# Usage of this module as follows:
#
#     find_package(ZeroMQ)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  ZeroMQ_ROOT_DIR  Set this variable to the root installation of
#                            ZeroMQ if the module has problems finding 
#                            the proper installation path.
#
# Variables defined by this module:
#
#  ZEROMQ_FOUND              System has ZeroMQ libs/headers
#  ZeroMQ_LIBRARIES          The ZeroMQ libraries
#  ZeroMQ_INCLUDE_DIR        The location of ZeroMQ headers

find_path (ZeroMQ_ROOT_DIR
  NAMES include/zmq.hpp)

find_library (ZeroMQ_LIBRARIES
  NAMES zmq
  HINTS ${ZeroMQ_ROOT_DIR}/lib)

find_path (ZeroMQ_INCLUDE_DIR
  NAMES zmq.hpp
  HINTS ${ZeroMQ_ROOT_DIR}/include)

#
set (ZMQ_CFG_FILE ${ZeroMQ_INCLUDE_DIR}/zmq.h)

# Extract the version major level
execute_process (
  COMMAND grep "#define ZMQ_VERSION_MAJOR"
  COMMAND cut -d\  -f3
  RESULT_VARIABLE VERSION_MAJOR_RESULT
  OUTPUT_VARIABLE ZMQ_VERSION_MAJOR
  INPUT_FILE ${ZMQ_CFG_FILE}
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# Extract the version minor level
execute_process (
  COMMAND grep "#define ZMQ_VERSION_MINOR"
  COMMAND cut -d\  -f3
  RESULT_VARIABLE VERSION_MINOR_RESULT
  OUTPUT_VARIABLE ZMQ_VERSION_MINOR
  INPUT_FILE ${ZMQ_CFG_FILE}
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# Extract the version patch level
execute_process (
  COMMAND grep "#define ZMQ_VERSION_PATCH"
  COMMAND cut -d\  -f3
  RESULT_VARIABLE VERSION_PATCH_RESULT
  OUTPUT_VARIABLE ZMQ_VERSION_PATCH
  INPUT_FILE ${ZMQ_CFG_FILE}
  OUTPUT_STRIP_TRAILING_WHITESPACE)

#
set (ZeroMQ_VERSION "${ZMQ_VERSION_MAJOR}.${ZMQ_VERSION_MINOR}")

##
# Check that the just (above) defined variables are valid paths:
#  - ZeroMQ_LIBRARIES
#  - ZeroMQ_INCLUDE_DIR
# In that case, ZEROMQ_FOUND is set to True.

# Given the way those variables have been calculated, they should
# either be defined or correspond to valid paths. We use the
# find_package_handle_standard_args() CMake macro to have a standard behaviour.
include (FindPackageHandleStandardArgs)
if (${CMAKE_VERSION} VERSION_GREATER 2.8.4)
  find_package_handle_standard_args (ZeroMQ 
	REQUIRED_VARS ZeroMQ_LIBRARIES ZeroMQ_INCLUDE_DIR
	VERSION_VAR ZeroMQ_VERSION)
else (${CMAKE_VERSION} VERSION_GREATER 2.8.4)
  find_package_handle_standard_args (ZeroMQ 
	DEFAULT_MSG ZeroMQ_LIBRARIES ZeroMQ_INCLUDE_DIR)
endif (${CMAKE_VERSION} VERSION_GREATER 2.8.4)

if (ZEROMQ_FOUND)
  mark_as_advanced (ZEROMQ_FOUND ZeroMQ_VERSION ZeroMQ_ROOT_DIR
	ZeroMQ_LIBRARIES ZeroMQ_INCLUDE_DIR)
  message (STATUS "Found ZeroMQ version: ${ZeroMQ_VERSION}")
else (ZEROMQ_FOUND)
  message (FATAL_ERROR "Could not find the ZeroMQ libraries! Please install the development-libraries and headers (e.g., 'zeromq-devel' for Fedora/RedHat).")
endif (ZEROMQ_FOUND)

