#
# RMOL Tests
#
set (MODULE_NAME rmol)
set (MODULE_LIB_TARGET ${MODULE_NAME}lib)

if (Boost_FOUND)

  # CMake macro (defined in config/add_test_suite.cmake)
  include (add_test_suite)

  enable_testing() 

  # * Unconstrainer Test Suite
  set (UNCONSTRAINER_TEST_TARGET UnconstrainerTest)
  set (unconstrainer_test_SOURCES UnconstrainerTestSuite.cpp)
  add_test_suite (${UNCONSTRAINER_TEST_TARGET} "${unconstrainer_test_SOURCES}"
    ${MODULE_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # * Forecaster Test Suite
  set (FORECASTER_TEST_TARGET ForecasterTest)
  set (forecaster_test_SOURCES ForecasterTestSuite.cpp)
  add_test_suite (${FORECASTER_TEST_TARGET} "${forecaster_test_SOURCES}"
    ${MODULE_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # * Optimise Test Suite
  set (OPTIMISE_TEST_TARGET OptimiseTest)
  set (optimise_test_SOURCES OptimiseTestSuite.cpp)
  add_test_suite (${OPTIMISE_TEST_TARGET} "${optimise_test_SOURCES}"
    ${MODULE_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # * BOMs for Forecaster Test Suite
  set (BOMSFORFORECASTER_TEST_TARGET BOMsForForecasterTest)
  set (bomsforforecaster_test_SOURCES OptimiseTestSuite.cpp)
  add_test_suite (${BOMSFORFORECASTER_TEST_TARGET}
    "${bomsforforecaster_test_SOURCES}"
    ${MODULE_LIB_TARGET} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

  # * Next test suite
  # ...

  # Don't forget to add the full test suite to the DEPENDS argument list of
  # the 'check' target within the ../test/CMakeLists.txt file.
  add_custom_target (check_${MODULE_NAME}
    COMMAND ${CMAKE_CTEST_COMMAND} 
    DEPENDS ${UNCONSTRAINER_TEST_TARGET} ${FORECASTER_TEST_TARGET}
    ${OPTIMISE_TEST_TARGET} ${BOMSFORFORECASTER_TEST_TARGET})


endif()
