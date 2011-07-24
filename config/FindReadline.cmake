#
# GNU Readline library finder
#
if (READLINE_INCLUDE_DIR AND READLINE_LIBRARY AND NCURSES_LIBRARY)
  set (READLINE_FOUND True)
else (READLINE_INCLUDE_DIR AND READLINE_LIBRARY AND NCURSES_LIBRARY)
  find_path (READLINE_INCLUDE_DIR readline/readline.h /usr/include/readline)
  
  find_library (READLINE_LIBRARY NAMES readline)
endif (READLINE_INCLUDE_DIR AND READLINE_LIBRARY AND NCURSES_LIBRARY)

#
set (RL_CFG_FILE ${READLINE_INCLUDE_DIR}/readline/readline.h)

# The lines specifying the Readline version are like the following:
#define RL_READLINE_VERSION [TAB] 0x0601      /* Readline 6.0 */
#define RL_VERSION_MAJOR [TAB] 6
#define RL_VERSION_MINOR [TAB] 1

# Extract the version major level
execute_process (
  COMMAND grep "#define RL_READLINE_VERSION"
  COMMAND cut -f2
  COMMAND cut -dx -f2
  RESULT_VARIABLE VERSION_MAJOR_RESULT
  OUTPUT_VARIABLE RL_READLINE_VERSION
  INPUT_FILE ${RL_CFG_FILE}
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# Extract the version major level
execute_process (
  COMMAND grep "#define RL_VERSION_MAJOR"
  COMMAND cut -f2
  RESULT_VARIABLE VERSION_MAJOR_RESULT
  OUTPUT_VARIABLE RL_VERSION_MAJOR
  INPUT_FILE ${RL_CFG_FILE}
  OUTPUT_STRIP_TRAILING_WHITESPACE)

# Extract the version minor level
execute_process (
  COMMAND grep "#define RL_VERSION_MINOR"
  COMMAND cut -f2
  RESULT_VARIABLE VERSION_MINOR_RESULT
  OUTPUT_VARIABLE RL_VERSION_MINOR
  INPUT_FILE ${RL_CFG_FILE}
  OUTPUT_STRIP_TRAILING_WHITESPACE)

#
set (READLINE_VERSION "${RL_VERSION_MAJOR}.${RL_VERSION_MINOR}")

##
# Check that the just (above) defined variables are valid paths:
#  - READLINE_LIBRARY
#  - READLINE_INCLUDE_DIR
# In that case, READLINE_FOUND is set to True.

# Given the way those variables have been calculated, they should
# either be defined or correspond to valid paths. We use the
# find_package_handle_standard_args() CMake macro to have a standard 
# behaviour.
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (Readline 
  REQUIRED_VARS READLINE_INCLUDE_DIR READLINE_LIBRARY
  VERSION_VAR READLINE_VERSION)

if (READLINE_FOUND)
  mark_as_advanced (READLINE_INCLUDE_DIR READLINE_LIBRARY)
  message (STATUS "Found Readline version: ${READLINE_VERSION}")
else (READLINE_FOUND)
  message (FATAL_ERROR "Could not find the Readline libraries! Please install the development-libraries and headers (e.g., 'readline-devel' for Fedora/RedHat).")
endif (READLINE_FOUND)
