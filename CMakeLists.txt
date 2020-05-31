#
cmake_minimum_required (VERSION 3.0)

##
# CMake macros for the project
include (config/project_config_embeddable.cmake)

##
# Project info
project (rmol)
set_project_names (rmol)
set_project_brief ("C++ library of Revenue Management and Optimisation classes and functions")
set_project_versions (1 00 6)

##
# Project options
# The parameters are:
#  * whether or not the documentation must be built and installed
#  * whether or not the tests must be compiled and run
#  * whether or not the code coverage must be performed
set_project_options (on on off)


#####################################
##            Packaging            ##
#####################################
#
packaging_init (${PROJECT_NAME})
packaging_set_summary (
"${PROJECT_NAME} is a C++ library of Revenue Management (RM)
and Optimisation classes and functions. Typically, that library
may be used by service providers (e.g., airlines offering flight seats,
hotels offering rooms, rental car companies offering rental days,
broadcasting company offering advertisement slots, theaters offering seats,
etc.) to help in optimising their revenues from seat capacities.
Most of the algorithms implemented are public and documented in the
following book:
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
get_external_libs (git "python 3.4" "boost 1.41" "mysql 5.0" "soci 3.0"
        readline curses "doxygen 1.4" "gcov 4.6.3" "lcov 1.9"
        "stdair 1.00.0" "airrac 1.00.0")


##############################################
##           Build, Install, Export         ##
##############################################
##
# Initialise the building process
init_build ()

##
# Sub-modules
add_modules (${PROJECT_NAME})

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
#
handle_html_doc ()

##
# Subdirs
add_subdirectory (man)


#####################################
##              Tests              ##
#####################################
##
# Initialise the unit test process
init_test ()

##
# Test suites
add_test_suite (${PROJECT_NAME})


#######################################
##             GCOV                 ##
#######################################
gcov_task()


#######################################
##          Overall Status           ##
#######################################
display_status ()


#######################################
##         CMake Cache Storage       ##
#######################################
store_in_cache ()
