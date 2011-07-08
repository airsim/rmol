#
cmake_minimum_required (VERSION 2.6)

# See also:
# http://snikt.net/index.php/2010/04/01/howto-use-cmake-with-cc-projects

###
##
# Project info
project (rmol)
set (PACKAGE_PRETTY_NAME "RMOL" CACHE INTERNAL "Description")
string (TOLOWER "${PROJECT_NAME}" PACKAGE_TMP)
set (PACKAGE "${PACKAGE_TMP}" CACHE INTERNAL "Description")
string (TOUPPER "${PROJECT_NAME}" PACKAGE_NAME_TMP)
set (PACKAGE_NAME "${PACKAGE_NAME_TMP}" CACHE INTERNAL "Description")

##
# Version
set (rmol_VERSION_MAJOR 99)
set (rmol_VERSION_MINOR 99)
set (rmol_VERSION_PATCH 99)
set (rmol_VERSION "${rmol_VERSION_MAJOR}.${rmol_VERSION_MINOR}.${rmol_VERSION_PATCH}")
set (PACKAGE_VERSION "${rmol_VERSION}")
# Note that the soname could be different from the version. The soname
# should change only the ABI compatibility is no longer guaranteed.
set (GENERIC_LIB_VERSION "${rmol_VERSION}")
set (GENERIC_LIB_SOVERSION "${rmol_VERSION_MAJOR}.${rmol_VERSION_MINOR}")
set (LIBDIR "lib${LIB_SUFFIX}")

##
# Project options
option (BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON)
option (INSTALL_DOC "Set to OFF to skip build/install Documentation" ON)
# Set default cmake build type to Debug (None Debug Release RelWithDebInfo
# MinSizeRel)
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE "Debug")
endif()

