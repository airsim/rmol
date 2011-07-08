#
# RMOL Tests
#
if (Boost_FOUND)

  # CMake macro (defined in config/add_test_suite.cmake)
  include (add_test_suite)

  enable_testing() 

  # * Unconstrainer Test Suite
  set (UNCONSTRAINER_TEST_TARGET UnconstrainerTest)
  set (unconstrainer_test_SOURCES UnconstrainerTestSuite.cpp)
  add_test_suite (${FORECASTER_TEST_TARGET} "${unconstrainer_test_SOURCES}"
    ${RMOL_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # Don't forget to add the test suite to the DEPENDS argument list of
  # the 'check' target within the test/CMakeLists.txt file
  add_custom_target (check${UNCONSTRAINER_TEST_TARGET} 
    COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${UNCONSTRAINER_TEST_TARGET})

  # * Forecaster Test Suite
  set (FORECASTER_TEST_TARGET ForecasterTest)
  set (forecaster_test_SOURCES ForecasterTestSuite.cpp)
  add_test_suite (${FORECASTER_TEST_TARGET} "${forecaster_test_SOURCES}"
    ${RMOL_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # Don't forget to add the test suite to the DEPENDS argument list of
  # the 'check' target within the test/CMakeLists.txt file
  add_custom_target (check${FORECASTER_TEST_TARGET} 
    COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${FORECASTER_TEST_TARGET})

  # * Optimise Test Suite
  set (OPTIMISE_TEST_TARGET OptimiseTest)
  set (optimise_test_SOURCES OptimiseTestSuite.cpp)
  add_test_suite (${OPTIMISE_TEST_TARGET} "${optimise_test_SOURCES}"
    ${RMOL_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # Don't forget to add the test suite to the DEPENDS argument list of
  # the 'check' target within the test/CMakeLists.txt file
  add_custom_target (check${OPTIMISE_TEST_TARGET} COMMAND ${CMAKE_CTEST_COMMAND}
    DEPENDS ${OPTIMISE_TEST_TARGET})

  # * BOMs for Forecaster Test Suite
  set (BOMSFORFORECASTER_TEST_TARGET BOMsForForecasterTest)
  set (bomsforforecaster_test_SOURCES OptimiseTestSuite.cpp)
  add_test_suite (${BOMSFORFORECASTER_TEST_TARGET}
    "${bomsforforecaster_test_SOURCES}"
    ${RMOL_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # Don't forget to add the test suite to the DEPENDS argument list of
  # the 'check' target within the test/CMakeLists.txt file
  add_custom_target (check${BOMSFORFORECASTER_TEST_TARGET} 
    COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${BOMSFORFORECASTER_TEST_TARGET})

  # * Next test suite
  # ...

endif()
