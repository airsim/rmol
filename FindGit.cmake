#
set (Git_FOUND FALSE)
 
find_program (Git_EXECUTABLE git DOC "git command line client")
mark_as_advanced (Git_EXECUTABLE)
 
if (Git_EXECUTABLE)
  set (Git_FOUND TRUE)

  macro (Git_WC_INFO dir prefix)
    execute_process (COMMAND ${Git_EXECUTABLE} rev-list -n 1 HEAD
      WORKING_DIRECTORY ${dir}
      ERROR_VARIABLE Git_error
      OUTPUT_VARIABLE ${prefix}_WC_REVISION_HASH
      OUTPUT_STRIP_TRAILING_WHITESPACE)
    if (NOT ${Git_error} EQUAL 0)
      message (SEND_ERROR 
	"Command \"${Git_EXECUTBALE} rev-list -n 1 HEAD\" in directory ${dir} failed with output:\n${Git_error}")
    else (NOT ${Git_error} EQUAL 0)
      execute_process (COMMAND ${Git_EXECUTABLE}
	name-rev ${${prefix}_WC_REVISION_HASH}
        WORKING_DIRECTORY ${dir}
        OUTPUT_VARIABLE ${prefix}_WC_REVISION_NAME
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    endif (NOT ${Git_error} EQUAL 0)
  endmacro (Git_WC_INFO)
endif (Git_EXECUTABLE)
 
if (NOT Git_FOUND)
  if (NOT Git_FIND_QUIETLY)
    message (STATUS "Git was not found")
  else (NOT Git_FIND_QUIETLY)
    if (Git_FIND_REQUIRED)
      message (FATAL_ERROR "Git was not found")
    endif (Git_FIND_REQUIRED)
  endif (NOT Git_FIND_QUIETLY)
endif (NOT Git_FOUND)