# Set default install prefix to project root directory
if (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
  set (CMAKE_INSTALL_PREFIX "/usr")
endif()

# Offer the user the choice of overriding the installation directories
set (INSTALL_LIB_DIR ${LIBDIR} CACHE
  PATH "Installation directory for libraries")
set (INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set (INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set (INSTALL_DATA_DIR share CACHE PATH
  "Installation directory for data files")

# Make relative paths absolute (needed later on)
foreach (p LIB BIN INCLUDE DATA)
  set (var INSTALL_${p}_DIR)
  if (NOT IS_ABSOLUTE "${${var}}")
    set (${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

##
# Library target. It is specified here because both the rmol/config (for
# the library target) and rmol/batches (for the binary target)
# sub-directories need it.
set (RMOL_LIB_TARGET ${PROJECT_NAME}lib)
# Library names
set (RMOL_LIB_NAME ${PROJECT_NAME})

##
# SCM (Git)
find_package (Git)
if (Git_FOUND)
  Git_WC_INFO (${CMAKE_CURRENT_SOURCE_DIR} ER)
  set (GIT_REVISION ${ER_WC_REVISION})
endif (Git_FOUND)

##
# "Other" Documentation
set (OTHERDOC_FILES AUTHORS NEWS README INSTALL)
set (OTHERDOC_PATH "share/doc/${PACKAGE}-${PACKAGE_VERSION}")
install (FILES ${OTHERDOC_FILES} DESTINATION ${OTHERDOC_PATH})

##
# Packaging
include (InstallRequiredSystemLibraries)
set (CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set (CPACK_PACKAGE_DESCRIPTION "C++ Standard Airline IT Library")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME} aims at providing a clean API, and the corresponding C++ implementation, for the basis of Airline IT Business Object Model (BOM), that is, to be used by several other open source projects, such as RMOL, Air-Sched, Travel-CCM, OpenTREP, etc.")

set (CPACK_PACKAGE_CONTACT "Denis Arnaud <denis_arnaud@users.sourceforge.net>")
set (CPACK_PACKAGE_VENDOR "Denis Arnaud")
set (CPACK_PACKAGE_VERSION_MAJOR ${rmol_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${rmol_VERSION_MINOR})
#set (CPACK_PACKAGE_VERSION_PATCH ${rmol_VERSION_PATCH})
set (CPACK_PACKAGE_VERSION_PATCH ${GIT_REVISION})
set (CPACK_PACKAGE_VERSION ${rmol_VERSION})
set (CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README)
set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
set (CPACK_GENERATOR "TBZ2")
#set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.6), libgcc1 (>= 1:4.1)")

# Available types of package: DEB, RPM, TZ, TGZ, TBZ2
set (CPACK_SOURCE_GENERATOR "TBZ2")
set (CPACK_SOURCE_PACKAGE_FILE_NAME 
  "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}"
  CACHE INTERNAL "tarball basename")
set (AUTOTOOLS_IGNRD "/tmp/;/tmp2/;/autom4te\\\\.cache/;autogen\\\\.sh$")
set (PACK_IGNRD "${CPACK_PACKAGE_NAME}\\\\.spec;/build/;\\\\.gz$;\\\\.bz2$")
set (EDIT_IGNRD "\\\\.swp$;\\\\.#;/#;~$")
set (SCM_IGNRD 
  "/CVS/;/\\\\.svn/;/\\\\.bzr/;/\\\\.hg/;/\\\\.git/;\\\\.gitignore$")
set (CPACK_SOURCE_IGNORE_FILES
  "${AUTOTOOLS_IGNRD};${SCM_IGNRD};${EDIT_IGNRD};${PACK_IGNRD}"
  CACHE STRING "CPACK will ignore these files")
#set (CPACK_SOURCE_IGNORE_DIRECTORY ${CPACK_SOURCE_IGNORE_FILES} .git)

##
# Dependencies
#
# CMake scripts, to find some dependencies (e.g., Boost, MySQL, SOCI)
set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/config/)

# ~~~~~~~~~~ BOOST ~~~~~~~~~~
#
# Note: ${Boost_DATE_TIME_LIBRARY} and ${Boost_PROGRAM_OPTIONS_LIBRARY}
# are already set by ${SOCIMYSQL_LIBRARIES} and/or ${SOCI_LIBRARIES}.
#
find_package (Boost 1.44 REQUIRED COMPONENTS program_options date_time 
  iostreams serialization filesystem unit_test_framework)
if (Boost_FOUND)
  include_directories (${Boost_INCLUDE_DIRS})
  set (BOOST_LIBS_FOR_LIB 
	${Boost_IOSTREAMS_LIBRARY} ${Boost_SERIALIZATION_LIBRARY}
	${Boost_FILESYSTEM_LIBRARY})
##
# See https://bugzilla.redhat.com/show_bug.cgi?id=718504
# For now, SOCI is linked with the single-threaded version of boost-date-time
# (and of boost-program-options). So, we do not add the multi-threaded versions
# of those libraries to the dependencies, otherwise we would end up with
# some strange behaviour of the generated binaries and libraries.
# For instance, when a program exits and the static variables are garbaged
# collected, two versions of the same library means two garbage collections
# for the same objects...
# When SOCI will be delivered with the multi-threaded Boost as dependency,
# just uncomment the following line:
# set (BOOST_LIBS_FOR_LIB ${BOOST_LIBS_FOR_LIB} ${Boost_DATE_TIME_LIBRARY})
  set (BOOST_LIBS_FOR_BIN ${Boost_PROGRAM_OPTIONS_LIBRARY})
  set (BOOST_LIBS_FOR_TEST ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
endif (Boost_FOUND)

# ~~~~~~~~~~ MySQL ~~~~~~~~~
find_package (MySQL)
if (MYSQL_FOUND)
  include_directories (${MYSQL_INCLUDE_DIR})
endif (MYSQL_FOUND)

# ~~~~~~~~~~ SOCI ~~~~~~~~~~
find_package (SOCI)
if (SOCI_FOUND)
  include_directories (${SOCI_INCLUDE_DIR})
endif (SOCI_FOUND)
find_package (SOCIMySQL)
if (SOCIMYSQL_FOUND)
  include_directories (${SOCIMYSQL_INCLUDE_DIR})
endif (SOCIMYSQL_FOUND)

# ~~~~~~~~~~ Doxygen ~~~~~~~~~
find_package (Doxygen REQUIRED)

# ~~~~~~~~~~ StdAir ~~~~~~~~~
find_package (StdAir REQUIRED HINTS ${WITH_STDAIR_PREFIX})
if (StdAir_FOUND)
  include_directories (${STDAIR_INCLUDE_DIRS})
  message (STATUS "StdAir binary directory: ${STDAIR_BINARY_DIRS}")
  message (STATUS "StdAir library directory: ${STDAIR_LIBRARY_DIRS}")
  message (STATUS "StdAir header directory: ${STDAIR_INCLUDE_DIRS}")
  message (STATUS "StdAir (CSV) sample directory: ${STDAIR_SAMPLE_DIR}")
  message (STATUS "StdAir libraries: ${STDAIR_LIBRARIES}")
  message (STATUS "StdAir binaries: ${STDAIR_EXECUTABLE}")
else (StdAir_FOUND)
  set (ERROR_MSG "The StdAir library cannot be found. If it is installed in a")
  set (ERROR_MSG "${ERROR_MSG} in a non standard directory, just invoke")
  set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_STDAIR_PREFIX=")
  set (ERROR_MSG "${ERROR_MSG}<StdAir install path> variable.")
  message (FATAL_ERROR "${ERROR_MSG}")
endif (StdAir_FOUND)

##
# Set all the directory pathes for the project (e.g., prefix, libdir, bindir)
include (config/project_config_non_stdair.cmake)

##
# For the other developers to use that project
include (config/devhelpers.cmake)

# Compilation
# Note: the debug flag (-g) is set (or not) by giving the
# corresponding option when calling cmake:
# cmake -DCMAKE_BUILD_TYPE:STRING={Debug,Release,MinSizeRel,RelWithDebInfo}
#set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
set (CMAKE_CXX_FLAGS "-Wall -Werror")
include_directories (BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}) 

##
# Subdirs
add_subdirectory (${PROJECT_NAME})
add_subdirectory (${PROJECT_NAME}/batches)
add_subdirectory (test)

# Add all targets to the build-tree export set
export (TARGETS ${PROJECT_NAME}
  ${RMOL_LIB_TARGET} ${RMOL_UICL_LIB_TARGET}
  FILE "${PROJECT_BINARY_DIR}/RmolLibraryDepends.cmake")

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export (PACKAGE rmol)

# Install the export set for use with the install-tree
install (EXPORT RmolLibraryDepends DESTINATION
  "${INSTALL_DATA_DIR}/${PACKAGE}/CMake" COMPONENT dev)

# Create a RmolConfig.cmake file for the use from the install tree
# and install it
set (RMOL_INCLUDE_DIRS "${INSTALL_INCLUDE_DIR}")
set (RMOL_BIN_DIR "${INSTALL_BIN_DIR}")
set (RMOL_LIB_DIR "${INSTALL_LIB_DIR}")
set (RMOL_CMAKE_DIR "${INSTALL_DATA_DIR}/${PACKAGE}/CMake")
configure_file (RmolConfig.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/RmolConfig.cmake" @ONLY)
configure_file (RmolConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/RmolConfigVersion.cmake" @ONLY)
install (FILES
  "${PROJECT_BINARY_DIR}/InstallFiles/RmolConfig.cmake"
  "${PROJECT_BINARY_DIR}/InstallFiles/RmolConfigVersion.cmake"
  DESTINATION "${RMOL_CMAKE_DIR}" COMPONENT dev)


##
# Packaging
include (CPack)
# Add a 'dist' target, similar to what is given by GNU Autotools
add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)


# Display status message for important variables
message (STATUS)
message (STATUS "=============================================================")
message (STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}" )
message (STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}" )
message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}" )
message (STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}" )
message (STATUS)
message (STATUS "---")
message (STATUS "INSTALL_LIB_DIR = ${INSTALL_LIB_DIR}")
message (STATUS "INSTALL_BIN_DIR = ${INSTALL_BIN_DIR}")
message (STATUS "INSTALL_INCLUDE_DIR = ${INSTALL_INCLUDE_DIR}")
message (STATUS "INSTALL_DATA_DIR = ${INSTALL_DATA_DIR}")
message (STATUS "INSTALL_DOC = ${INSTALL_DOC}" )
message (STATUS)
message (STATUS "---")
message (STATUS "CPACK_PACKAGE_CONTACT = ${CPACK_PACKAGE_CONTACT}")
message (STATUS "CPACK_PACKAGE_VENDOR = ${CPACK_PACKAGE_VENDOR}")
message (STATUS "CPACK_PACKAGE_VERSION = ${CPACK_PACKAGE_VERSION}")
message (STATUS "CPACK_PACKAGE_DESCRIPTION_FILE = ${CPACK_PACKAGE_DESCRIPTION_FILE}")
message (STATUS "CPACK_RESOURCE_FILE_LICENSE = ${CPACK_RESOURCE_FILE_LICENSE}")
message (STATUS "CPACK_GENERATOR = ${CPACK_GENERATOR}")
message (STATUS "CPACK_DEBIAN_PACKAGE_DEPENDS = ${CPACK_DEBIAN_PACKAGE_DEPENDS}")
message (STATUS "CPACK_SOURCE_GENERATOR = ${CPACK_SOURCE_GENERATOR}")
message (STATUS "CPACK_SOURCE_PACKAGE_FILE_NAME = ${CPACK_SOURCE_PACKAGE_FILE_NAME}")
message (STATUS)
message (STATUS "External libraries:")
message (STATUS "-------------------")
message (STATUS "* Boost:")
message (STATUS "  - Boost_INCLUDE_DIRS ........ : ${Boost_INCLUDE_DIRS}")
message (STATUS "  - BOOST_LIBS_FOR_LIB ........ : ${BOOST_LIBS_FOR_LIB}")
message (STATUS "  - BOOST_LIBS_FOR_BIN ........ : ${BOOST_LIBS_FOR_BIN}")
message (STATUS "  - BOOST_LIBS_FOR_TEST ....... : ${BOOST_LIBS_FOR_TEST}")
message (STATUS)
message (STATUS "* MySQL:")
message (STATUS "  - MYSQL_INCLUDE_DIR ......... : ${MYSQL_INCLUDE_DIR}")
message (STATUS "  - MYSQL_LIBRARIES ........... : ${MYSQL_LIBRARIES}")
message (STATUS)
message (STATUS "* SOCI:")
message (STATUS "  - SOCI_INCLUDE_DIR .......... : ${SOCI_INCLUDE_DIR}")
message (STATUS "  - SOCIMYSQL_INCLUDE_DIR ..... : ${SOCIMYSQL_INCLUDE_DIR}")
message (STATUS "  - SOCI_LIBRARIES ............ : ${SOCI_LIBRARIES}")
message (STATUS "  - SOCIMYSQL_LIBRARIES ....... : ${SOCIMYSQL_LIBRARIES}")
message (STATUS)
message (STATUS "* StdAir:")
message (STATUS "  - STDAIR_BINARY_DIRS ........ : ${STDAIR_BINARY_DIRS}")
message (STATUS "  - STDAIR_EXECUTABLE ......... : ${STDAIR_EXECUTABLE}")
message (STATUS "  - STDAIR_LIBRARY_DIRS ....... : ${STDAIR_LIBRARY_DIRS}")
message (STATUS "  - STDAIR_LIBRARIES .......... : ${STDAIR_LIBRARIES}")
message (STATUS "  - STDAIR_INCLUDE_DIRS ....... : ${STDAIR_INCLUDE_DIRS}")
message (STATUS "  - STDAIR_SAMPLE_DIR ......... : ${STDAIR_SAMPLE_DIR}")
message (STATUS)
message (STATUS "Change a value with: cmake -D<Variable>=<Value>" )
message (STATUS "=============================================================")
message (STATUS)

# Force some variables that could be defined in the command line to be
# written to cache
set (BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS}" CACHE BOOL
  "Set to OFF to build static libraries" FORCE)
set (CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE PATH
  "Where to install ${PROJECT_NAME}" FORCE)
set (CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
  "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" CACHE PATH
  "Path to custom CMake Modules" FORCE)
set (INSTALL_DOC "${INSTALL_DOC}" CACHE BOOL
  "Set to OFF to skip build/install Documentation" FORCE)
