# That file is just wrapper around the standard Fedora/RedHat FindBoost.cmake
# script. Indeed, that latter does not do version comparison. So, we just
# use here standard CMake mechanism to enforce the Boost required version.
# 
set (Boost_HUMAN_VERSION
  ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION})
message (STATUS "Found Boost version: ${Boost_HUMAN_VERSION}")

# Check the version requirement only
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (BoostWrapper
  REQUIRED_VARS Boost_INCLUDE_DIRS
  VERSION_VAR Boost_HUMAN_VERSION)

if (BOOSTWRAPPER_FOUND)
  mark_as_advanced (BOOSTWRAPPER_FOUND Boost_HUMAN_VERSION)
else (BOOSTWRAPPER_FOUND)
  message (FATAL_ERROR "Could not find the Boost libraries! Please install the development-libraries and headers (e.g., 'boost-devel' for Fedora/RedHat).")
endif (BOOSTWRAPPER_FOUND)

