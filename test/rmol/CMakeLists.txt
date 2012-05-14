#
# RMOL Tests
#

##
# Specify each test suite configuration

# * BOMs for Forecaster Test Suite
module_test_add_suite (rmol BOMsForForecasterTest bomsforforecaster.cpp)

# * Unconstrainer Test Suite
module_test_add_suite (rmol UnconstrainerTest UnconstrainerTestSuite.cpp)

# * Forecaster Test Suite
module_test_add_suite (rmol ForecasterTest ForecasterTestSuite.cpp)

# * Optimise Test Suite
module_test_add_suite (rmol OptimiseTest OptimiseTestSuite.cpp)

# * MRT for New Q_FF Test Suite
module_test_add_suite (rmol MRTForNewQFFTest MRTForNewQFFTestSuite.cpp)

# * Optimise for Q_FF Test Suite
module_test_add_suite (rmol OptimiseForQFFTest OptimiseForQFFTestSuite.cpp)

##
# Register all the test suites to be built and performed
module_test_build_all ()

