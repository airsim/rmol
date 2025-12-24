#
# GNU Readline library finder
#
# - Try to find readline include dirs and libraries 
#
# Usage of this module as follows:
#
#     find_package(Readline)
#
# Variables used by this module, they can change the default behaviour and need
# to be set before calling find_package:
#
#  Readline_ROOT_DIR         Set this variable to the root installation of
#                            readline if the module has problems finding the
#                            proper installation path.
#
# Variables defined by this module:
#
#  Readline_FOUND            System has readline, include and lib dirs found
#  Readline_VERSION          The Readline version
#  Readline_VERSION_MAJOR    The Readline major version
#  Readline_VERSION_MINOR    The Readline minor version
#  Readline_INCLUDE_DIR      The readline include directories
#  Readline_LIBRARY          The readline library
#

find_path (Readline_ROOT_DIR
  NAMES include/readline/readline.h
)

find_path (Readline_INCLUDE_DIR
  NAMES readline/readline.h
  HINTS ${Readline_ROOT_DIR}/include
)
  
find_library (Readline_LIBRARY
  NAMES readline
  HINTS ${Readline_ROOT_DIR}/lib
)

  # Extract version information from readline.h
  if (Readline_INCLUDE_DIR)
	# Extract Readline_VERSION from readline.h
	# Read the whole file:
	set (Readline_VERSION "")
	set (Readline_VERSION_MAJOR "")
	set (Readline_VERSION_MINOR "")
	file (READ "${Readline_INCLUDE_DIR}/readline/readline.h"
	  _readline_VERSION_HPP_CONTENTS)
	if (Readline_DEBUG)
      message (STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
		"location of readline.h: ${Readline_INCLUDE_DIR}/readline/readline.h")
	endif (Readline_DEBUG)
  
	string (REGEX REPLACE ".*#define RL_READLINE_VERSION\t([0-9x]*).*" "\\1"
	  Readline_VERSION "${_readline_VERSION_HPP_CONTENTS}")

	string (REGEX REPLACE ".*#define RL_VERSION_MAJOR\t([0-9]*).*" "\\1"
	  Readline_VERSION_MAJOR "${_readline_VERSION_HPP_CONTENTS}")

	string (REGEX REPLACE ".*#define RL_VERSION_MINOR\t([0-9]*).*" "\\1"
	  Readline_VERSION_MINOR "${_readline_VERSION_HPP_CONTENTS}")

	set (Readline_VERSION ${Readline_VERSION}
	  CACHE INTERNAL "The version number for Readline")

	set (Readline_VERSION_MAJOR ${Readline_VERSION_MAJOR}
	  CACHE INTERNAL "The major version number for Readline")

	set (Readline_VERSION_MINOR ${Readline_VERSION_MINOR}
	  CACHE INTERNAL "The minor version number for Readline")

	#
	if (Readline_DEBUG)
      message (STATUS "[ ${CMAKE_CURRENT_LIST_FILE}:${CMAKE_CURRENT_LIST_LINE} ] "
		"readline.h reveals Readline ${Readline_VERSION}")
	endif (Readline_DEBUG)
	
  else (Readline_INCLUDE_DIR)
	set (Readline_ERROR_REASON
      "${Readline_ERROR_REASON}Unable to find the Readline header files. Please set Readline_ROOT_DIR to the root directory containing Readline or Readline_INCLUDE_DIR to the directory containing Readline's headers.")
  endif (Readline_INCLUDE_DIR)

if(Readline_INCLUDE_DIR AND Readline_LIBRARY AND Ncurses_LIBRARY)
  set(Readline_FOUND TRUE)
else(Readline_INCLUDE_DIR AND Readline_LIBRARY AND Ncurses_LIBRARY)
  FIND_LIBRARY(Readline_LIBRARY NAMES readline)
  include(FindPackageHandleStandardArgs)
  FIND_PACKAGE_HANDLE_STANDARD_ARGS(Readline DEFAULT_MSG Readline_INCLUDE_DIR Readline_LIBRARY )
  MARK_AS_ADVANCED(Readline_INCLUDE_DIR Readline_LIBRARY)
endif(Readline_INCLUDE_DIR AND Readline_LIBRARY AND Ncurses_LIBRARY)

mark_as_advanced(
  Readline_ROOT_DIR
  Readline_VERSION
  Readline_VERSION_MAJOR
  Readline_VERSION_MINOR
  Readline_INCLUDE_DIR
  Readline_LIBRARY
)
 
