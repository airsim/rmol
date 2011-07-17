#######################################################################
## CMake Macros for an embeddable project
##
## Author: Denis Arnaud
## Date: July 2011
#######################################################################


###################################################################
##                     Project Configuration                     ##
###################################################################
##
# Set the project names
macro (set_project_names _project_name_param)
  # Set the pretty name
  string (TOUPPER ${_project_name_param} _pretty_name_tmp)
  if (${ARGC} GREATER 1)
	set (_pretty_name_tmp ${ARGV1})
  endif (${ARGC} GREATER 1)
  set (PACKAGE_PRETTY_NAME "${_pretty_name_tmp}" CACHE INTERNAL "Description")

  # Set the lowercase project name
  string (TOLOWER "${_project_name_param}" _package_tmp)
  set (PACKAGE "${_package_tmp}" CACHE INTERNAL "Description")

  # Set the uppercase project name
  string (TOUPPER "${_project_name_param}" _package_name_tmp)
  set (PACKAGE_NAME "${_package_name_tmp}" CACHE INTERNAL "Description")

  # Set the project name
  project (${PACKAGE})
endmacro (set_project_names)

##
# Set the project versions
macro (set_project_versions _major _minor _patch)
  set (_full_version ${_major}.${_minor}.${_patch})
  #
  set (${PROJECT_NAME}_VERSION_MAJOR ${_major})
  set (${PROJECT_NAME}_VERSION_MINOR ${_minor})
  set (${PROJECT_NAME}_VERSION_PATCH ${_patch})
  set (${PROJECT_NAME}_VERSION ${_full_version})
  #
  set (PACKAGE_VERSION ${_full_version})
  # Note that the soname can be different from the version. The soname
  # should change only when the ABI compatibility is no longer guaranteed.
  set (GENERIC_LIB_VERSION ${_full_version})
  set (GENERIC_LIB_SOVERSION ${_major}.${_minor})
endmacro (set_project_versions)

##
# Set a few options:
#  * BUILD_SHARED_LIBS   - Whether or not to build shared libraries
#  * CMAKE_BUILD_TYPE    - Debug or release
#  * CMAKE_INSTALL_PREFIX
#  * INSTALL_DOC         - Whether or not to build and install the documentation
#  * INSTALL_LIB_DIR     - Installation directory for the libraries
#  * INSTALL_BIN_DIR     - Installation directory for the binaries
#  * INSTALL_INCLUDE_DIR - Installation directory for the header files
#  * INSTALL_DATA_DIR    - Installation directory for the data files
#
macro (set_project_options _build_doc)
  # Shared libraries
  option (BUILD_SHARED_LIBS "Set to OFF to build static libraries" ON)

  # Set default cmake build type to Debug (None Debug Release RelWithDebInfo
  # MinSizeRel)
  if (NOT CMAKE_BUILD_TYPE)
	set (CMAKE_BUILD_TYPE "Debug")
  endif()

  # Set default install prefix to project root directory
  if (CMAKE_INSTALL_PREFIX STREQUAL "/usr/local")
	set (CMAKE_INSTALL_PREFIX "/usr")
  endif()

  # Documentation
  option (INSTALL_DOC "Set to OFF to skip build/install Documentation" 
	${_build_doc})

  # Set the library installation directory (either 32 or 64 bits)
  set (LIBDIR "lib${LIB_SUFFIX}")

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
  # "Other" Documentation
  set (OTHERDOC_FILES AUTHORS NEWS README INSTALL)
  set (OTHERDOC_PATH "share/doc/${PACKAGE}-${PACKAGE_VERSION}")

endmacro (set_project_options)

#
macro (store_in_cache)
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
endmacro (store_in_cache)


