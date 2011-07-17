#
# Tests for RMOL
#

# Subdirs
add_subdirectory (${PROJECT_NAME})

if (Boost_FOUND)

  # Each individual test suite is specified within the dedicated sub-directory
  add_custom_target (check DEPENDS check_${PROJECT_NAME})

endif()
