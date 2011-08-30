#
cmake_minimum_required (VERSION 2.6)

##
# CMake macros for the project
include (config/project_config_embeddable.cmake)

##
# Project info
set_project_names (rmol)
set_project_brief ("C++ library of Revenue Management and Optimisation classes and functions")
set_project_versions (99 99 99)

##
# Project options
# The parameters are:
#  * whether or not the documentation must be built and installed
set_project_options (on)


#####################################
##            Packaging            ##
#####################################
#
packaging_init (${PROJECT_NAME})
packaging_set_summary ("${PROJECT_NAME} is a C++ library of Revenue Management and Optimisation classes and functions. Typically, that library may be used by service providers (e.g., airlines offering flight seats, hotels offering rooms, rental car companies offering rental days, broadcasting company offering advertisement slots, theaters offering seats, etc.) to help in optimising their revenues from seat capacities.
Most of the algorithms implemented are public and documented in the following
book:
The Theory and practice of Revenue Management, by Kalyan T. Talluri and
Garrett J. van Ryzin, Kluwer Academic Publishers, 2004, ISBN 1-4020-7701-7")
packaging_set_contact ("Denis Arnaud <denis_arnaud - at - users dot sourceforge dot net>")
packaging_set_vendor ("Denis Arnaud")

#
packaging_set_other_options (TBZ2 "TBZ2;TGZ")


########################################
##            Dependencies            ##
########################################
#
# Reverse the commenting below in order to rely on an actually external AirRAC,
# rather than on the embedded AirRAC
#get_external_libs (git "boost 1.41" mysql "soci 3.0" "stdair 0.35"
#				  "airrac 0.3" doxygen)
get_external_libs (git "boost 1.41" mysql "soci 3.0" "stdair 0.35" doxygen)


##############################################
##           Build, Install, Export         ##
##############################################
##
# Initialise the building process
init_build ()

##
# Sub-modules
# Reverse the commenting below in order to rely on an actually external AirRAC,
# rather than on the embedded AirRAC
#add_modules (${PROJECT_NAME})
add_modules (airrac ${PROJECT_NAME})

##
# For other projects to use RMOL, install a few helpers for standard
# build/packaging systems: CMake, GNU Autotools (M4), pkgconfig/pc, rmol-config
install_dev_helper_files ()

##
# Basic documentation (i.e., AUTHORS, NEWS, README, INSTALL)
install_basic_documentation ()


##########################################
##            Documentation             ##
##########################################
if (${INSTALL_DOC} STREQUAL "ON")
  add_subdirectory (doc)
endif (${INSTALL_DOC} STREQUAL "ON")

##
# Subdirs
add_subdirectory (man)


#####################################
##              Tests              ##
#####################################
##
# Test suites
add_test_suites (${PROJECT_NAME})


#######################################
##          Overall Status           ##
#######################################
display_status ()


#######################################
##         CMake Cache Storage       ##
#######################################
store_in_cache ()