#####################################
##            Packaging            ##
#####################################
#
macro (define_package_options)
  set (CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
  set (CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
  #set (CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH})
  set (CPACK_PACKAGE_VERSION_PATCH ${GIT_REVISION})
  set (CPACK_PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})
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

  include (CPack)
  # Add a 'dist' target, similar to what is given by GNU Autotools
  add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
endmacro (define_package_options)


##############################################
##           Build, Install, Export         ##
##############################################
macro (init_build)
  ##
  # Compilation
  # Note: the debug flag (-g) is set (or not) by giving the
  # corresponding option when calling cmake:
  # cmake -DCMAKE_BUILD_TYPE:STRING={Debug,Release,MinSizeRel,RelWithDebInfo}
  #set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
  set (CMAKE_CXX_FLAGS "-Wall -Werror")
  include_directories (BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
  
  ##
  # Set all the directory installation paths for the project (e.g., prefix,
  # libdir, bindir).
  # Note that those paths need to be set before the sub-directories are browsed
  # for the building process (see below), because that latter needs those paths
  # to be correctly set.
  include (config/project_install_dirs.cmake)
endmacro (init_build)

##
# For each sub-module:
#  * The libraries and binaries are built (with the regular
#    'make' command) and installed (with the 'make install' command).
#    The header files are installed as well.
#  * The corresponding targets (libraries and binaries) are exported within
#    a CMake import helper file, namely '${PROJECT_NAME}-library-depends.cmake'.
#    That CMake import helper file is installed in the installation directory,
#    within the <install_dir>/share/${PROJECT_NAME}/CMake sub-directory.
#    That CMake import helper file is used by the ${PROJECT_NAME}-config.cmake
#    file, to be installed in the same sub-directory. The
#    ${PROJECT_NAME}-config.cmake file is specified a little bit below.
macro (add_modules)
  set (_embedded_components ${ARGV})
  set (LIB_DEPENDENCY_EXPORT ${PROJECT_NAME}-library-depends)
  set (LIB_DEPENDENCY_EXPORT_PATH "${INSTALL_DATA_DIR}/${PROJECT_NAME}/CMake")
  #
  foreach (_embedded_comp ${_embedded_components})
	add_subdirectory (${_embedded_comp})
  endforeach (_embedded_comp)
endmacro (add_modules)


###################################################################
##                         Dependencies                          ##
###################################################################
# ~~~~~~~~~~ Git ~~~~~~~~~~
macro (get_git)
  message (STATUS "Requires Git without specifying any version")

  find_package (Git)
  if (Git_FOUND)
	Git_WC_INFO (${CMAKE_CURRENT_SOURCE_DIR} ER)
	set (GIT_REVISION ${ER_WC_REVISION})
	message (STATUS "Found Git version: ${GIT_REVISION}")
  endif (Git_FOUND)
endmacro (get_git)

# ~~~~~~~~~~ BOOST ~~~~~~~~~~
macro (get_boost)
  set (_required_version 0)
  if (${ARGC} GREATER 0)
	set (_required_version ${ARGV0})
	message (STATUS "Requires Boost-${_required_version}")
  else (${ARGC} GREATER 0)
	message (STATUS "Requires Boost without specifying any version")
  endif (${ARGC} GREATER 0)

  #
  # Note: ${Boost_DATE_TIME_LIBRARY} and ${Boost_PROGRAM_OPTIONS_LIBRARY}
  # are already set by ${SOCIMYSQL_LIBRARIES} and/or ${SOCI_LIBRARIES}.
  #
  set (Boost_USE_STATIC_LIBS OFF)
  set (Boost_USE_MULTITHREADED ON)
  set (Boost_USE_STATIC_RUNTIME OFF)
  find_package (Boost ${_required_version} REQUIRED
	COMPONENTS program_options date_time iostreams serialization filesystem
	unit_test_framework)

  if (Boost_FOUND)
	set (Boost_HUMAN_VERSION
	  ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION})
	include_directories (${Boost_INCLUDE_DIRS})
	set (BOOST_LIBS_FOR_LIB 
	  ${Boost_IOSTREAMS_LIBRARY} ${Boost_SERIALIZATION_LIBRARY}
	  ${Boost_FILESYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY})
	set (BOOST_LIBS_FOR_BIN ${Boost_PROGRAM_OPTIONS_LIBRARY})
	set (BOOST_LIBS_FOR_TEST ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	message (STATUS "Found Boost version: ${Boost_HUMAN_VERSION}")
  endif (Boost_FOUND)
endmacro (get_boost)

# ~~~~~~~~~~ MySQL ~~~~~~~~~
macro (get_mysql)
  set (_required_version 0)
  if (${ARGC} GREATER 0)
	set (_required_version ${ARGV0})
	message (STATUS "Requires MySQL-${_required_version}")
  else (${ARGC} GREATER 0)
	message (STATUS "Requires MySQL without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (MySQL)
  if (MYSQL_FOUND)
	include_directories (${MYSQL_INCLUDE_DIR})
  endif (MYSQL_FOUND)
endmacro (get_mysql)

# ~~~~~~~~~~ SOCI ~~~~~~~~~~
macro (get_soci)
  set (_required_version 0)
  if (${ARGC} GREATER 0)
	set (_required_version ${ARGV0})
	message (STATUS "Requires SOCI-${_required_version}")
  else (${ARGC} GREATER 0)
	message (STATUS "Requires SOCI without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (SOCI)
  if (SOCI_FOUND)
	include_directories (${SOCI_INCLUDE_DIR})
	message (STATUS "Found SOCI version: ${SOCI_VERSION}")
  endif (SOCI_FOUND)
  find_package (SOCIMySQL)
  if (SOCIMYSQL_FOUND)
	include_directories (${SOCIMYSQL_INCLUDE_DIR})
  endif (SOCIMYSQL_FOUND)
endmacro (get_soci)

# ~~~~~~~~~~ Doxygen ~~~~~~~~~
macro (get_doxygen)
  set (_required_version 0)
  if (${ARGC} GREATER 0)
	set (_required_version ${ARGV0})
	message (STATUS "Requires Doxygen-${_required_version}")
  else (${ARGC} GREATER 0)
	message (STATUS "Requires Doxygen without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (Doxygen REQUIRED)
endmacro (get_doxygen)

# ~~~~~~~~~~ StdAir ~~~~~~~~~
macro (get_stdair)
  set (_required_version 0)
  if (${ARGC} GREATER 0)
	set (_required_version ${ARGV0})
	message (STATUS "Requires StdAir-${_required_version}")
  else (${ARGC} GREATER 0)
	message (STATUS "Requires StdAir without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (StdAir REQUIRED HINTS ${WITH_STDAIR_PREFIX})
  if (StdAir_FOUND)
	include_directories (${STDAIR_INCLUDE_DIRS})
	message (STATUS "Found StdAir version: ${STDAIR_VERSION}")
  else (StdAir_FOUND)
	set (ERROR_MSG "The StdAir library cannot be found. If it is installed in")
	set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
	set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_STDAIR_PREFIX=")
	set (ERROR_MSG "${ERROR_MSG}<StdAir install path> variable.")
	message (FATAL_ERROR "${ERROR_MSG}")
  endif (StdAir_FOUND)
endmacro (get_stdair)

# ~~~~~~~~ Wrapper ~~~~~~~~
macro (get_external_libs)
  foreach (_arg ${ARGV})
	string (TOLOWER ${_arg} _arg_lower_full)

	# Extract the name of the external dependency
	string (REGEX MATCH "^[a-z]+" _arg_lower ${_arg_lower_full})

	# Extract the required version of the external dependency
	string (REGEX MATCH "[0-9._-]+$" _arg_version ${_arg_lower_full})

	if (${_arg_lower} STREQUAL "git")
	  get_git (${_arg_version})
	endif (${_arg_lower} STREQUAL "git")

	if (${_arg_lower} STREQUAL "boost")
	  get_boost (${_arg_version})
	endif (${_arg_lower} STREQUAL "boost")

	if (${_arg_lower} STREQUAL "mysql")
	  get_mysql (${_arg_version})
	endif (${_arg_lower} STREQUAL "mysql")

	if (${_arg_lower} STREQUAL "soci")
	  get_soci (${_arg_version})
	endif (${_arg_lower} STREQUAL "soci")

	if (${_arg_lower} STREQUAL "stdair")
	  get_stdair (${_arg_version})
	endif (${_arg_lower} STREQUAL "stdair")

	if (${_arg_lower} STREQUAL "doxygen")
	  get_doxygen (${_arg_version})
	endif (${_arg_lower} STREQUAL "doxygen")

  endforeach (_arg)
endmacro (get_external_libs)


###################################################################
##                    Development Helpers                        ##
###################################################################
macro (install_dev_helper_files)
  ##
  ## First, build and install CMake development helper files
  ##
  # Create a ${PROJECT_NAME}-config.cmake file for the use from 
  # the install tree and install it
  install (EXPORT ${LIB_DEPENDENCY_EXPORT}
	DESTINATION ${LIB_DEPENDENCY_EXPORT_PATH})
  set (${PACKAGE_NAME}_INCLUDE_DIRS "${INSTALL_INCLUDE_DIR}")
  set (${PACKAGE_NAME}_BIN_DIR "${INSTALL_BIN_DIR}")
  set (${PACKAGE_NAME}_LIB_DIR "${INSTALL_LIB_DIR}")
  set (${PACKAGE_NAME}_CMAKE_DIR "${LIB_DEPENDENCY_EXPORT_PATH}")
  configure_file (${PROJECT_NAME}-config.cmake.in
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" @ONLY)
  configure_file (${PROJECT_NAME}-config-version.cmake.in
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake" @ONLY)
  install (FILES
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	DESTINATION "${${PACKAGE_NAME}_CMAKE_DIR}" COMPONENT devel)

  ##
  ## Then, build and install development helper files for other build systems
  ##
  # For the other developers to use that project, a few helper scripts are
  # installed:
  #  * ${PROJECT_NAME}-config (to be used by any other build system)
  #  * GNU Autotools M4 macro
  #  * packaging configuration script (pkgconfig/pc)
  include (config/devhelpers.cmake)

  # Install the development helpers
  install (PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/${CFG_SCRIPT} 
	DESTINATION ${CFG_SCRIPT_PATH})
  install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${PKGCFG_SCRIPT}
	DESTINATION ${PKGCFG_SCRIPT_PATH})
  install (FILES ${CMAKE_CURRENT_BINARY_DIR}/${M4_MACROFILE}
	DESTINATION ${M4_MACROFILE_PATH})

endmacro (install_dev_helper_files)


#######################################
##          Overall Status           ##
#######################################
# Boost
macro (display_boost)
  if (Boost_FOUND)
	message (STATUS "* Boost:")
	message (STATUS "  - Boost_VERSION ............. : ${Boost_VERSION}")
	message (STATUS "  - Boost_LIB_VERSION ......... : ${Boost_LIB_VERSION}")
	message (STATUS "  - Boost_HUMAN_VERSION ....... : ${Boost_HUMAN_VERSION}")
	message (STATUS "  - Boost_INCLUDE_DIRS ........ : ${Boost_INCLUDE_DIRS}")
	message (STATUS "  - BOOST_LIBS_FOR_LIB ........ : ${BOOST_LIBS_FOR_LIB}")
	message (STATUS "  - BOOST_LIBS_FOR_BIN ........ : ${BOOST_LIBS_FOR_BIN}")
	message (STATUS "  - BOOST_LIBS_FOR_TEST ....... : ${BOOST_LIBS_FOR_TEST}")
  endif (Boost_FOUND)
endmacro (display_boost)

# MySQL
macro (display_mysql)
  if (MYSQL_FOUND)
	message (STATUS)
	message (STATUS "* MySQL:")
	message (STATUS "  - MYSQL_VERSION ............. : ${MYSQL_VERSION}")
	message (STATUS "  - MYSQL_INCLUDE_DIR ......... : ${MYSQL_INCLUDE_DIR}")
	message (STATUS "  - MYSQL_LIBRARIES ........... : ${MYSQL_LIBRARIES}")
  endif (MYSQL_FOUND)
endmacro (display_mysql)

# SOCI
macro (display_soci)
  if (SOCI_FOUND)
	message (STATUS)
	message (STATUS "* SOCI:")
	message (STATUS "  - SOCI_VERSION .............. : ${SOCI_VERSION}")
	message (STATUS "  - SOCI_INCLUDE_DIR .......... : ${SOCI_INCLUDE_DIR}")
	message (STATUS "  - SOCIMYSQL_INCLUDE_DIR ..... : ${SOCIMYSQL_INCLUDE_DIR}")
	message (STATUS "  - SOCI_LIBRARIES ............ : ${SOCI_LIBRARIES}")
	message (STATUS "  - SOCIMYSQL_LIBRARIES ....... : ${SOCIMYSQL_LIBRARIES}")
  endif (SOCI_FOUND)
endmacro (display_soci)

# StdAir
macro (display_stdair)
  if (StdAir_FOUND)
	message (STATUS)
	message (STATUS "* StdAir:")
	message (STATUS "  - STDAIR_VERSION ............ : ${STDAIR_VERSION}")
	message (STATUS "  - STDAIR_BINARY_DIRS ........ : ${STDAIR_BINARY_DIRS}")
	message (STATUS "  - STDAIR_EXECUTABLES ........ : ${STDAIR_EXECUTABLES}")
	message (STATUS "  - STDAIR_LIBRARY_DIRS ....... : ${STDAIR_LIBRARY_DIRS}")
	message (STATUS "  - STDAIR_LIBRARIES .......... : ${STDAIR_LIBRARIES}")
	message (STATUS "  - STDAIR_INCLUDE_DIRS ....... : ${STDAIR_INCLUDE_DIRS}")
	message (STATUS "  - STDAIR_SAMPLE_DIR ......... : ${STDAIR_SAMPLE_DIR}")
  endif (StdAir_FOUND)
endmacro (display_stdair)

##
macro (display_status)
  message (STATUS)
  message (STATUS "=============================================================")
  message (STATUS "---------------------------")
  message (STATUS "--- Project Information ---")
  message (STATUS "---------------------------")
  message (STATUS "PROJECT_NAME = ${PROJECT_NAME}")
  message (STATUS "PACKAGE_PRETTY_NAME = ${PACKAGE_PRETTY_NAME}")
  message (STATUS "PACKAGE = ${PACKAGE}")
  message (STATUS "PACKAGE_NAME = ${PACKAGE_NAME}")
  message (STATUS "PACKAGE_VERSION = ${PACKAGE_VERSION}")
  message (STATUS "GENERIC_LIB_VERSION = ${GENERIC_LIB_VERSION}")
  message (STATUS "GENERIC_LIB_SOVERSION = ${GENERIC_LIB_SOVERSION}")
  message (STATUS)
  message (STATUS "---------------------------")
  message (STATUS "--- Build Configuration ---")
  message (STATUS "---------------------------")
  message (STATUS "Embedded components = ${EMBEDDED_COMPONENTS}")
  message (STATUS "BUILD_SHARED_LIBS = ${BUILD_SHARED_LIBS}")
  message (STATUS "CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
  message (STATUS "CMAKE_MODULE_PATH = ${CMAKE_MODULE_PATH}")
  message (STATUS "CMAKE_INSTALL_PREFIX = ${CMAKE_INSTALL_PREFIX}")
  message (STATUS)
  message (STATUS "----------------------------------")
  message (STATUS "--- Installation Configuration ---")
  message (STATUS "----------------------------------")
  message (STATUS "INSTALL_LIB_DIR = ${INSTALL_LIB_DIR}")
  message (STATUS "INSTALL_BIN_DIR = ${INSTALL_BIN_DIR}")
  message (STATUS "INSTALL_INCLUDE_DIR = ${INSTALL_INCLUDE_DIR}")
  message (STATUS "INSTALL_DATA_DIR = ${INSTALL_DATA_DIR}")
  message (STATUS "INSTALL_DOC = ${INSTALL_DOC}" )
  message (STATUS)
  message (STATUS "-------------------------------")
  message (STATUS "--- Packaging Configuration ---")
  message (STATUS "-------------------------------")
  message (STATUS "CPACK_PACKAGE_CONTACT = ${CPACK_PACKAGE_CONTACT}")
  message (STATUS "CPACK_PACKAGE_VENDOR = ${CPACK_PACKAGE_VENDOR}")
  message (STATUS "CPACK_PACKAGE_VERSION = ${CPACK_PACKAGE_VERSION}")
  message (STATUS "CPACK_PACKAGE_DESCRIPTION_FILE = ${CPACK_PACKAGE_DESCRIPTION_FILE}")
  message (STATUS "CPACK_RESOURCE_FILE_LICENSE = ${CPACK_RESOURCE_FILE_LICENSE}")
  message (STATUS "CPACK_GENERATOR = ${CPACK_GENERATOR}")
  message (STATUS "CPACK_DEBIAN_PACKAGE_DEPENDS = ${CPACK_DEBIAN_PACKAGE_DEPENDS}")
  message (STATUS "CPACK_SOURCE_GENERATOR = ${CPACK_SOURCE_GENERATOR}")
  message (STATUS "CPACK_SOURCE_PACKAGE_FILE_NAME = ${CPACK_SOURCE_PACKAGE_FILE_NAME}")
  #
  message (STATUS)
  message (STATUS "--------------------------")
  message (STATUS "--- External libraries ---")
  message (STATUS "--------------------------")
  #
  display_boost ()
  display_mysql ()
  display_soci ()
  display_stdair ()
  #
  message (STATUS)
  message (STATUS "Change a value with: cmake -D<Variable>=<Value>" )
  message (STATUS "=============================================================")
  message (STATUS)
endmacro (display_status)
