#
cmake_minimum_required (VERSION 2.6)

# See also:
# http://snikt.net/index.php/2010/04/01/howto-use-cmake-with-cc-projects

##
# CMake macros for the project
include (config/project_config_embeddable.cmake)

###
##
# Project info
set_project_names (rmol)
set_project_versions (99 99 99)

##
# Project options
# The parameters are:
#  * whether or not the documentation must be built and installed
set_project_options (off)


#####################################
##            Packaging            ##
#####################################
#
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set (CPACK_PACKAGE_DESCRIPTION "C++ Standard Airline IT Library")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} aims at providing a clean API, and the corresponding C++ implementation, for the basis of Airline IT Business Object Model (BOM), that is, to be used by several other open source projects, such as RMOL, Air-Sched, Travel-CCM, OpenTREP, etc.")

set (CPACK_PACKAGE_CONTACT "Denis Arnaud <denis_arnaud@users.sourceforge.net>")
set (CPACK_PACKAGE_VENDOR "Denis Arnaud")

#
define_package_options ()


########################################
##            Dependencies            ##
########################################
#
# CMake scripts, to find some dependencies (e.g., Boost, MySQL, SOCI)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/config/)

#
get_external_libs (git "boost 1.41" mysql "soci 3.0" "stdair 0.35" doxygen)


##############################################
##           Build, Install, Export         ##
##############################################
##
# Initialise the building process
init_build ()

##
# Sub-modules
add_modules (airrac ${PROJECT_NAME})

##
#
install_dev_helper_files ()

##
# Documentation
install (FILES ${OTHERDOC_FILES} DESTINATION ${OTHERDOC_PATH})


##########################################
##            Documentation             ##
##########################################
if (${INSTALL_DOC} STREQUAL "ON")
  add_subdirectory (doc)
endif (${INSTALL_DOC} STREQUAL "ON")


#####################################
##              Tests              ##
#####################################
add_subdirectory (test)


#######################################
##          Overall Status           ##
#######################################
display_status ()


#######################################
##           Cache Storage           ##
#######################################
store_in_cache ()