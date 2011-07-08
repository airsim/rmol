#
# Tests for RMOL
#

# Subdirs
add_subdirectory (${PROJECT_NAME})

if (Boost_FOUND)

  add_custom_target (check
    DEPENDS checkUnconstrainerTest checkForecasterTest
    checkOptimiseTest checkBOMsForForecasterTest)

endif()
