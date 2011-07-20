# GNU Readline library finder
# From http://www.opensource.apple.com/source/pcre/pcre-4.1/pcre/cmake/FindReadline.cmake
if (READLINE_INCLUDE_DIR AND READLINE_LIBRARY AND NCURSES_LIBRARY)
  set (READLINE_FOUND TRUE)
else (READLINE_INCLUDE_DIR AND READLINE_LIBRARY AND NCURSES_LIBRARY)
  find_path (READLINE_INCLUDE_DIR readline/readline.h /usr/include/readline)
  
  find_library (READLINE_LIBRARY NAMES readline)
  include (FindPackageHandleStandardArgs)
  find_package_handle_standard_args (Readline 
    DEFAULT_MSG READLINE_INCLUDE_DIR READLINE_LIBRARY)

  mark_as_advanced (READLINE_INCLUDE_DIR READLINE_LIBRARY)

endif(READLINE_INCLUDE_DIR AND READLINE_LIBRARY AND NCURSES_LIBRARY)
