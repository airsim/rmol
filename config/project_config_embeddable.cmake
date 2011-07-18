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
  # Basic documentation (i.e., AUTHORS, NEWS, README, INSTALL)
  set (BASICDOC_FILES AUTHORS NEWS README INSTALL)
  set (BASICDOC_PATH "share/doc/${PACKAGE}-${PACKAGE_VERSION}")

endmacro (set_project_options)

#
macro (install_basic_documentation)
  install (FILES ${BASICDOC_FILES} DESTINATION ${BASICDOC_PATH})
endmacro (install_basic_documentation)


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
macro (packaging_init _project_name)
  include (InstallRequiredSystemLibraries)
  set (CPACK_PACKAGE_NAME "${_project_name}")
endmacro (packaging_init)

#
macro (packaging_set_description _project_description)
  set (CPACK_PACKAGE_DESCRIPTION "${_project_description}")
endmacro (packaging_set_description)

#
macro (packaging_set_summary _project_summary)
  set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "${_project_summary}")
endmacro (packaging_set_summary)

#
macro (packaging_set_contact _project_contact)
  set (CPACK_PACKAGE_CONTACT "${_project_contact}")
endmacro (packaging_set_contact)

#
macro (packaging_set_vendor _project_vendor)
  set (CPACK_PACKAGE_VENDOR "${_project_vendor}")
endmacro (packaging_set_vendor)

#
macro (packaging_set_other_options)
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

  #
  include (CPack)

  # Add a 'dist' target, similar to what is given by GNU Autotools
  add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

endmacro (packaging_set_other_options)


###################################################################
##                         Dependencies                          ##
###################################################################
# ~~~~~~~~ Wrapper ~~~~~~~~
macro (get_external_libs)
  # CMake scripts, to find some dependencies (e.g., Boost, MySQL, SOCI)
  set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/config/)

  #
  set (PROJ_DEP_LIBS_FOR_LIB "")
  set (PROJ_DEP_LIBS_FOR_BIN "")
  set (PROJ_DEP_LIBS_FOR_TST "")
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

