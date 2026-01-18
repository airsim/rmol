# That file is just a wrapper around the standard Fedora/RedHat FindBoost.cmake
# script. Indeed, that latter does not do version comparison. So, we just
# use here standard CMake mechanism to enforce the Boost required version.
#
# Moreover, on EPEL 5, Boost-1.41 is available in non-standard directories
# (since the standard Boost version is 1.33 for RedHat/CentOS/EPEL 5).
# cmake should therefore be invoked with the following options:
# -DBOOST_LIBRARYDIR=/usr/lib/boost141 \
# -DBOOST_INCLUDEDIR=/usr/include/boost141 \
# -DBoost_ADDITIONAL_VERSIONS="1.41 1.41.0"
#
set (Boost_HUMAN_VERSION
  ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION})
message (STATUS "Found Boost version: ${Boost_HUMAN_VERSION}")

# Check the version requirement only
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (BoostWrapper
  REQUIRED_VARS Boost_INCLUDE_DIRS Boost_LIBRARY_DIRS
  VERSION_VAR Boost_HUMAN_VERSION)

if (BOOSTWRAPPER_FOUND)
  mark_as_advanced (BOOSTWRAPPER_FOUND Boost_HUMAN_VERSION)
else (BOOSTWRAPPER_FOUND)
  message (FATAL_ERROR "Could not find the Boost libraries! Please install the development-libraries and headers (e.g., 'boost-devel' for Fedora/RedHat).")
endif (BOOSTWRAPPER_FOUND)

