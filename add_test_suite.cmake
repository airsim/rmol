###############################################################
function(
            ## Function name 
            add_test_suite 
            ## Argument list
            name           # Test name
            source_list    # List of sources
                           # ... libraries to link with (up to 5)
        )

  add_executable(${name} ${source_list})

  target_link_libraries(${name} ${ARGV2} ${ARGV3} ${ARGV4} ${ARGV5} ${ARGV6})

	if ( WIN32 )
	    add_test(${name} ${name}.exe)
	else ()
	    add_test(${name} ${name})
	endif ()

endfunction(add_test_suite)
###############################################################


###############################################################
# This is similar to the previous ones but we check if the test
# is in the given list.
###############################################################
function(
            ## Function name 
            add_test_suite_if 
            ## Argument list
            list           # List to check against
            name           # Test name
            source_list    # List of sources
                           # ... libraries to link with (up to 5)
        )

  list ( FIND list ${name}  TO_BE_COMPILED ) 

  if ( TO_BE_COMPILED GREATER -1 )

    add_test_suite(${name} ${source_list} ${ARGN})

  endif ()

endfunction(add_test_suite_if)
###############################################################