# ~~~~~~~~~~ Git ~~~~~~~~~~
macro (get_git)
  message (STATUS "Requires Git without specifying any version")

  find_package (Git)
  if (Git_FOUND)
	Git_WC_INFO (${CMAKE_CURRENT_SOURCE_DIR} PROJ)
	set (GIT_REVISION ${PROJ_WC_REVISION_HASH})
	message (STATUS "Current Git revision name: ${PROJ_WC_REVISION_NAME}")
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
  set (BOOST_REQUIRED_COMPONENTS
    program_options date_time iostreams serialization filesystem 
    unit_test_framework)
  find_package (Boost ${_required_version} REQUIRED
    COMPONENTS ${BOOST_REQUIRED_COMPONENTS})

  if (Boost_FOUND)
    # 
    set (Boost_HUMAN_VERSION
      ${Boost_MAJOR_VERSION}.${Boost_MINOR_VERSION}.${Boost_SUBMINOR_VERSION})
    message (STATUS "Found Boost version: ${Boost_HUMAN_VERSION}")

    # Update the list of include directories for the project
    include_directories (${Boost_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    set (PROJ_DEP_LIBS_FOR_LIB ${PROJ_DEP_LIBS_FOR_LIB}
      ${Boost_IOSTREAMS_LIBRARY} ${Boost_SERIALIZATION_LIBRARY}
      ${Boost_FILESYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY})
    set (PROJ_DEP_LIBS_FOR_BIN ${PROJ_DEP_LIBS_FOR_BIN}
      ${Boost_PROGRAM_OPTIONS_LIBRARY})
    set (PROJ_DEP_LIBS_FOR_TST ${PROJ_DEP_LIBS_FOR_TST}
      ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

    # For display purposes
    set (BOOST_REQUIRED_LIBS
      ${Boost_IOSTREAMS_LIBRARY} ${Boost_SERIALIZATION_LIBRARY}
      ${Boost_FILESYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY}
      ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

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

    # Update the list of include directories for the project
    include_directories (${MYSQL_INCLUDE_DIR})

    # Update the list of dependencies for the project
    set (PROJ_DEP_LIBS_FOR_LIB ${PROJ_DEP_LIBS_FOR_LIB} ${MYSQL_LIBRARIES})
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
    #
    message (STATUS "Found SOCI version: ${SOCI_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SOCI_INCLUDE_DIR})

    # Update the list of dependencies for the project
    set (PROJ_DEP_LIBS_FOR_LIB ${PROJ_DEP_LIBS_FOR_LIB} ${SOCI_LIBRARIES})
  endif (SOCI_FOUND)

  find_package (SOCIMySQL)
  if (SOCIMYSQL_FOUND)
    #
    message (STATUS "Found MySQL back-end support for SOCI")

    # Update the list of include directories for the project
    include_directories (${SOCIMYSQL_INCLUDE_DIR})

    # Update the list of dependencies for the project
    set (PROJ_DEP_LIBS_FOR_LIB ${PROJ_DEP_LIBS_FOR_LIB} ${SOCIMYSQL_LIBRARIES})
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
    #
    message (STATUS "Found StdAir version: ${STDAIR_VERSION}")

    # Update the list of include directories for the project
    include_directories (${STDAIR_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    set (PROJ_DEP_LIBS_FOR_LIB ${PROJ_DEP_LIBS_FOR_LIB} ${STDAIR_LIBRARIES})

  else (StdAir_FOUND)
    set (ERROR_MSG "The StdAir library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_STDAIR_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<StdAir install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (StdAir_FOUND)

endmacro (get_stdair)


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

  ##
  # Initialise the list of targets to build: libraries, binaries and tests
  set (PROJ_ALL_LIB_TARGETS "")
  set (PROJ_ALL_BIN_TARGETS "")
  set (PROJ_ALL_TST_TARGETS "")

endmacro (init_build)

####
## Module support
####

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

# Set the name of the module
macro (module_set_name _module_name)
  set (MODULE_NAME ${_module_name})
  set (MODULE_LIB_TARGET ${MODULE_NAME}lib)
endmacro (module_set_name)

##
# Convert the configuration headers (basically, just replace the @<variable>@
# variables).
macro (module_generate_config_helpers)

  # Generic module configuration header
  if (EXISTS config.h.in)
    configure_file (config.h.in config.h @ONLY)
  endif (EXISTS config.h.in)

  # Specific module configuration header
  set (PROJ_PATH_CFG_SRC 
    ${CMAKE_CURRENT_SOURCE_DIR}/config/${MODULE_NAME}-paths.hpp.in)
  if (EXISTS ${PROJ_PATH_CFG_SRC})
    set (PROJ_PATH_CFG
      ${CMAKE_CURRENT_BINARY_DIR}/config/${MODULE_NAME}-paths.hpp)
    configure_file (${PROJ_PATH_CFG_SRC} ${PROJ_PATH_CFG} @ONLY)
  
    # Add the 'hdr_cfg_${MODULE_NAME}' target, depending on the converted header
    add_custom_target (hdr_cfg_${MODULE_NAME} ALL DEPENDS ${PROJ_PATH_CFG})

  else (EXISTS ${PROJ_PATH_CFG_SRC})
    message (FATAL_ERROR "The ${PROJ_PATH_CFG_SRC} file is missing.")
  endif (EXISTS ${PROJ_PATH_CFG_SRC})

endmacro (module_generate_config_helpers)

##
# Library sources.
macro (module_define_sources)
  # Collect the header and source files at the root level of the module
  file (GLOB ${MODULE_LIB_TARGET}_root_HEADERS *.hpp)
  set (${MODULE_LIB_TARGET}_HEADERS 
    ${PROJ_PATH_CFG} ${${MODULE_LIB_TARGET}_root_HEADERS})
  
  file (GLOB ${MODULE_LIB_TARGET}_root_SOURCES *.cpp)
  set (${MODULE_LIB_TARGET}_SOURCES ${${MODULE_LIB_TARGET}_root_SOURCES})

  # Collect the header and source files for all the other layers, as
  # specified as input paramters of this macro
  foreach (_layer ${ARGV})
    file (GLOB ${MODULE_LIB_TARGET}_${_layer}_HEADERS ${_layer}/*.hpp)
    set (${MODULE_LIB_TARGET}_HEADERS
      ${${MODULE_LIB_TARGET}_HEADERS} ${${MODULE_LIB_TARGET}_${_layer}_HEADERS})

    file (GLOB ${MODULE_LIB_TARGET}_${_layer}_SOURCES ${_layer}/*.cpp)
    set (${MODULE_LIB_TARGET}_SOURCES 
      ${${MODULE_LIB_TARGET}_SOURCES} ${${MODULE_LIB_TARGET}_${_layer}_SOURCES})
  endforeach (_layer ${ARGV})

  # Gather both the header and source files into a single list
  set (${MODULE_LIB_TARGET}_SOURCES
    ${${MODULE_LIB_TARGET}_HEADERS} ${${MODULE_LIB_TARGET}_SOURCES})
endmacro (module_define_sources)

##
# Assembling: specify the standard library target for the current module.
# The parameter corresponds to the modules this current module depends upon.
macro (module_library_add_standard)
  # Add the (CMake) target for the library
  add_library (${MODULE_LIB_TARGET} SHARED ${${MODULE_LIB_TARGET}_SOURCES})

  # For each module, given as parameter of that macro, add the corresponding
  # library target to a dedicated list
  set (_intermodule_dependencies "")
  foreach (_arg_module ${ARGV})
    set (_intermodule_dependencies
      ${_intermodule_dependencies} ${_arg_module}lib)
  endforeach (_arg_module)

  # Add the dependencies:
  #  * on external libraries (Boost, MySQL, SOCI, StdAir), as calculated by 
  #    the get_external_libs() macro above;
  #  * on the other module libraries, as provided as paramaters to this macro
  target_link_libraries (${MODULE_LIB_TARGET} 
    ${PROJ_DEP_LIBS_FOR_LIB} ${_intermodule_dependencies})

  # Add the dependency on the generated configuration headers, as generated
  # by the module_generate_config_helpers() macro
  add_dependencies (${MODULE_LIB_TARGET} hdr_cfg_${MODULE_NAME})

  # Register the library target in the project (for reporting purpose)
  set (PROJ_ALL_LIB_TARGETS
	${PROJ_ALL_LIB_TARGETS} ${MODULE_LIB_TARGET} PARENT_SCOPE)

  ##
  # Library name (and soname)
  set (_module_lib_name ${MODULE_NAME})
  if (WIN32)
    set_target_properties (${MODULE_LIB_TARGET} PROPERTIES 
      OUTPUT_NAME ${_module_lib_name} 
      VERSION ${GENERIC_LIB_VERSION}
      PUBLIC_HEADER "${${MODULE_LIB_TARGET}_root_HEADERS}")
  else (WIN32)
    set_target_properties (${MODULE_LIB_TARGET} PROPERTIES 
      OUTPUT_NAME ${_module_lib_name}
      VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
      PUBLIC_HEADER "${${MODULE_LIB_TARGET}_root_HEADERS}")
  endif (WIN32)

endmacro (module_library_add_standard)

##
# Library installation
# The parameter corresponds to additional libraries to be installed.
# When no parameter is given, only the standard library is installed.
macro (module_library_install_all)
  set (_all_targets ${MODULE_LIB_TARGET})
  foreach (_arg_target ${ARGV})
    set (_all_targets ${_all_targets} ${_arg_target})
  endforeach (_arg_target)

  install (TARGETS ${_all_targets}
    EXPORT ${LIB_DEPENDENCY_EXPORT}
    RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT runtime
    LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT runtime
    PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${MODULE_NAME}"
    COMPONENT devel)

endmacro (module_library_install_all)

##
# Install the CMake import helper, so that third party projects can refer to it
# (for libraries, header files and binaries)
macro (module_export_install)
  install (EXPORT ${LIB_DEPENDENCY_EXPORT} DESTINATION
    "${INSTALL_DATA_DIR}/${PACKAGE}/CMake" COMPONENT devel)
endmacro (module_export_install)

##
# Assembling: specify the standard binary target for the current module.
macro (module_binary_add_standard)
  # Register the binary
  add_executable (${MODULE_NAME} batches/${MODULE_NAME}.cpp)

  # Register the dependencies on which the binary depends upon
  target_link_libraries (${MODULE_NAME}
	${PROJ_DEP_LIBS_FOR_BIN} ${MODULE_LIB_TARGET} ${_intermodule_dependencies})

  # Register the binary target in the project (for reporting purpose)
  set (PROJ_ALL_BIN_TARGETS ${PROJ_ALL_BIN_TARGETS} ${MODULE_NAME} PARENT_SCOPE)
endmacro (module_binary_add_standard)

##
# Binary installation
# The parameter corresponds to additional binaries to be installed.
# When no parameter is given, only the standard binary is installed.
macro (module_binary_install_all)
  install (TARGETS ${MODULE_NAME} 
	EXPORT ${LIB_DEPENDENCY_EXPORT}
	RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT runtime)
endmacro (module_binary_install_all)


###################################################################
##                            Tests                              ##
###################################################################
#
macro (add_test_suites _test_suite_dir_list)
  if (Boost_FOUND)
	# Tell CMake/CTest that tests will be performed
	enable_testing() 

	#
	foreach (_module_name ${_test_suite_dir_list})
	  set (${_module_name}_ALL_TST_TARGETS "")
	  # Each individual test suite is specified within the dedicated
	  # sub-directory
	  add_subdirectory (test/${_module_name})
	  add_custom_target (check DEPENDS check_${_module_name}tst)
	endforeach (_module_name)
  endif (Boost_FOUND)

endmacro (add_test_suites)

#
macro (module_test_add_suite _test_name _test_sources)
  if (Boost_FOUND)
	# Register the test binary target
	add_executable (${_test_name} ${_test_sources})

	# Build the list of library targets on which that test depends upon
	set (_library_lists "")
	foreach (_arg_lib ${ARGV})
	  if (NOT ${_arg_lib} STREQUAL ${_test_name}
		  AND NOT ${_arg_lib} STREQUAL ${_test_sources})
		set (_library_lists ${_library_lists} ${_arg_lib})
	  endif ()
	endforeach (_arg_lib)

	# Tell the test binary that it depends on all those libraries
	target_link_libraries (${_test_name} ${_library_lists} 
	  ${MODULE_LIB_TARGET} ${PROJ_DEP_LIBS_FOR_TST})

	# Register the binary target in the module
	set (${MODULE_NAME}_ALL_TST_TARGETS
	  ${${MODULE_NAME}_ALL_TST_TARGETS} ${_test_name})

	# Register the test
	if (WIN32)
	  add_test (${_test_name} ${_test_name}.exe)
	else (WIN32)
	  add_test (${_test_name} ${_test_name})
	endif (WIN32)
  endif (Boost_FOUND)

  # Register the binary target in the project (for reporting purpose)
  set (PROJ_ALL_TST_TARGETS
	${PROJ_ALL_TST_TARGETS} ${${MODULE_NAME}_ALL_TST_TARGETS} PARENT_SCOPE)

endmacro (module_test_add_suite)

#
macro (module_test_build_all)
  if (Boost_FOUND)
	# Tell how to test, i.e., how to run the test binaries 
	# and collect the results
	add_custom_target (check_${MODULE_NAME}tst
	  COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${PROJ_ALL_TST_TARGETS})
  endif (Boost_FOUND)
endmacro (module_test_build_all)


###################################################################
##                    Development Helpers                        ##
###################################################################
# For other projects to use this component (let us name it myproj),
# install a few helpers for standard build/packaging systems: CMake,
# GNU Autotools (M4), pkgconfig/pc, myproj-config
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
	message (STATUS "  - Boost required components . : ${BOOST_REQUIRED_COMPONENTS}")
	message (STATUS "  - Boost required libraries .. : ${BOOST_REQUIRED_LIBS}")
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
  message (STATUS "Libraries to build ... : ${PROJ_ALL_LIB_TARGETS}")
  message (STATUS "Binaries to build .... : ${PROJ_ALL_BIN_TARGETS}")
  message (STATUS "Tests to build ....... : ${PROJ_ALL_TST_TARGETS}")
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
