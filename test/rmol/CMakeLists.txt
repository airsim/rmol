#
# RMOL Tests
#
module_set_name (rmol)


##
# Specify each test suite configuration

# * Unconstrainer Test Suite
module_test_add_suite (UnconstrainerTest UnconstrainerTestSuite.cpp)

# * Forecaster Test Suite
module_test_add_suite (ForecasterTest ForecasterTestSuite.cpp)

# * Optimise Test Suite
module_test_add_suite (OptimiseTest OptimiseTestSuite.cpp)

# * BOMs for Forecaster Test Suite
module_test_add_suite (BOMsForForecasterTest bomsforforecaster.cpp)


##
# Register all the test suites to be built and performed
module_test_build_all ()
