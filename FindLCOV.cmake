find_program ( LCOV lcov )
IF(NOT LCOV)
  message (FATAL_ERROR "Could not find the lcov utilities! Please install them (e.g., 'lcov' for Fedora/RedHat).") 
else (NOT LCOV)
  exec_program (lcov ARGS --version OUTPUT_VARIABLE MY_TMP)
  string (REGEX REPLACE "lcov: LCOV version ([0-9].[0-9])" "\\1" LCOV_VERSION
	 "${MY_TMP}")
  message (STATUS "Found lcov version: ${LCOV_VERSION}")
ENDIF(NOT LCOV)
 
 
