#
# AirRAC Tests
#
set (MODULE_NAME airrac)
set (MODULE_LIB_TARGET ${MODULE_NAME}lib)

if (Boost_FOUND)

  # CMake macro (defined in config/add_test_suite.cmake)
  include (add_test_suite)

  enable_testing() 

  # * AirRAC Test Suite
  set (YIELD_TEST_TARGET YieldTestSuite)
  set (yield_test_SOURCES YieldTestSuite.cpp)
  add_test_suite (${YIELD_TEST_TARGET} "${yield_test_SOURCES}"
    ${MODULE_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # * Next test suite
  # ...

  # Don't forget to add the full test suite to the DEPENDS argument list of
  # the 'check' target within the ../test/CMakeLists.txt file.
  add_custom_target (check_${MODULE_NAME}
    COMMAND ${CMAKE_CTEST_COMMAND} 
    DEPENDS ${YIELD_TEST_TARGET})

endif()
