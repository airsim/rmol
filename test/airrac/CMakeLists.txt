#
# AirRAC Tests
#
module_set_name (airrac)


##
# Specify each test suite configuration

# * AirRAC Test Suite
module_test_add_suite (YieldTestSuite YieldTestSuite.cpp)


##
# Register all the test suites to be built and performed
module_test_build_all ()
