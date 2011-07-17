#
# AirRAC Tests
#
if (Boost_FOUND)

  # CMake macro (defined in config/add_test_suite.cmake)
  include (add_test_suite)

  enable_testing() 

  # * AirRAC Test Suite
  #file (GLOB airractest_SOURCES *.cpp)
  set (TEST_TARGET AirracTest)
  set (airractest_SOURCES YieldTestSuite.cpp)
  add_test_suite (${TEST_TARGET} "${airractest_SOURCES}"
    ${AIRRAC_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # * Next test suite
  # ...

  # Don't forget to add the test suite to the DEPENDS argument list of
  # the 'check' target within the test/CMakeLists.txt file
  add_custom_target (check${TEST_TARGET} COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS ${TEST_TARGET})

endif()
