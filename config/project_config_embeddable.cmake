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
endmacro (set_project_names)

##
# Set the project brief
macro (set_project_brief _project_brief)
  set (PACKAGE_BRIEF ${_project_brief})
endmacro (set_project_brief)


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
#  * BUILD_SHARED_LIBS    - Whether or not to build shared libraries
#  * CMAKE_BUILD_TYPE     - Debug or release
#  * CMAKE_INSTALL_PREFIX - Where to install the deliverable parts
#  * CMAKE_INSTALL_RPATH  - The list of paths to be used by the linker
#  * CMAKE_INSTALL_RPATH_USE_LINK_PATH
#                         - Whether or not to set the run-path/rpath within
#                           the (executable and library) binaries
#  * ENABLE_TEST          - Whether or not to build and check the unit tests
#  * INSTALL_DOC          - Whether or not to build and install the documentation
#  * INSTALL_LIB_DIR      - Installation directory for the libraries
#  * INSTALL_PY_LIB_DIR   - Installation directory for the Python libraries
#  * INSTALL_BIN_DIR      - Installation directory for the binaries
#  * INSTALL_LIBEXEC_DIR  - Installation directory for the internal executables
#  * INSTALL_INCLUDE_DIR  - Installation directory for the header files
#  * INSTALL_DATA_DIR     - Installation directory for the data files
#  * INSTALL_SAMPLE_DIR   - Installation directory for the (CSV) sample files
#  * NEED_PYTHON          - Whether Python libraries are needed
#                           That paremeter is derived from the required libraries
#  * RUN_GCOV             - Whether or not to perform code coverage
#
macro (set_project_options _build_doc _enable_tests _run_gcov)
  # C++ standard (C++-11)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

  # Unit tests (thanks to CMake/CTest)
  option (ENABLE_TEST "Set to OFF to skip build/check unit tests"
	${_enable_tests})

  # Documentation
  option (INSTALL_DOC "Set to OFF to skip build/install Documentation" 
    ${_build_doc})

  # Initialise a few variables
  set (DOXYGEN_OUTPUT_REL)
  set (REFMAN_TEX)
  set (REFMAN_PDF)
  set (CSS_ALL_TARGETS)
  set (IMG_ALL_TARGETS)
  set (MAN_ALL_TARGETS)
  set (NEED_PYTHON OFF)

  # Set the library installation directory (either 32 or 64 bits)
  set (LIBDIR "lib${LIB_SUFFIX}" CACHE PATH
    "Library directory name, either lib or lib64")

  # Offer the user the choice of overriding the installation directories
  set (INSTALL_LIB_DIR ${LIBDIR} CACHE PATH
	"Installation directory for libraries")
  set (INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
  set (INSTALL_LIBEXEC_DIR CACHE PATH
	"Installation directory for internal executables")
  set (INSTALL_INCLUDE_DIR include CACHE PATH
    "Installation directory for header files")
  set (INSTALL_DATA_DIR share CACHE PATH "Installation directory for data files")
  set (INSTALL_SAMPLE_DIR share/${PROJECT_NAME}/samples CACHE PATH
    "Installation directory for (CSV) sample files")
  set (INSTALL_ETC_DIR etc CACHE PATH "Installation directory for Config files")

  # GCOV
  option (RUN_GCOV "Set to OFF to skip code coverage" ${_run_gcov})

  # Make relative paths absolute (needed later on)
  foreach (_path_type LIB PY_LIB BIN LIBEXEC INCLUDE DATA SAMPLE)
    set (var INSTALL_${_path_type}_DIR)
    if (NOT IS_ABSOLUTE "${${var}}")
      set (${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
    endif ()
  endforeach (_path_type)

  # When the install directory is not the canonical one (i.e., /usr),
  # the run-path/rpath must be set in all the (executable and library)
  # binaries, so that the dynamic loader can find the dependencies
  # without the user having to set the LD_LIBRARY_PATH environment
  # variable.
  if (CMAKE_INSTALL_PREFIX STREQUAL "/usr")
    set (CMAKE_INSTALL_RPATH "")
    set (CMAKE_INSTALL_RPATH_USE_LINK_PATH OFF)
  else()
    set (CMAKE_INSTALL_RPATH ${INSTALL_LIB_DIR} ${INSTALL_PY_LIB_DIR})
    set (CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
  endif()

  # Define STDAIR_SAMPLE_DIR if the project is STDAIR
  if ("${PROJECT_NAME}" STREQUAL "stdair")
    set (STDAIR_SAMPLE_DIR ${INSTALL_SAMPLE_DIR})
  endif ("${PROJECT_NAME}" STREQUAL "stdair")

  # Define OPENTREP_SAMPLE_DIR if the project is OPENTREP
  if ("${PROJECT_NAME}" STREQUAL "opentrep")
    set (OPENTREP_SAMPLE_DIR ${INSTALL_DATA_DIR}/${PACKAGE}/data)
  endif ("${PROJECT_NAME}" STREQUAL "opentrep")

  ##
  # Basic documentation (i.e., AUTHORS, NEWS, README, INSTALL)
  set (DOC_INSTALL_FILE INSTALL)
  if (NOT EXISTS ${DOC_INSTALL_FILE})
    unset (DOC_INSTALL_FILE)
  endif (NOT EXISTS ${DOC_INSTALL_FILE})
  set (DOC_NEWS_FILE NEWS)
  if (NOT EXISTS ${DOC_NEWS_FILE})
    unset (DOC_NEWS_FILE)
  endif (NOT EXISTS ${DOC_NEWS_FILE})
  set (BASICDOC_FILES AUTHORS ${DOC_NEWS_FILE} README.md ${DOC_INSTALL_FILE})
  set (BASICDOC_PATH "share/doc/${PACKAGE}")

endmacro (set_project_options)

#
macro (install_basic_documentation)
  install (FILES ${BASICDOC_FILES} DESTINATION ${BASICDOC_PATH})
endmacro (install_basic_documentation)


#
macro (store_in_cache)
  # Force some variables that could be defined in the command line to be
  # written to cache
  set (PACKAGE_VERSION "${PACKAGE_VERSION}" CACHE STRING
    "Version of the project/package")
  set (BUILD_SHARED_LIBS "${BUILD_SHARED_LIBS}" CACHE BOOL
    "Set to OFF to build static libraries" FORCE)
  set (CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}" CACHE PATH
    "Where to install ${PROJECT_NAME}" FORCE)
  set (CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_RPATH}" CACHE PATH
    "Run-path for the library/executable binaries" FORCE)
  set (CMAKE_INSTALL_RPATH_USE_LINK_PATH "${CMAKE_INSTALL_RPATH_USE_LINK_PATH}"
    CACHE BOOL
    "Whether to set the run-path for the library/executable binaries" FORCE)
  set (CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING
    "C++ compilation flags" FORCE)
  set (COMPILE_FLAGS "${COMPILE_FLAGS}" CACHE STRING
    "Supplementary C++ compilation flags" FORCE)
  set (CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" CACHE PATH
    "Path to custom CMake Modules" FORCE)
  set (ENABLE_TEST "${ENABLE_TEST}" CACHE BOOL
    "Set to OFF to skip build/check unit tests" FORCE)
  set (INSTALL_DOC "${INSTALL_DOC}" CACHE BOOL
    "Set to OFF to skip build/install Documentation" FORCE)
  set (RUN_GCOV "${RUN_GCOV}" CACHE BOOL
    "Set to OFF to skip coverage tests" FORCE)
endmacro (store_in_cache)


#####################################
##            Packaging            ##
#####################################
#
macro (packaging_init _project_name)
  set (CPACK_PACKAGE_NAME "${_project_name}")
  set (CPACK_PACKAGE_DESCRIPTION "${PACKAGE_BRIEF}")
endmacro (packaging_init)

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

# Both parameters are semi-colon sepetated lists of the types of
# packages to generate, e.g., "TGZ;TBZ2"
macro (packaging_set_other_options _package_type_list _source_package_type_list)
  #
  set (CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_VERSION_MAJOR})
  set (CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_VERSION_MINOR})
  #set (CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_VERSION_PATCH})
  set (CPACK_PACKAGE_VERSION_PATCH ${GIT_REVISION})
  set (CPACK_PACKAGE_VERSION ${${PROJECT_NAME}_VERSION})

  # Basic documentation
  if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
    message (FATAL_ERROR "A README.md file must be defined and located at the root directory")
  endif (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
  set (CPACK_PACKAGE_DESCRIPTION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/README.md)
  set (CPACK_RESOURCE_FILE_README ${CMAKE_CURRENT_SOURCE_DIR}/README.md)

  # Licence
  if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
    message (FATAL_ERROR "A licence file, namely COPYING, must be defined and located at the root directory")
  endif (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)
  set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/COPYING)

  ##
  # Reset the generators for the binary packages
  # Available types of package: DEB, RPM, STGZ, TZ, TGZ, TBZ2
  set (CPACK_GENERATOR "${_package_type_list}")
  #set (CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.6), libgcc1 (>= 1:4.1)")

  ##
  # Source packages
  # Available types of package: TZ, TGZ, TBZ2
  set (CPACK_SOURCE_GENERATOR "${_source_package_type_list}")

  set (CPACK_SOURCE_PACKAGE_FILE_NAME 
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}"
    CACHE INTERNAL "tarball basename")
  set (AUTOTOOLS_IGNRD "/tmp/;/tmp2/;/autom4te\\\\.cache/;autogen\\\\.sh$")
  set (PACK_IGNRD
	"${CMAKE_CURRENT_BINARY_DIR};${CPACK_PACKAGE_NAME}\\\\.spec;\\\\.gz$;\\\\.bz2$")
  set (EDIT_IGNRD "\\\\.swp$;\\\\.#;/#;~$")
  set (SCM_IGNRD 
    "/CVS/;/\\\\.svn/;/\\\\.bzr/;/\\\\.hg/;/\\\\.git/;\\\\.gitignore$")
  set (PYTHON_IGNRD "\\\\.pyc$;\\\\.pyo$")
  set (JS_IGNRD "/browser/js/libs;/browser/js/mylibs;/browser/libs")
  set (CPACK_SOURCE_IGNORE_FILES
    "${AUTOTOOLS_IGNRD};${SCM_IGNRD};${EDIT_IGNRD};${PACK_IGNRD};${PYTHON_IGNRD};${JS_IGNRD}"
    CACHE STRING "CPACK will ignore these files")
  #set (CPACK_SOURCE_IGNORE_DIRECTORY ${CPACK_SOURCE_IGNORE_FILES} .git)

  # Initialise the source package generator with the variables above
  include (InstallRequiredSystemLibraries)
  include (CPack)

  # Add a 'dist' target, similar to what is given by GNU Autotools
  add_custom_target (dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)

  ##
  # Reset the generator types for the binary packages. Indeed, the variable
  # has been reset by "include (CPack)".
  set (CPACK_GENERATOR "${_package_type_list}")

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
  set (PROJ_DEP_LIBS_FOR_PYEXT "")
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

    if (${_arg_lower} STREQUAL "gcov")
      get_gcov (${_arg_version})
    endif (${_arg_lower} STREQUAL "gcov")

    if (${_arg_lower} STREQUAL "lcov")
      get_lcov (${_arg_version})
    endif (${_arg_lower} STREQUAL "lcov")

    if (${_arg_lower} STREQUAL "python")
      set (NEED_PYTHON ON)
      get_python (${_arg_version})
    endif (${_arg_lower} STREQUAL "python")

    if (${_arg_lower} STREQUAL "icu")
      get_icu (${_arg_version})
    endif (${_arg_lower} STREQUAL "icu")

    if (${_arg_lower} STREQUAL "zeromq")
      get_zeromq (${_arg_version})
    endif (${_arg_lower} STREQUAL "zeromq")

    if (${_arg_lower} STREQUAL "boost")
      get_boost (${_arg_version})
    endif (${_arg_lower} STREQUAL "boost")

    if (${_arg_lower} STREQUAL "protobuf")
      get_protobuf (${_arg_version})
    endif (${_arg_lower} STREQUAL "protobuf")

    if (${_arg_lower} STREQUAL "xapian")
      get_xapian (${_arg_version})
    endif (${_arg_lower} STREQUAL "xapian")

    if (${_arg_lower} STREQUAL "readline")
      get_readline (${_arg_version})
    endif (${_arg_lower} STREQUAL "readline")

    if (${_arg_lower} STREQUAL "curses")
      get_curses (${_arg_version})
    endif (${_arg_lower} STREQUAL "curses")

    if (${_arg_lower} STREQUAL "sqlite")
      get_sqlite (${_arg_version})
    endif (${_arg_lower} STREQUAL "sqlite")

    if (${_arg_lower} STREQUAL "mysql")
      get_mysql (${_arg_version})
    endif (${_arg_lower} STREQUAL "mysql")

    if (${_arg_lower} STREQUAL "soci")
      get_soci (${_arg_version})
    endif (${_arg_lower} STREQUAL "soci")

    if (${_arg_lower} STREQUAL "optd")
      get_optd (${_arg_version})
    endif (${_arg_lower} STREQUAL "optd")

    if (${_arg_lower} STREQUAL "stdair")
      get_stdair (${_arg_version})
    endif (${_arg_lower} STREQUAL "stdair")

    if (${_arg_lower} STREQUAL "sevmgr")
      get_sevmgr (${_arg_version})
    endif (${_arg_lower} STREQUAL "sevmgr")

    if (${_arg_lower} STREQUAL "trademgen")
      get_trademgen (${_arg_version})
    endif (${_arg_lower} STREQUAL "trademgen")

    if (${_arg_lower} STREQUAL "travelccm")
      get_travelccm (${_arg_version})
    endif (${_arg_lower} STREQUAL "travelccm")

    if (${_arg_lower} STREQUAL "airtsp")
      get_airtsp (${_arg_version})
    endif (${_arg_lower} STREQUAL "airtsp")

    if (${_arg_lower} STREQUAL "airrac")
      get_airrac (${_arg_version})
    endif (${_arg_lower} STREQUAL "airrac")

    if (${_arg_lower} STREQUAL "rmol")
      get_rmol (${_arg_version})
    endif (${_arg_lower} STREQUAL "rmol")

    if (${_arg_lower} STREQUAL "airinv")
      get_airinv (${_arg_version})
    endif (${_arg_lower} STREQUAL "airinv")

    if (${_arg_lower} STREQUAL "avlcal")
      get_avlcal (${_arg_version})
    endif (${_arg_lower} STREQUAL "avlcal")

    if (${_arg_lower} STREQUAL "simfqt")
      get_simfqt (${_arg_version})
    endif (${_arg_lower} STREQUAL "simfqt")

    if (${_arg_lower} STREQUAL "simlfs")
      get_simlfs (${_arg_version})
    endif (${_arg_lower} STREQUAL "simlfs")

    if (${_arg_lower} STREQUAL "simcrs")
      get_simcrs (${_arg_version})
    endif (${_arg_lower} STREQUAL "simcrs")

    if (${_arg_lower} STREQUAL "tvlsim")
      get_tvlsim (${_arg_version})
    endif (${_arg_lower} STREQUAL "tvlsim")

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

# ~~~~~~~~~~ Gcov ~~~~~~~~~~
macro (get_gcov)
  if (${RUN_GCOV} STREQUAL "ON")	
    message (STATUS "Requires gcov without specifying any version")

    find_package (GCOV)
    if (GCOV_FOUND)
      GCOV_WC_INFO (${CMAKE_CURRENT_SOURCE_DIR} PROJ)
      set (GCOV_REVISION ${PROJ_WC_REVISION_HASH})
      message (STATUS "Current gcov revision name: ${PROJ_WC_REVISION_NAME}")
    endif (GCOV_FOUND)
  endif (${RUN_GCOV} STREQUAL "ON")
endmacro (get_gcov)

# ~~~~~~~~~~ Lcov ~~~~~~~~~~
macro (get_lcov)
  if (${RUN_GCOV} STREQUAL "ON")	
    message (STATUS "Requires lcov without specifying any version")

    find_package (LCOV)
    if (LCOV_FOUND)
      LCOV_WC_INFO (${CMAKE_CURRENT_SOURCE_DIR} PROJ)
      set (LCOV_REVISION ${PROJ_WC_REVISION_HASH})
      message (STATUS "Current lcov revision name: ${PROJ_WC_REVISION_NAME}")
    endif (LCOV_FOUND)
  endif (${RUN_GCOV} STREQUAL "ON")	
endmacro (get_lcov)

# ~~~~~~~~~~ Python ~~~~~~~~~
macro (get_python)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires Python with version ${_required_version}; however just Python3 is considered here")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires Python3; any version will do")
  endif (${ARGC} GREATER 0)

  # The first check searches for the libraries and include paths.
  # However, on some older versions (e.g., on RedHat/CentOS 5.x),
  # only the static library is searched.
  find_package (Python3 COMPONENTS Development REQUIRED)

  # Python extension
  #find_package (PythonExtensions REQUIRED)
  include(targetLinkLibrariesWithDynamicLookup)

  # The second check is to get the dynamic library for sure.
  #find_package (PythonLibsWrapper ${_required_version} REQUIRED)

  if (Python3_FOUND)
    message (STATUS "Found Python3 ${Python3_VERSION} (${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}.${Python3_VERSION_PATCH})")

    # Set the Python installation directory
    set (INSTALL_PY_LIB_DIR
      ${INSTALL_LIB_DIR}/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages/py${PROJECT_NAME}
      CACHE PATH "Installation directory for Python libraries")

    # Update the list of include directories for the project
    include_directories (${Python3_INCLUDE_DIRS})

  else (Python3_FOUND)
	message (FATAL_ERROR "Python libraries are missing. Please install them (e.g., 'python-devel' for the Fedora/RedHat package)")
  endif (Python3_FOUND)

endmacro (get_python)

# ~~~~~~~~~~ ICU ~~~~~~~~~
macro (get_icu)
  if (${CMAKE_VERSION} VERSION_GREATER 3.12)
    cmake_policy (SET CMP0074 NEW)
  endif (${CMAKE_VERSION} VERSION_GREATER 3.12)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires ICU-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires ICU without specifying any version")
  endif (${ARGC} GREATER 0)

  # 
  set (ICU_REQUIRED_COMPONENTS i18n uc data)
  find_package (ICU ${_required_version}
	COMPONENTS ${ICU_REQUIRED_COMPONENTS} REQUIRED)

  icudebug (ICU_I18N_FOUND)
  if (ICU_FOUND)
	#
	#if (ICU_I18N_FOUND)
	#  icudebug (ICU_I18N_FOUND)
	#endif (ICU_I18N_FOUND)

    # Update the list of include directories for the project
    include_directories (${ICU_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${ICU_LIBRARIES})
  endif (ICU_FOUND)

endmacro (get_icu)

# ~~~~~~~~~~ ZeroMQ ~~~~~~~~~
macro (get_zeromq)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires ZeroMQ-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires ZeroMQ without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (ZeroMQ ${_required_version} REQUIRED)

  if (ZEROMQ_FOUND)
    # Update the list of include directories for the project
    include_directories (${ZeroMQ_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${ZeroMQ_LIBRARIES})
  endif (ZEROMQ_FOUND)

endmacro (get_zeromq)

# ~~~~~~~~~~ BOOST ~~~~~~~~~~
# Derive the names of required Boost libraries, usually something like
# Boost_CPTNAME_LIBRARY, where CPTNAME is the name of the component
# (e.g., regex, locale)
macro (register_boost_lib _boost_lib_list_name _boost_lib_list)
  # Update the list of library dependencies for the project
  foreach (_lib_cpt ${_boost_lib_list})
    string (TOUPPER ${_lib_cpt} _lib_cpt_up)

    if (Boost_${_lib_cpt_up}_LIBRARY)
      # Update the list of dependencies for the project
      list (APPEND ${_boost_lib_list_name} ${Boost_${_lib_cpt_up}_LIBRARY})

      # Update the list of libraries to be displayed
      list (APPEND BOOST_REQUIRED_LIBS ${Boost_${_lib_cpt_up}_LIBRARY})
    endif (Boost_${_lib_cpt_up}_LIBRARY)
  endforeach (_lib_cpt ${_boost_lib_list})
endmacro (register_boost_lib _boost_lib_list_name _boost_lib_list)

#
macro (get_boost)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires Boost-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires Boost without specifying any version")
  endif (${ARGC} GREATER 0)
 
  #
  # Note 1: ${Boost_DATE_TIME_LIBRARY} and ${Boost_PROGRAM_OPTIONS_LIBRARY}
  #         are already set by ${SOCIMYSQL_LIBRARIES} and/or ${SOCI_LIBRARIES}.
  # Note 2: Boost libraries are not installed in a consistent way across the
  #         the different platforms and versions of Boost.
  #         For a while, the Boost.Python library component was just called
  #         'python'. It is now suffixed with the version of Python, and
  #         on some Linux distributions, there is even a '-py' suffix.
  #         On some platform/Boost version combinations, the Python version
  #         may be just the major version (2 or 3 as of 2020) or the major
  #         and minor versions (e.g., 27, 28, 34, 36, 37, 38, 39 as of 2020)
  # Note 3: Boot.Python has is reuired only for Python extensions. It should
  #         not be linked with other regular (non-Python) libraries/binaries,
  #         as it pulls with it symbols from the Python interpreter, which are
  #         available only when launched from a Python interpreter.
  set (Boost_USE_STATIC_LIBS OFF)
  set (Boost_USE_MULTITHREADED ON)
  set (Boost_USE_STATIC_RUNTIME OFF)
  # Boost.Python - Depending on the platforms, the component name
  # differs. We try all of them, and the find_package() will retrieve
  # just one
  if (NEED_PYTHON)
    set (python_cpt_name0 "python")
    #
    if (Python3_VERSION_MAJOR)
      set (python_cpt_name1 "python${Python3_VERSION_MAJOR}")
    endif (Python3_VERSION_MAJOR)
    #
    if (Python3_VERSION_MINOR)
      set (python_cpt_name2 "python${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}")
    endif (Python3_VERSION_MINOR)
  endif (NEED_PYTHON)

  # Boost components for (non-Python) libraries
  set (BOOST_REQUIRED_COMPONENTS_FOR_LIB
    date_time random iostreams serialization filesystem system locale regex)

  # Boost components for Python extensions
  if (NEED_PYTHON)
    set (BOOST_REQUIRED_COMPONENTS_FOR_PYEXT
      ${python_cpt_name0} ${python_cpt_name1} ${python_cpt_name2})
  endif (NEED_PYTHON)    
  
  # Boost components for main (non-test) binaries
  set (BOOST_REQUIRED_COMPONENTS_FOR_BIN program_options)

  # Boost components for test binaries
  set (BOOST_REQUIRED_COMPONENTS_FOR_TST unit_test_framework)

  # Summary for reporting
  set (BOOST_REQUIRED_COMPONENTS ${BOOST_REQUIRED_COMPONENTS_FOR_LIB}
	${BOOST_REQUIRED_COMPONENTS_FOR_BIN} ${BOOST_REQUIRED_COMPONENTS_FOR_TST}
	${BOOST_REQUIRED_COMPONENTS_FOR_PYEXT})

  # The first check is for the required components.
  find_package (Boost COMPONENTS ${BOOST_REQUIRED_COMPONENTS})

  # Fix a bug for some old CMake package finder scripts (e.g., on Fedora 15)
  if (Boost_VERSION)
    set (Boost_FOUND ON)
  endif (Boost_VERSION)

  # The second check is for the required version (FindBoostWrapper.cmake is
  # provided by us). Indeed, the Fedora/RedHat FindBoost.cmake does not seem
  # to provide version enforcement.
  find_package (BoostWrapper ${_required_version} REQUIRED)

  if (Boost_FOUND)

    if (NEED_PYTHON)
      # Boost has a single Python library, but its name depends on the
      # distribution, it can be libboost_python3 or libboost_python3x
      if (Boost_PYTHON_LIBRARY)
	set (BOOST_REQUIRED_COMPONENTS_FOR_PYEXT ${python_cpt_name0})
	if (Python3_VERSION_MAJOR)
	  list (REMOVE_ITEM BOOST_REQUIRED_COMPONENTS ${python_cpt_name1})
	endif (Python3_VERSION_MAJOR)
	if (Python3_VERSION_MINOR)
	  list (REMOVE_ITEM BOOST_REQUIRED_COMPONENTS ${python_cpt_name2})
	endif (Python3_VERSION_MINOR)
      endif (Boost_PYTHON_LIBRARY)

      #
      if (Boost_PYTHON${Python3_VERSION_MAJOR}_LIBRARY)
	set (BOOST_REQUIRED_COMPONENTS_FOR_PYEXT ${python_cpt_name1})
	list (REMOVE_ITEM BOOST_REQUIRED_COMPONENTS ${python_cpt_name0})
	if (Python3_VERSION_MINOR)
	  list (REMOVE_ITEM BOOST_REQUIRED_COMPONENTS ${python_cpt_name2})
	endif (Python3_VERSION_MINOR)
      endif (Boost_PYTHON${Python3_VERSION_MAJOR}_LIBRARY)

      #
      if (Boost_PYTHON${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}_LIBRARY)
	set (BOOST_REQUIRED_COMPONENTS_FOR_PYEXT ${python_cpt_name2})
	list (REMOVE_ITEM BOOST_REQUIRED_COMPONENTS ${python_cpt_name0})
	if (Python3_VERSION_MAJOR)
	  list (REMOVE_ITEM BOOST_REQUIRED_COMPONENTS ${python_cpt_name1})
	endif (Python3_VERSION_MAJOR)
      endif (Boost_PYTHON${Python3_VERSION_MAJOR}${Python3_VERSION_MINOR}_LIBRARY)

      # Reporting
      message (STATUS "  + Retained Boost Python component: ${BOOST_REQUIRED_COMPONENTS_FOR_PYEXT}")
      
      # Derive the Boost.Python component name (amoung Boost_PYTHON,
      # Boost_PYTHON3, Boost_PYTHON3X)
      string (TOUPPER ${BOOST_REQUIRED_COMPONENTS_FOR_PYEXT} _python_cpt)

      # Reporting
      message (STATUS "  + Boost Python component: Boost_${_python_cpt}")

      # Derive the Python version used by Boost.Python
      if (${Boost_${_python_cpt}_LIBRARY} MATCHES "python([1-9])\\.?([0-9])?")
	set (Boost_PYTHON_VERSION "${CMAKE_MATCH_1}${CMAKE_MATCH_2}")
      endif (${Boost_${_python_cpt}_LIBRARY} MATCHES "python([1-9])\\.?([0-9])?")

      # Reporting
      message (STATUS "  + Boost_PYTHON_VERSION: ${Boost_PYTHON_VERSION}")

      # Boost.Python library
      if (Boost_${_python_cpt}_LIBRARY)
	message (STATUS "  + Boost_${_python_cpt}_LIBRARY: ${Boost_${_python_cpt}_LIBRARY}")
      endif (Boost_${_python_cpt}_LIBRARY)
    endif (NEED_PYTHON)

    # Update the list of include directories for the project
    include_directories (${Boost_INCLUDE_DIRS})

    # For display purposes
    set (BOOST_REQUIRED_LIBS "")

    # Update the list of library dependencies for the project
    register_boost_lib ("PROJ_DEP_LIBS_FOR_LIB"
      "${BOOST_REQUIRED_COMPONENTS_FOR_LIB}")

    # Update the list of Python library dependencies for the project
    if (NEED_PYTHON)
      register_boost_lib ("PROJ_DEP_LIBS_FOR_PYEXT"
	"${BOOST_REQUIRED_COMPONENTS_FOR_PYEXT}")
    endif (NEED_PYTHON)

    # Update the list of binary dependencies for the project
    register_boost_lib ("PROJ_DEP_LIBS_FOR_BIN"
      "${BOOST_REQUIRED_COMPONENTS_FOR_BIN}")

    # Update the list of test dependencies for the project
    register_boost_lib ("PROJ_DEP_LIBS_FOR_TST"
      "${BOOST_REQUIRED_COMPONENTS_FOR_TST}")

  endif (Boost_FOUND)

endmacro (get_boost)

##
# The following implementation derives from the eponym function, from
# /usr/share/cmake/Modules/FindProtobuf.cmake, when such a function exists.
# It exists in a Fedora 23+. Note that when the function exists in
# FindProtobuf.cmake, it is not overriden by the implementation below.
#
# PROTOBUF_GENERATE_PYTHON2 (public function)
#   _proto_srcs = Variable to define with autogenerated Python source files
#   ARGN = proto files
function (PROTOBUF_GENERATE_PYTHON2 _proto_srcs)
  if (NOT ARGN)
    message (SEND_ERROR
	  "Error: PROTOBUF_GENERATE_PYTHON2() called without any proto files")
    return()
  endif (NOT ARGN)

  if (PROTOBUF_GENERATE_CPP_APPEND_PATH)
    # Create an include path for each file specified
    foreach (FIL ${ARGN})
      get_filename_component (ABS_FIL ${FIL} ABSOLUTE)
      get_filename_component (ABS_PATH ${ABS_FIL} PATH)
      list (FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if (${_contains_already} EQUAL -1)
        list (APPEND _protobuf_include_path -I ${ABS_PATH})
      endif (${_contains_already} EQUAL -1)
    endforeach (FIL ${ARGN})
  else (PROTOBUF_GENERATE_CPP_APPEND_PATH)
    set (_protobuf_include_path -I ${CMAKE_CURRENT_SOURCE_DIR})
  endif (PROTOBUF_GENERATE_CPP_APPEND_PATH)

  if (DEFINED PROTOBUF_IMPORT_DIRS)
    foreach (DIR ${PROTOBUF_IMPORT_DIRS})
      get_filename_component (ABS_PATH ${DIR} ABSOLUTE)
      list (FIND _protobuf_include_path ${ABS_PATH} _contains_already)
      if (${_contains_already} EQUAL -1)
          list (APPEND _protobuf_include_path -I ${ABS_PATH})
      endif (${_contains_already} EQUAL -1)
    endforeach (DIR ${PROTOBUF_IMPORT_DIRS})
  endif (DEFINED PROTOBUF_IMPORT_DIRS)

  set (${_proto_srcs})
  foreach (FIL ${ARGN})
    # Extract the file-path and the extension of the Protobuf specification file
    get_filename_component (ABS_FIL ${FIL} ABSOLUTE)
    get_filename_component (FIL_WE ${FIL} NAME_WE)

    # With Python, Protobuf adds "_pb2"
    set (_proto_gen_src ${FIL_WE}_pb2.py)

    message (STATUS
      "Adding ${CMAKE_CURRENT_BINARY_DIR}/${_proto_gen_src} to Python sources")

    list (APPEND ${_proto_srcs} "${CMAKE_CURRENT_BINARY_DIR}/${_proto_gen_src}")

    # Add a specific command for the Protobuf stub/skeleton generation
    add_custom_command (OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${_proto_gen_src}"
      COMMAND  ${PROTOBUF_PROTOC_EXECUTABLE}
      --python_out ${CMAKE_CURRENT_BINARY_DIR} ${_protobuf_include_path} ${ABS_FIL}
      DEPENDS ${ABS_FIL} ${PROTOBUF_PROTOC_EXECUTABLE}
      COMMENT "Running Python protocol buffer compiler on ${FIL}, generating ${CMAKE_CURRENT_BINARY_DIR}/${_proto_gen_src}"
      VERBATIM)
  endforeach (FIL ${ARGN})

  set_source_files_properties (${${_proto_srcs}} PROPERTIES GENERATED TRUE)
  set (${_proto_srcs} ${${_proto_srcs}} PARENT_SCOPE)
endfunction (PROTOBUF_GENERATE_PYTHON2)

##
# Internal function: search for normal library as well as a debug one
#    if the debug one is specified also include debug/optimized keywords
#    in *_LIBRARIES variable
function(_protobuf_find_libraries name filename)
  find_library(${name}_LIBRARY
    NAMES ${filename}
    PATHS ${PROTOBUF_SRC_ROOT_FOLDER}/vsprojects/Release)
  mark_as_advanced(${name}_LIBRARY)

  find_library(${name}_LIBRARY_DEBUG
    NAMES ${filename}
    PATHS ${PROTOBUF_SRC_ROOT_FOLDER}/vsprojects/Debug)
  mark_as_advanced(${name}_LIBRARY_DEBUG)

  if(NOT ${name}_LIBRARY_DEBUG)
    # There is no debug library
    set(${name}_LIBRARY_DEBUG ${${name}_LIBRARY} PARENT_SCOPE)
    set(${name}_LIBRARIES     ${${name}_LIBRARY} PARENT_SCOPE)
  else()
    # There IS a debug library
    set(${name}_LIBRARIES
      optimized ${${name}_LIBRARY}
      debug     ${${name}_LIBRARY_DEBUG}
      PARENT_SCOPE
      )
  endif()
endfunction()

# ~~~~~~~~~~ Protobuf ~~~~~~~~~
macro (get_protobuf)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires Protobuf-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires Protobuf without specifying any version")
  endif (${ARGC} GREATER 0)

  set (PROTOBUF_FOUND False)

  find_package (Protobuf ${_required_version} REQUIRED)
  if (PROTOBUF_LIBRARY)
    set (PROTOBUF_FOUND True)
  endif (PROTOBUF_LIBRARY)

  if (PROTOBUF_FOUND)
    # Update the list of include directories for the project
    include_directories (${PROTOBUF_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${PROTOBUF_LIBRARIES})
  endif (PROTOBUF_FOUND)

endmacro (get_protobuf)

# ~~~~~~~~~~ Xapian ~~~~~~~~~
macro (get_xapian)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires Xapian-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires Xapian without specifying any version")
  endif (${ARGC} GREATER 0)

  # The first check is to get Xapian installation details
  if (${CMAKE_VERSION} VERSION_LESS 2.8.0)
	set (Xapian_DIR /usr/${LIBDIR}/cmake/xapian)
  endif (${CMAKE_VERSION} VERSION_LESS 2.8.0)
  find_package (Xapian)

  # The second check is for the required version (FindXapianWrapper.cmake is
  # provided by us). Indeed, the Fedora/RedHat xapian-config.cmake does not seem
  # to provide version enforcement.
  find_package (XapianWrapper ${_required_version} REQUIRED)

  if (XAPIAN_FOUND)
    # Update the list of include directories for the project
    include_directories (${XAPIAN_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${XAPIAN_LIBRARIES})
  endif (XAPIAN_FOUND)

endmacro (get_xapian)

# ~~~~~~~~~~ Readline ~~~~~~~~~
macro (get_readline)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires Readline-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires Readline without specifying any version")
  endif (${ARGC} GREATER 0)

  set (READLINE_FOUND False)

  find_package (Readline ${_required_version} REQUIRED)
  if (READLINE_LIBRARY)
    set (READLINE_FOUND True)
  endif (READLINE_LIBRARY)

  if (READLINE_FOUND)
    # Update the list of include directories for the project
    include_directories (${READLINE_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${READLINE_LIBRARY})
  endif (READLINE_FOUND)

endmacro (get_readline)

# ~~~~~~~~~~ (N)Curses ~~~~~~~~~
macro (get_curses)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires (N)Curses-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires (N)Curses without specifying any version")
  endif (${ARGC} GREATER 0)

  set (CURSES_FOUND False)

  set (CURSES_NEED_NCURSES True)
  find_package (Curses ${_required_version} REQUIRED)
  if (CURSES_LIBRARY)
    set (CURSES_FOUND True)
  endif (CURSES_LIBRARY)

  if (CURSES_FOUND)
    # Update the list of include directories for the project
    include_directories (${CURSES_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${CURSES_LIBRARY})
  endif (CURSES_FOUND)

endmacro (get_curses)

# ~~~~~~~~~~ SQLite3 ~~~~~~~~~
macro (get_sqlite)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires SQLite3-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires SQLite3 without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (SQLite3 ${_required_version} REQUIRED)
  if (SQLITE3_FOUND)

    # Update the list of include directories for the project
    include_directories (${SQLITE3_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${SQLITE3_LIBRARIES})
  endif (SQLITE3_FOUND)

endmacro (get_sqlite)

# ~~~~~~~~~~ MySQL ~~~~~~~~~
macro (get_mysql)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires MySQL-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires MySQL without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (MySQL ${_required_version} REQUIRED)
  if (MYSQL_FOUND)

    # Update the list of include directories for the project
    include_directories (${MYSQL_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${MYSQL_LIBRARIES})
  endif (MYSQL_FOUND)

endmacro (get_mysql)

# ~~~~~~~~~~ OpenTravelData (OPTD) ~~~~~~~~~
macro (get_optd)
  set (__optd_por_file optd_por_public_all.csv)
  
  find_path (OPTD_POR_DIR
    NAMES "opentraveldata/share/opentraveldata/data/por/${__optd_por_file}"
    PATHS "${WITH_OPENTRAVELDATA_PREFIX}"
    DOC "Full path to the OpenTravelData (OPTD) file")
  
  if (OPTD_POR_DIR-NOTFOUND)
    set (ERROR_MSG "The OPTD POR data dir cannot be found. If OPTD is")
    set (ERROR_MSG "${ERROR_MSG} in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_OPENTRAVELDATA_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<OPTD install path> variable.")
    message (STATUS "${ERROR_MSG}")
    #message (FATAL_ERROR "${ERROR_MSG}")
  else (OPTD_POR_DIR-NOTFOUND)
    #
    message (STATUS "Found OPTD POR data dir: ${OPTD_POR_DIR}")
  endif (OPTD_POR_DIR-NOTFOUND)

endmacro (get_optd)

# ~~~~~~~~~~ SOCI ~~~~~~~~~~
macro (get_soci)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires SOCI-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires SOCI without specifying any version")
  endif (${ARGC} GREATER 0)

  # SOCI core
  find_package (SOCI ${_required_version} REQUIRED)
  if (SOCI_FOUND)
    #
    message (STATUS "Found SOCI with version: ${SOCI_HUMAN_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SOCI_INCLUDE_DIR})
  endif (SOCI_FOUND)

  # SOCI MySQL
  find_package (SOCIMySQL ${_required_version} REQUIRED)
  if (SOCIMYSQL_FOUND)
    #
    message (STATUS "Found SOCI with MySQL back-end support version:"
	  " ${SOCI_HUMAN_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SOCIMYSQL_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES})
  endif (SOCIMYSQL_FOUND)

  # SOCI SQLite
  find_package (SOCISQLite ${_required_version} REQUIRED)
  if (SOCISQLITE_FOUND)
    #
    message (STATUS "Found SOCI with SQLite back-end support version:"
	  " ${SOCI_HUMAN_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SOCISQLITE_INCLUDE_DIR})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${SOCI_LIBRARIES} ${SOCISQLITE_LIBRARIES})
  endif (SOCISQLITE_FOUND)

endmacro (get_soci)

# ~~~~~~~~~~ Doxygen ~~~~~~~~~
macro (get_doxygen)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires Doxygen-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires Doxygen without specifying any version")
  endif (${ARGC} GREATER 0)

  # The first check is to get Doxygen installation details
  find_package (Doxygen)

  # The second check is for the required version (FindDoxygenWrapper.cmake is
  # provided by us). Indeed, the Fedora/RedHat FindDoxygen.cmake does not seem
  # to provide version enforcement.
  find_package (DoxygenWrapper ${_required_version} REQUIRED)

endmacro (get_doxygen)

# ~~~~~~~~~~ StdAir ~~~~~~~~~
macro (get_stdair)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires StdAir-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires StdAir without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (StdAir ${_required_version} REQUIRED
	HINTS ${WITH_STDAIR_PREFIX})
  if (StdAir_FOUND)
    #
    message (STATUS "Found StdAir version: ${STDAIR_VERSION}")

    # Update the list of include directories for the project
    include_directories (${STDAIR_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${STDAIR_LIBRARIES})

  else (StdAir_FOUND)
    set (ERROR_MSG "The StdAir library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_STDAIR_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<StdAir install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (StdAir_FOUND)

endmacro (get_stdair)

# ~~~~~~~~~~ SEvMgr ~~~~~~~~~
macro (get_sevmgr)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires SEvMgr-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires SEvMgr without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (SEvMgr ${_required_version} REQUIRED
	HINTS ${WITH_SEVMGR_PREFIX})
  if (SEvMgr_FOUND)
    #
    message (STATUS "Found SEvMgr version: ${SEVMGR_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SEVMGR_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${SEVMGR_LIBRARIES})

  else (SEvMgr_FOUND)
    set (ERROR_MSG "The SEvMgr library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_SEVMGR_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<SEvMgr install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (SEvMgr_FOUND)

endmacro (get_sevmgr)

# ~~~~~~~~~~ TraDemGen ~~~~~~~~~
macro (get_trademgen)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires TraDemGen-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires TraDemGen without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (TraDemGen ${_required_version} REQUIRED
	HINTS ${WITH_TRADEMGEN_PREFIX})
  if (TraDemGen_FOUND)
    #
    message (STATUS "Found TraDemGen version: ${TRADEMGEN_VERSION}")

    # Update the list of include directories for the project
    include_directories (${TRADEMGEN_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${TRADEMGEN_LIBRARIES})

  else (TraDemGen_FOUND)
    set (ERROR_MSG "The TraDemGen library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_TRADEMGEN_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<TraDemGen install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (TraDemGen_FOUND)

endmacro (get_trademgen)

# ~~~~~~~~~~ TravelCCM ~~~~~~~~~
macro (get_travelccm)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires TravelCCM-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires TravelCCM without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (TravelCCM ${_required_version} REQUIRED
	HINTS ${WITH_TRAVELCCM_PREFIX})
  if (TravelCCM_FOUND)
    #
    message (STATUS "Found TravelCCM version: ${TRAVELCCM_VERSION}")

    # Update the list of include directories for the project
    include_directories (${TRAVELCCM_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${TRAVELCCM_LIBRARIES})

  else (TravelCCM_FOUND)
    set (ERROR_MSG "The TravelCCM library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_TRAVELCCM_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<TravelCCM install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (TravelCCM_FOUND)

endmacro (get_travelccm)

# ~~~~~~~~~~ AirTSP ~~~~~~~~~
macro (get_airtsp)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires AirTSP-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires AirTSP without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (AirTSP ${_required_version} REQUIRED
	HINTS ${WITH_AIRTSP_PREFIX})
  if (AirTSP_FOUND)
    #
    message (STATUS "Found AirTSP version: ${AIRTSP_VERSION}")

    # Update the list of include directories for the project
    include_directories (${AIRTSP_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${AIRTSP_LIBRARIES})

  else (AirTSP_FOUND)
    set (ERROR_MSG "The AirTSP library cannot be found. If it is installed")
    set (ERROR_MSG "${ERROR_MSG} in a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_AIRTSP_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<AirTSP install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (AirTSP_FOUND)

endmacro (get_airtsp)

# ~~~~~~~~~~ AirRAC ~~~~~~~~~
macro (get_airrac)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires AirRAC-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires AirRAC without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (AirRAC ${_required_version} REQUIRED
	HINTS ${WITH_AIRRAC_PREFIX})
  if (AirRAC_FOUND)
    #
    message (STATUS "Found AirRAC version: ${AIRRAC_VERSION}")

    # Update the list of include directories for the project
    include_directories (${AIRRAC_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${AIRRAC_LIBRARIES})

  else (AirRAC_FOUND)
    set (ERROR_MSG "The AirRAC library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_AIRRAC_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<AirRAC install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (AirRAC_FOUND)

endmacro (get_airrac)

# ~~~~~~~~~~ RMOL ~~~~~~~~~
macro (get_rmol)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires RMOL-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires RMOL without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (RMOL ${_required_version} REQUIRED
	HINTS ${WITH_RMOL_PREFIX})
  if (RMOL_FOUND)
    #
    message (STATUS "Found RMOL version: ${RMOL_VERSION}")

    # Update the list of include directories for the project
    include_directories (${RMOL_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${RMOL_LIBRARIES})

  else (RMOL_FOUND)
    set (ERROR_MSG "The RMOL library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_RMOL_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<RMOL install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (RMOL_FOUND)

endmacro (get_rmol)

# ~~~~~~~~~~ AirInv ~~~~~~~~~
macro (get_airinv)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires AirInv-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires AirInv without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (AirInv ${_required_version} REQUIRED
	HINTS ${WITH_AIRINV_PREFIX})
  if (AirInv_FOUND)
    #
    message (STATUS "Found AirInv version: ${AIRINV_VERSION}")

    # Update the list of include directories for the project
    include_directories (${AIRINV_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${AIRINV_LIBRARIES})

  else (AirInv_FOUND)
    set (ERROR_MSG "The AirInv library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_AIRINV_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<AirInv install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (AirInv_FOUND)

endmacro (get_airinv)

# ~~~~~~~~~~ AvlCal ~~~~~~~~~
macro (get_avlcal)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires AvlCal-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires AvlCal without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (AvlCal ${_required_version} REQUIRED
	HINTS ${WITH_AVLCAL_PREFIX})
  if (AvlCal_FOUND)
    #
    message (STATUS "Found AvlCal version: ${AVLCAL_VERSION}")

    # Update the list of include directories for the project
    include_directories (${AVLCAL_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${AVLCAL_LIBRARIES})

  else (AvlCal_FOUND)
    set (ERROR_MSG "The AvlCal library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_AVLCAL_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<AvlCal install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (AvlCal_FOUND)

endmacro (get_avlcal)

# ~~~~~~~~~~ SimFQT ~~~~~~~~~
macro (get_simfqt)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires SimFQT-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires SimFQT without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (SimFQT ${_required_version} REQUIRED
	HINTS ${WITH_SIMFQT_PREFIX})
  if (SimFQT_FOUND)
    #
    message (STATUS "Found SimFQT version: ${SIMFQT_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SIMFQT_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${SIMFQT_LIBRARIES})

  else (SimFQT_FOUND)
    set (ERROR_MSG "The SimFQT library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_SIMFQT_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<SimFQT install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (SimFQT_FOUND)

endmacro (get_simfqt)

# ~~~~~~~~~~ SimLFS ~~~~~~~~~
macro (get_simlfs)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires SimLFS-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires SimLFS without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (SimLFS ${_required_version} REQUIRED
	HINTS ${WITH_SIMLFS_PREFIX})
  if (SimLFS_FOUND)
    #
    message (STATUS "Found SimLFS version: ${SIMLFS_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SIMLFS_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${SIMLFS_LIBRARIES})

  else (SimLFS_FOUND)
    set (ERROR_MSG "The SimLFS library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_SIMLFS_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<SimLFS install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (SimLFS_FOUND)

endmacro (get_simlfs)

# ~~~~~~~~~~ SimCRS ~~~~~~~~~
macro (get_simcrs)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires SimCRS-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires SimCRS without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (SimCRS ${_required_version} REQUIRED
	HINTS ${WITH_SIMCRS_PREFIX})
  if (SimCRS_FOUND)
    #
    message (STATUS "Found SimCRS version: ${SIMCRS_VERSION}")

    # Update the list of include directories for the project
    include_directories (${SIMCRS_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${SIMCRS_LIBRARIES})

  else (SimCRS_FOUND)
    set (ERROR_MSG "The SimCRS library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_SIMCRS_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<SimCRS install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (SimCRS_FOUND)

endmacro (get_simcrs)

# ~~~~~~~~~~ TvlSim ~~~~~~~~~
macro (get_tvlsim)
  unset (_required_version)
  if (${ARGC} GREATER 0)
    set (_required_version ${ARGV0})
    message (STATUS "Requires TvlSim-${_required_version}")
  else (${ARGC} GREATER 0)
    message (STATUS "Requires TvlSim without specifying any version")
  endif (${ARGC} GREATER 0)

  find_package (TvlSim ${_required_version} REQUIRED
	HINTS ${WITH_TVLSIM_PREFIX})
  if (TvlSim_FOUND)
    #
    message (STATUS "Found TvlSim version: ${TVLSIM_VERSION}")

    # Update the list of include directories for the project
    include_directories (${TVLSIM_INCLUDE_DIRS})

    # Update the list of dependencies for the project
    list (APPEND PROJ_DEP_LIBS_FOR_LIB ${TVLSIM_LIBRARIES})

  else (TvlSim_FOUND)
    set (ERROR_MSG "The TvlSim library cannot be found. If it is installed in")
    set (ERROR_MSG "${ERROR_MSG} a in a non standard directory, just invoke")
    set (ERROR_MSG "${ERROR_MSG} 'cmake' specifying the -DWITH_TVLSIM_PREFIX=")
    set (ERROR_MSG "${ERROR_MSG}<TvlSim install path> variable.")
    message (FATAL_ERROR "${ERROR_MSG}")
  endif (TvlSim_FOUND)

endmacro (get_tvlsim)


##############################################
##           Build, Install, Export         ##
##############################################
macro (init_build)
  ##
  # Compilation
  # Note:
  #  * The debug flag (-g) is set (or not) by giving the corresponding option
  #    when calling cmake:
  #    cmake -DCMAKE_BUILD_TYPE:STRING={Debug,Release,MinSizeRel,RelWithDebInfo}
  #  * The CMAKE_CXX_FLAGS is set by CMake to be equal to the CXXFLAGS 
  #    environment variable. Hence:
  #    CXXFLAGS="-O2"; export CXXFLAGS; cmake ..
  #    will set CMAKE_CXX_FLAGS as being equal to -O2.
  if (NOT CMAKE_CXX_FLAGS)
	#set (CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -Werror")
    if (${RUN_GCOV} STREQUAL "ON")
	  set (CMAKE_CXX_FLAGS "-Wall -Werror -fprofile-arcs -ftest-coverage")
    else (${RUN_GCOV} STREQUAL "ON")
      set (CMAKE_CXX_FLAGS "-Wall -Werror")
	endif (${RUN_GCOV} STREQUAL "ON")
  endif (NOT CMAKE_CXX_FLAGS)
  # Tell the source code the version of Boost (only once)
  if (NOT "${CMAKE_CXX_FLAGS}" MATCHES "-DBOOST_VERSION=")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_VERSION=${Boost_VERSION}")
  endif (NOT "${CMAKE_CXX_FLAGS}" MATCHES "-DBOOST_VERSION=")
  if (NOT "${CMAKE_CXX_FLAGS}" MATCHES "-DBOOST_VERSION_MACRO=")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBOOST_VERSION_MACRO=${Boost_VERSION_MACRO}")
  endif (NOT "${CMAKE_CXX_FLAGS}" MATCHES "-DBOOST_VERSION_MACRO=")

  #
  include_directories (BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR})
  
  ##
  # Set all the directory installation paths for the project (e.g., prefix,
  # libdir, bindir).
  # Note that those paths need to be set before the sub-directories are browsed
  # for the building process (see below), because that latter needs those paths
  # to be correctly set.
  set_install_directories ()

  ##
  # Initialise the list of modules to build and test suites to check
  set (PROJ_ALL_MOD_FOR_BLD "")
  set (PROJ_ALL_SUITES_FOR_TST "")

  ##
  # Initialise the list of targets to build: libraries, binaries and tests
  set (PROJ_ALL_LIB_TARGETS "")
  set (PROJ_ALL_BIN_TARGETS "")
  set (PROJ_ALL_TST_TARGETS "")

endmacro (init_build)

# Define the substitutes for the variables present in the development
# support files.
# Note that STDAIR_SAMPLE_DIR is either defined because the current project
# is StdAir, or because the current project has a dependency on StdAir, 
# in which case STDAIR_SAMPLE_DIR is an imported variable.
macro (set_install_directories)
  set (prefix        ${CMAKE_INSTALL_PREFIX})
  set (exec_prefix   ${prefix})
  set (bindir        ${exec_prefix}/bin)
  set (libdir        ${exec_prefix}/${LIBDIR})
  set (pylibdir	     ${libdir}/python${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}/site-packages/py${PACKAGE})
  set (libexecdir    ${exec_prefix}/libexec)
  set (sbindir       ${exec_prefix}/sbin)
  set (sysconfdir    ${prefix}/etc)
  set (includedir    ${prefix}/include)
  set (datarootdir   ${prefix}/share)
  set (datadir       ${datarootdir})
  set (pkgdatadir    ${datarootdir}/${PACKAGE})
  set (sampledir     ${STDAIR_SAMPLE_DIR})
  set (docdir        ${datarootdir}/doc/${PACKAGE}-${PACKAGE_VERSION})
  set (htmldir       ${docdir}/html)
  set (pdfdir        ${htmldir})
  set (mandir        ${datarootdir}/man)
  set (infodir       ${datarootdir}/info)
  set (pkgincludedir ${includedir}/${PACKAGE})
  set (pkglibdir     ${libdir}/${PACKAGE})
  set (pkglibexecdir ${libexecdir}/${PACKAGE})
endmacro (set_install_directories)


####
## Module support
####

##
# Set the name of the module
macro (module_set_name _module_name)
  set (MODULE_NAME ${_module_name})
  set (MODULE_LIB_TARGET ${MODULE_NAME}lib)
endmacro (module_set_name)

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
  set (PY_LIB_DEPENDENCY_EXPORT ${PROJECT_NAME}-python-library-depends)
  set (LIB_DEPENDENCY_EXPORT_PATH "${INSTALL_DATA_DIR}/${PROJECT_NAME}/CMake")
  #
  foreach (_embedded_comp ${_embedded_components})
    #
    add_subdirectory (${_embedded_comp})
  endforeach (_embedded_comp)

  # Register, for book-keeping purpose, the list of modules at the project level
  set (PROJ_ALL_MOD_FOR_BLD ${_embedded_components})

endmacro (add_modules)

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
  set (PROJ_PATH_CFG_DIR ${CMAKE_CURRENT_BINARY_DIR}/config)
  if (EXISTS ${PROJ_PATH_CFG_SRC})
    set (PROJ_PATH_CFG ${PROJ_PATH_CFG_DIR}/${MODULE_NAME}-paths.hpp)
    configure_file (${PROJ_PATH_CFG_SRC} ${PROJ_PATH_CFG} @ONLY)

    # Add the 'hdr_cfg_${MODULE_NAME}' target, depending on the converted header
    add_custom_target (hdr_cfg_${MODULE_NAME} ALL DEPENDS ${PROJ_PATH_CFG})

  else (EXISTS ${PROJ_PATH_CFG_SRC})
    message (FATAL_ERROR "The ${PROJ_PATH_CFG_SRC} file is missing.")
  endif (EXISTS ${PROJ_PATH_CFG_SRC})

endmacro (module_generate_config_helpers)

##
# Detect and generate Protobuf-related stubs
macro (layer_generate_protobuf _protobuf_dir)

  # Detect the presence of Protobuf specification files
  file (GLOB _pb_interface_list
	RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${_protobuf_dir}*.proto)

  # Generate the Protobuf stubs/skeletons for every Protobuf specification
  # file detected
  foreach (_proto_file ${_pb_interface_list})
	# Build the C++ stubs/skeletons
	PROTOBUF_GENERATE_CPP (PROTO_CPP_SRCS PROTO_CPP_HDRS ${_proto_file})
	# Build the Python helper
	# Deprecated? PROTOBUF_GENERATE_PYTHON (PROTO_PY_SRCS python ${_proto_file})
	PROTOBUF_GENERATE_PYTHON (PROTO_PY_SRCS ${_proto_file})

	# Specify the source file, which is by convention (here) made of the name
	# of the Protobuf interface file suffixed by .hpp/.cpp
	list (APPEND ${MODULE_LIB_TARGET}_HEADERS ${PROTO_CPP_HDRS})
	list (APPEND ${MODULE_LIB_TARGET}_SOURCES ${PROTO_CPP_SRCS})
	list (APPEND ${MODULE_LIB_TARGET}_PY_SRCS ${PROTO_PY_SRCS})

  endforeach (_proto_file ${_pb_interface_list})

endmacro (layer_generate_protobuf)

##
# Building and installation of the "standard library".
# All the sources within each of the layers/sub-directories are used and
# assembled, in order to form a single library, named here the
# "standard library".
# The three parameters (among which only the first one is mandatory) are:
#  * A semi-colon separated list of all the layers in which header and source
#    files are to be found.
#  * Whether or not all the header files should be published. By default, only
#    the header files of the root directory are to be published.
#  * A list of additional dependency on inter-module library targets.
macro (module_library_add_standard _layer_list)
  # First, generate the configuration helper header files
  module_generate_config_helpers ()

  # ${ARGV} contains a single semi-colon (';') separated list, which
  # is the aggregation of all the elements of all the list parameters.
  # The list of intermodule dependencies must therefore be calculated.
  set (_intermodule_dependencies ${ARGV})

  # Extract the information whether or not all the header files need
  # to be published. Not that that parameter is optional. Its existence
  # has therefore to be checked.
  set (_publish_all_headers_flag False)
  if (${ARGC} GREATER 1)
    string (TOLOWER ${ARGV1} _flag_lower)
    if ("${_flag_lower}" STREQUAL "all")
      set (_publish_all_headers_flag True)
      list (REMOVE_ITEM _intermodule_dependencies ${ARGV1})
    endif ("${_flag_lower}" STREQUAL "all")
  endif (${ARGC} GREATER 1)

  # Initialise the list of header files with the configuration helper header.
  set (${MODULE_LIB_TARGET}_HEADERS ${PROJ_PATH_CFG})

  # Collect the header and source files for all the layers, as specified 
  # as input paramters of this macro
  set (_all_layers ${_layer_list})
  foreach (_layer ${_all_layers})
    # Remove the layer from the list of intermodule dependencies, so that that
    # latter contains only intermodule dependencies at the end. Note that that
    # latter list may be empty at the end (which then means that there is no
    # dependency among modules).
    list (REMOVE_ITEM _intermodule_dependencies ${_layer})

    # Derive the name of the layer. By default, the layer name corresponds
    # to the layer sub-directory. For the root layer (current source directory),
    # though, the layer name is 'root', rather than '.'
    set (_layer_name ${_layer})
    if ("${_layer_name}" STREQUAL ".")
      set (_layer_name root)
    endif ("${_layer_name}" STREQUAL ".")

    # Derive the name of the layer directory. By default, the layer directory
    # name corresponds to the layer sub-directory. For the root layer (current
    # source directory), though, the layer directory name is empty (""),
    # rather than './'
    set (_layer_dir_name "${_layer}/")
    if ("${_layer_dir_name}" STREQUAL "./")
      set (_layer_dir_name "")
    endif ("${_layer_dir_name}" STREQUAL "./")

	# Generate the Protobuf stubs/skeletons for that layer
	layer_generate_protobuf ("${_layer_dir_name}")

	#
    file (GLOB ${MODULE_LIB_TARGET}_${_layer_name}_HEADERS 
      RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${_layer_dir_name}*.hpp)
    list (APPEND ${MODULE_LIB_TARGET}_HEADERS
      ${${MODULE_LIB_TARGET}_${_layer_name}_HEADERS})

    file (GLOB ${MODULE_LIB_TARGET}_${_layer_name}_SOURCES 
      RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} ${_layer_dir_name}*.cpp)
    list (APPEND ${MODULE_LIB_TARGET}_SOURCES 
      ${${MODULE_LIB_TARGET}_${_layer_name}_SOURCES})
  endforeach (_layer)

  # Register, for book-keeping purpose, the list of layers at the module level
  set (${MODULE_NAME}_ALL_LAYERS ${_all_layers} PARENT_SCOPE)
  set (${MODULE_NAME}_ALL_LAYERS ${_all_layers})

  # Gather both the header and source files into a single list
  set (${MODULE_LIB_TARGET}_SOURCES
    ${${MODULE_LIB_TARGET}_HEADERS} ${${MODULE_LIB_TARGET}_SOURCES})

  ##
  # Building of the library.
  # Delegate the (CMake) target registration to a dedicated macro (below)
  module_library_add_specific (${MODULE_NAME} "."
    "${${MODULE_LIB_TARGET}_root_HEADERS}" "${${MODULE_LIB_TARGET}_SOURCES}" 
    ${_intermodule_dependencies})

  # If so required, installation of all the remaining header files 
  # for the module, i.e., the header files located in all the layers
  # except the root.
  if (_publish_all_headers_flag)
    module_header_install_everything_else()
  endif (_publish_all_headers_flag)

  # Convenient message to the user/developer
  if (NOT CMAKE_INSTALL_RPATH_USE_LINK_PATH)
    install (CODE "message (\"On Unix-based platforms, run export LD_LIBRARY_PATH=${INSTALL_LIB_DIR}:${INSTALL_PY_LIB_DIR}:\$LD_LIBRARY_PATH once per session\")")
  endif (NOT CMAKE_INSTALL_RPATH_USE_LINK_PATH)

endmacro (module_library_add_standard)

##
# Building and installation of a specific library.
# The first four parameters are mandatory and correspond to:
#  * The short name of the library to be built.
#    Note that the library (CMake) target is derived directly from the library
#    short name: a 'lib' suffix is just appended to the short name.
#  * The directory where to find the header files.
#  * The header files to be published/installed along with the library.
#    If there are no header to be exported, the 'na' keyword (standing for
#    'non available') must be given.
#  * The source files to build the library.
#    Note that the source files contain at least the header files. Hence,
#    even when there are no .cpp source files, the .hpp files will appear.
#
# Note that the header and source files should be given as single parameters,
# i.e., enclosed by double quotes (").
#
# The additional parameters, if given, correspond to the names of the
# modules this current module depends upon. Dependencies on the
# external libraries (e.g., Boost, SOCI, StdAir) are automatically
# appended, thanks to the get_external_libs() macro.
macro (module_library_add_specific
    _lib_short_name _lib_dir _lib_headers _lib_sources)
  # Derive the library (CMake) target from its name
  set (_lib_target ${_lib_short_name}lib)

  string (SUBSTRING ${_lib_short_name} 0 2 _lib_prefix)

  # Register the (CMake) target for the library
  add_library (${_lib_target} SHARED ${_lib_sources})

  # For each module, given as parameter of that macro, add the corresponding
  # library target to a dedicated list
  set (_intermodule_dependencies "")
  foreach (_arg_module ${ARGV})
    if (NOT "${_lib_dir};${_lib_short_name};${_lib_headers};${_lib_sources}" 
		MATCHES "${_arg_module}")
      list (APPEND _intermodule_dependencies ${_arg_module}lib)
    endif ()
  endforeach (_arg_module)
  #
  if (NOT "${_lib_short_name}" STREQUAL "${MODULE_NAME}")
	set (_intramodule_dependencies ${MODULE_NAME}lib)
  endif (NOT "${_lib_short_name}" STREQUAL "${MODULE_NAME}")

  # Add the dependencies:
  #  * on external libraries (Boost, MySQL, SOCI, StdAir), as calculated by 
  #    the get_external_libs() macro above;
  #  * on the other module libraries, as provided as paramaters to this macro
  #  * on the main/standard library of the module (when, of course, the
  #    current library is not the main/standard library).
  target_link_libraries (${_lib_target} ${PROJ_DEP_LIBS_FOR_LIB} 
	${_intermodule_dependencies} ${_intramodule_dependencies})

  # Register the library target in the project (for reporting purpose).
  # Note, the list() commands creates a new variable value in the current scope:
  # the set() must therefore be used to propagate the value upwards. And for
  # those wondering whether we could do that operation with a single set()
  # command, I have already tried... unsucessfully(!)
  list (APPEND PROJ_ALL_LIB_TARGETS ${_lib_target})
  set (PROJ_ALL_LIB_TARGETS ${PROJ_ALL_LIB_TARGETS} PARENT_SCOPE)

  # Register the intermodule dependency targets in the project (for
  # reporting purpose).
  set (${MODULE_NAME}_INTER_TARGETS ${_intermodule_dependencies})
  set (${MODULE_NAME}_INTER_TARGETS ${_intermodule_dependencies} PARENT_SCOPE)

  # For the "standard library", an extra dependency must be added:
  #  * generated configuration header
  if (${_lib_short_name} STREQUAL ${MODULE_NAME})
    ##
    # Add the dependency on the generated configuration headers, 
    # as generated by the module_generate_config_helpers() macro
    add_dependencies (${_lib_target} hdr_cfg_${MODULE_NAME})
  endif (${_lib_short_name} STREQUAL ${MODULE_NAME})

  ##
  # Python extension libraries has some peculiarities
  if ("${_lib_prefix}" STREQUAL "py")
    message (STATUS "${_lib_short_name} is assumed to be a Python library:")
    message (STATUS "  -> Following libraries will be weakly linked: ${Python3_LIBRARIES} ${PROJ_DEP_LIBS_FOR_PYEXT}")
	
    # no 'lib' prefix
    set_target_properties (${_lib_target} PROPERTIES PREFIX "")

    # The suffix must be .so (even on MacOS, not .dylib)
    set_target_properties (${_lib_target} PROPERTIES SUFFIX ".so")

    # Add the dependencies for Python extensions.
    #
    # Python extensions (which are also libraries per se) must not be linked
    # against libpython3.x.so (which includes the interpreter). On Linux, it is
    # fine not to link against libpython3.x.so, but on OS X, the compiler
    # fails, unless the -undefined dynamic_lookup option is passed, which is
    # what target_link_libraries_with_dynamic_lookup() is doing. That function
    # is specified in the targetLinkLibrariesWithDynamicLookup.cmake file.
    #
    # See also:
    #  https://blog.tim-smith.us/2015/09/python-extension-modules-os-x/
    #  https://github.com/scikit-build/scikit-build/blob/master/skbuild/resources/cmake/targetLinkLibrariesWithDynamicLookup.cmake
    target_link_libraries_with_dynamic_lookup (${_lib_target}
      ${Python3_LIBRARIES} ${PROJ_DEP_LIBS_FOR_PYEXT})
    #python_extension_module (${_lib_target})
	
  endif ("${_lib_prefix}" STREQUAL "py")

  ##
  # Library name (and soname)
  if (WIN32)
    # MS Windows
    set_target_properties (${_lib_target} PROPERTIES 
      OUTPUT_NAME ${_lib_short_name} 
      VERSION ${GENERIC_LIB_VERSION})

  else (WIN32)
    # Linux and MacOS
    set_target_properties (${_lib_target} PROPERTIES 
      OUTPUT_NAME ${_lib_short_name}
      VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION})
  endif (WIN32)

  # If everything else is not enough for CMake to derive the language
  # to be used by the linker, it must be told to fall-back on C++
  get_target_property (_linker_lang ${_lib_target} LINKER_LANGUAGE)
  if ("${_linker_lang}" STREQUAL "_linker_lang-NOTFOUND")
    set_target_properties (${_lib_target} PROPERTIES LINKER_LANGUAGE CXX)
    message(STATUS "Had to set the linker language for '${_lib_target}' to CXX")
  endif ("${_linker_lang}" STREQUAL "_linker_lang-NOTFOUND")

  ##
  # Installation of the library
  if ("${_lib_prefix}" STREQUAL "py")
    # If the library is Python, install it into a dedicated directory
    message (STATUS "${_lib_short_name} is assumed to be a Python library")
    install (TARGETS ${_lib_target}
      EXPORT ${PY_LIB_DEPENDENCY_EXPORT}
      LIBRARY DESTINATION "${INSTALL_PY_LIB_DIR}" COMPONENT python-runtime)
    
  else ("${_lib_prefix}" STREQUAL "py")
    # Install the library in the standard location
    install (TARGETS ${_lib_target}
      EXPORT ${LIB_DEPENDENCY_EXPORT}
      LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT runtime)
  endif ("${_lib_prefix}" STREQUAL "py")
  
  # Register, for reporting purpose, the list of libraries to be built
  # and installed for that module
  list (APPEND ${MODULE_NAME}_ALL_LIBS ${_lib_target})
  set (${MODULE_NAME}_ALL_LIBS ${${MODULE_NAME}_ALL_LIBS} PARENT_SCOPE)

  # If given/existing, install the header files for the library
  string (TOLOWER "${_lib_headers}" _lib_headers_lower)
  if (NOT "${_lib_headers_lower}" STREQUAL "na")
    module_header_install_specific (${_lib_dir} "${_lib_headers}")
  endif (NOT "${_lib_headers_lower}" STREQUAL "na")

endmacro (module_library_add_specific)

##
# Installation of specific header files
macro (module_header_install_specific _lib_dir _lib_headers)
  #
  set (_relative_destination_lib_dir "/${_lib_dir}")
  if ("${_relative_destination_lib_dir}" STREQUAL "/.")
    set (_relative_destination_lib_dir "")
  endif ("${_relative_destination_lib_dir}" STREQUAL "/.")

  # Install header files
  install (FILES ${_lib_headers}
    DESTINATION 
    "${INSTALL_INCLUDE_DIR}/${MODULE_NAME}${_relative_destination_lib_dir}"
    COMPONENT devel)

  # DEBUG
  #message ("DEBUG -- [${_lib_dir}] _lib_headers = ${_lib_headers}")

endmacro (module_header_install_specific)

##
# Installation of all the remaining header files for the module, i.e.,
# the header files located in all the layers except the root.
macro (module_header_install_everything_else)
  # Add the layer for the generated headers to the list of source layers
  set (_all_layers ${${MODULE_NAME}_ALL_LAYERS} ${PROJ_PATH_CFG_DIR})

  # The header files of the root layer have already been addressed by the
  # module_library_add_standard() macro (which calls, in turn,
  # module_library_add_specific(), which calls, in turn, 
  # module_header_install_specific() on the root header files)

  # It remains to install the header files for all the other layers
  foreach (_layer ${_all_layers})
    # Install header files
    install (FILES ${${MODULE_LIB_TARGET}_${_layer}_HEADERS}
      DESTINATION "${INSTALL_INCLUDE_DIR}/${MODULE_NAME}/${_layer}"
      COMPONENT devel)
  endforeach (_layer ${${MODULE_NAME}_ALL_LAYERS})

endmacro (module_header_install_everything_else)

##
# Building and installation of the executables/binaries.
# The two parameters (among which only the first one is mandatory) are:
#  * The path/directory where the header and source files can be found
#    in order to build the executable.
#  * If specified, the name to be given to the executable. If no such name
#    is given as parameter, the executable is given the name of the current
#    module.
macro (module_binary_add _exec_source_dir)
  # First, derive the name to be given to the executable, defaulting
  # to the name of the module
  set (_exec_name ${MODULE_NAME})
  if (${ARGC} GREATER 1})
    set (_exec_name ${ARGV1})
  endif (${ARGC} GREATER 1})

  # Extract the prefix to differentiate Python binaries
  string (SUBSTRING ${_exec_name} 0 2 _bin_prefix)
  
  # Register the (CMake) target for the executable, and specify the name
  # of that latter
  add_executable (${_exec_name}bin ${_exec_source_dir}/${_exec_name}.cpp)
  set_target_properties (${_exec_name}bin PROPERTIES OUTPUT_NAME ${_exec_name})

  # Register the dependencies on which the binary depends upon
  target_link_libraries (${_exec_name}bin
    ${PROJ_DEP_LIBS_FOR_BIN} ${MODULE_LIB_TARGET} 
    ${${MODULE_NAME}_INTER_TARGETS})

  # Binary installation
  if ("${_bin_prefix}" STREQUAL "py")
	# Python binary
	install (TARGETS ${_exec_name}bin
      EXPORT ${PY_LIB_DEPENDENCY_EXPORT}
      RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT python-runtime)
	
  else ("${_bin_prefix}" STREQUAL "py")
	# Standard binary
	install (TARGETS ${_exec_name}bin
      EXPORT ${LIB_DEPENDENCY_EXPORT}
      RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT runtime)
  endif ("${_bin_prefix}" STREQUAL "py")

  # Register the binary target in the project (for reporting purpose)
  list (APPEND PROJ_ALL_BIN_TARGETS ${_exec_name})
  set (PROJ_ALL_BIN_TARGETS ${PROJ_ALL_BIN_TARGETS} PARENT_SCOPE)

  # Register, for reporting purpose, the list of executables to be built
  # and installed for that module
  list (APPEND ${MODULE_NAME}_ALL_EXECS ${_exec_name})
  set (${MODULE_NAME}_ALL_EXECS ${${MODULE_NAME}_ALL_EXECS} PARENT_SCOPE)

endmacro (module_binary_add)

##
# Installation of the configuration INI file (format cfg).
# The two parameters (among which only the first one is mandatory) are:
#  * The path/directory where the configuration file can be found.
#  * If specified, the name to be given to the file. If no such name
#    is given as parameter, the configuration file is given the name of 
#    the current module.
macro (module_config_add _config_source_dir)
  # First, derive the name to be given to the config file, defaulting
  # to the name of the module
  set (_config_name ${MODULE_NAME})
  if (${ARGC} GREATER 1})
    set (_config_name ${ARGV1})
  endif (${ARGC} GREATER 1})

  # Define the macro path of the configuration file
  set (PROJ_PATH_CFG_SRC ${_config_source_dir}/${_config_name}.cfg)

  # Installation of the cfg file
  install (FILES ${PROJ_PATH_CFG_SRC} 
    DESTINATION "${INSTALL_ETC_DIR}" COMPONENT runtime)

endmacro (module_config_add)

##
# Installation of Python module scripts (e.g., __init__.py)
#
# The parameter is the relative file path of the Python initialiser script
# to be installed. A typical Python module script is __init__.py
# 
macro (python_module_add _python_module_file_path)
  install (FILES ${_python_module_file_path} DESTINATION ${INSTALL_PY_LIB_DIR})
endmacro (python_module_add)

##
# Add a (Shell, Python, Perl, Ruby, etc) script to be installed.
#
# The parameter is the relative file path of the (template) script to
# be installed. That template file must end with the '.in' suffix.
# Indeed, the project variables (wrapped by @@ signs) of the template file
# are evaluated and expanded thanks to the configure command.
# The '.in' extension of the script is dropped once installed.
#
macro (module_script_add _script_file)
  #
  set (_full_script_src_path ${CMAKE_CURRENT_SOURCE_DIR}/${_script_file}.in)
  set (_full_script_path ${CMAKE_CURRENT_BINARY_DIR}/${_script_file})
  if (EXISTS ${_full_script_src_path})
	#
    configure_file (${_full_script_src_path} ${_full_script_path} @ONLY)

	# Extract the file name (only) from the full file path
	get_filename_component (_script_alone ${_script_file} NAME)
    
	# Initialise the list of script sources with the script itself
	set (_full_script_srcs ${_full_script_path})

	# If the script is Python, add a dependency on the Protobuf-related helpers
	string (SUBSTRING ${_script_alone} 0 2 _script_ext)
	if ("${_script_ext}" STREQUAL "py")
	  message (STATUS "${_script_file} is assumed to be a Python script")
	  message (STATUS " => Added dependencies: ${${MODULE_LIB_TARGET}_PY_SRCS}")
      list (APPEND _full_script_srcs ${${MODULE_LIB_TARGET}_PY_SRCS})

      # Install the Python helpers
      install (PROGRAMS ${${MODULE_LIB_TARGET}_PY_SRCS}
		DESTINATION "${INSTALL_PY_LIB_DIR}" COMPONENT python-devel)
	endif ("${_script_ext}" STREQUAL "py")

	# Add the 'scripts_${MODULE_NAME}' target, depending on the
    # converted (Shell, Python, Perl, Ruby, etc) scripts
    add_custom_target (${_script_alone}_script ALL DEPENDS ${_full_script_srcs})

    # Install the (Shell, Python, Perl, Ruby, etc) script file
	if ("${_script_ext}" STREQUAL "py")
	  # The Python scripts have to be installed in the Python
	  # site-package/library dedicated directory
      install (PROGRAMS ${_full_script_path}
		DESTINATION "${INSTALL_PY_LIB_DIR}" COMPONENT python-devel)
	else ("${_script_ext}" STREQUAL "py")
      install (PROGRAMS ${_full_script_path} DESTINATION bin COMPONENT devel)
	endif ("${_script_ext}" STREQUAL "py")

  else (EXISTS ${_full_script_src_path})
    message (FATAL_ERROR
      "The template of the script, '${_script_file}.in', does not exist")
  endif (EXISTS ${_full_script_src_path})

  # Register the binary target in the project (for reporting purpose)
  list (APPEND PROJ_ALL_BIN_TARGETS ${_script_alone})
  set (PROJ_ALL_BIN_TARGETS ${PROJ_ALL_BIN_TARGETS} PARENT_SCOPE)

  # Register, for reporting purpose, the list of executables to be built
  # and installed for that module
  list (APPEND ${MODULE_NAME}_ALL_EXECS ${_script_alone})
  set (${MODULE_NAME}_ALL_EXECS ${${MODULE_NAME}_ALL_EXECS} PARENT_SCOPE)

endmacro (module_script_add)

##
# Installation of the CMake import helper, so that third party projects
# can refer to it (for libraries, header files and binaries)
macro (module_export_install)
  install (EXPORT ${LIB_DEPENDENCY_EXPORT}
    DESTINATION "${INSTALL_DATA_DIR}/${PACKAGE}/CMake" COMPONENT devel)

  if (NEED_PYTHON)
	install (EXPORT ${PY_LIB_DEPENDENCY_EXPORT}
      DESTINATION "${INSTALL_DATA_DIR}/${PACKAGE}/CMake" COMPONENT python-devel)
  endif (NEED_PYTHON)
endmacro (module_export_install)


###################################################################
##                            Tests                              ##
###################################################################
##
# Initialise the CTest framework with CMake, if so enabled
macro (init_test)
  # Register the main test target. Every specific test will then be added
  # as a dependency on that target. When the unit tests are disabled
  # (i.e., the ENABLE_TEST variable is set to OFF), that target remains empty.
  add_custom_target (check)
  
  if (Boost_FOUND AND ENABLE_TEST)
	# Tell CMake/CTest that tests will be performed
	enable_testing() 

  endif (Boost_FOUND AND ENABLE_TEST)
endmacro (init_test)

##
# Register a specific test sub-directory/suite to be checked by CMake/CTest.
# That macro must be called once for each test sub-directory/suite.
# The parameter is:
#  * The test directory path, ommitting the 'test/' prefix. Most often, it is
#    the same as the module name. And when there is a single module (which is
#    the most common case), it corresponds to the project name.
macro (add_test_suite _test_suite_dir)
  if (Boost_FOUND AND ENABLE_TEST)
    # Browse all the modules, and register test suites for each of them
    set (_check_target check_${_test_suite_dir}tst)

    # Each individual test suite is specified within the dedicated
    # sub-directory. The CMake file within each of those test sub-directories
    # specifies a target named check_${_module_name}tst.
    add_subdirectory (test/${_test_suite_dir})

    # Register the test suite (i.e., add the test target as a dependency of
	# the 'check' target).
    add_dependencies (check ${_check_target})

	# Register, for book-keeping purpose (a few lines below), 
	# the (CMake/CTest) test target of the current test suite. When the
	# test directory corresponds to any given module, the test targets will
	# be added to that module dependencies.
	set (${_test_suite_dir}_ALL_TST_TARGETS "")

    # Register, for reporting purpose, the list of test suites to be checked
    list (APPEND PROJ_ALL_SUITES_FOR_TST ${_test_suite_dir})

  endif (Boost_FOUND AND ENABLE_TEST)

endmacro (add_test_suite)

##
# Register a test with CMake/CTest.
# The parameters are:
#  * The name of the test module
#  * The name of the test, which will serve as the name for the test binary.
#  * The list of sources for the test binary. The list must be
#    semi-colon (';') seperated.
#  * A list of intermodule dependencies. That list is separated by
#    either white space or semi-colons (';').
macro (module_test_add_suite _module_name _test_name _test_sources)
  if (Boost_FOUND AND ENABLE_TEST)

	# If the module is already known, the corresponding library is added to
	# the list of dependencies.
	set (MODULE_NAME ${_module_name})
	set (MODULE_LIB_TARGET "")
	foreach (_module_item ${PROJ_ALL_MOD_FOR_BLD})
	  if ("${_module_name}" STREQUAL "${_module_item}")
		set (MODULE_LIB_TARGET ${MODULE_NAME}lib)
	  endif ("${_module_name}" STREQUAL "${_module_item}")
	endforeach (_module_item ${PROJ_ALL_MOD_FOR_BLD})

    # Register the test binary target
    add_executable (${_test_name}tst ${_test_sources})
    set_target_properties (${_test_name}tst PROPERTIES
      OUTPUT_NAME ${_test_name})

    message (STATUS "Test '${_test_name}' to be built with '${_test_sources}'")

    # Build the list of library targets on which that test depends upon
    set (_library_list "")
    foreach (_arg_lib ${ARGV})
      if (NOT "${_module_name};${_test_name};${_test_sources}"
		  MATCHES "${_arg_lib}")
		list (APPEND _library_list ${_arg_lib}lib)
      endif ()
    endforeach (_arg_lib)

    # Tell the test binary that it depends on all those libraries
    target_link_libraries (${_test_name}tst ${_library_list} 
      ${MODULE_LIB_TARGET} ${${MODULE_NAME}_INTER_TARGETS}
	  ${PROJ_DEP_LIBS_FOR_TST})

    # Register the binary target in the module
    list (APPEND ${MODULE_NAME}_ALL_TST_TARGETS ${_test_name}tst)

    # Register the test with CMake/CTest
    if (WIN32)
      add_test (${_test_name}tst ${_test_name}.exe)
    else (WIN32)
      add_test (${_test_name}tst ${_test_name})
    endif (WIN32)
  endif (Boost_FOUND AND ENABLE_TEST)

  # Register the binary target in the project (for reporting purpose)
  list (APPEND PROJ_ALL_TST_TARGETS ${${MODULE_NAME}_ALL_TST_TARGETS})
  set (PROJ_ALL_TST_TARGETS ${PROJ_ALL_TST_TARGETS} PARENT_SCOPE)

  # Register, for reporting purpose, the list of tests to be checked
  # for that module
  list (APPEND ${MODULE_NAME}_ALL_TESTS ${${MODULE_NAME}_ALL_TST_TARGETS})
  set (${MODULE_NAME}_ALL_TESTS ${${MODULE_NAME}_ALL_TESTS} PARENT_SCOPE)

endmacro (module_test_add_suite)

##
# Register all the test binaries for the current module.
# That macro must be called only once per module.
macro (module_test_build_all)
  if (Boost_FOUND)
    # Tell how to test, i.e., how to run the test binaries 
    # and collect the results
    add_custom_target (check_${MODULE_NAME}tst
      COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${${MODULE_NAME}_ALL_TST_TARGETS})
  endif (Boost_FOUND)
endmacro (module_test_build_all)


###################################################################
##                         Documentation                         ##
###################################################################
##
# HTML pages and PDF reference manual
##
#
macro (handle_html_doc)
  if (${INSTALL_DOC} STREQUAL "ON")
	add_subdirectory (doc)
  endif (${INSTALL_DOC} STREQUAL "ON")
endmacro (handle_html_doc)

# Define the substitutes for the variables present in the Doxygen
# configuration files. Note that PACKAGE, PACKAGE_NAME and PACKAGE_VERSION
# are defined in the main CMakeLists.txt (of the top root directory).
macro (doc_set_directories)
  set (OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
  set (top_srcdir ${CMAKE_SOURCE_DIR})
  set (srcdir ${CMAKE_CURRENT_SOURCE_DIR})
endmacro (doc_set_directories)

#
macro (doc_add_web_pages)
  # Set the documentation directories for the Doxygen configuration file
  doc_set_directories()

  # Convert the Doxygen configuration files (basically, just replace
  # the @<variable>@ variables).
  set (DOXYGEN_CFG_SRC doxygen_html.cfg.in)
  set (DOXYGEN_CFG ${CMAKE_CURRENT_BINARY_DIR}/doxygen_html.cfg)
  configure_file (${DOXYGEN_CFG_SRC} ${DOXYGEN_CFG} @ONLY)

  ## Documentation sources
  # (CSS) Style sheets
  set (docstyles_DIR ${CMAKE_CURRENT_SOURCE_DIR}/styles)
  set (style_SOURCES ${CPACK_PACKAGE_NAME}.css)
  set (docstyles_SOURCES ${docstyles_DIR}/${style_SOURCES})
  # Images
  set (docimages_DIR ${CMAKE_CURRENT_SOURCE_DIR}/images)
  set (image_SOURCES ${CPACK_PACKAGE_NAME}_logo.png sfx_logo.png favicon.ico)
  set (docimages_SOURCES "")
  foreach (_doc_img_src ${image_SOURCES})
	list (APPEND docimages_SOURCES ${docimages_DIR}/${_doc_img_src})
  endforeach (_doc_img_src ${image_SOURCES})
  # Tutorial
  FILE (GLOB doctutorial_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tutorial/*.doc)
  # Local
  FILE (GLOB doclocaldoc_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/local/*.doc)
  FILE (GLOB doclocalhtml_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/local/*.html)
  set (doclocal_SOURCES ${doclocaldoc_SOURCES} ${doclocalhtml_SOURCES})
  # Aggregating all the documentation sources
  set (doc_SOURCES ${doctutorial_SOURCES} ${doclocal_SOURCES}
	${docstyles_SOURCES} ${docimages_SOURCES})

  # Latex reference manual source (.tex file), generated by Doxygen
  set (REFMAN refman)
  set (TEX_GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/latex)
  set (REFMAN_TEX ${REFMAN}.tex)
  set (REFMAN_TEX ${REFMAN_TEX} PARENT_SCOPE)
  set (REFMAN_TEX_FULL ${TEX_GEN_DIR}/${REFMAN_TEX})
  set (REFMAN_TEX_OTHERS ${TEX_GEN_DIR}/index.tex ${TEX_GEN_DIR}/namespaces.tex
	${TEX_GEN_DIR}/annotated.tex ${TEX_GEN_DIR}/hierarchy.tex
	${TEX_GEN_DIR}/files.tex)

  # Add the build rule for Doxygen
  set (DOXYGEN_OUTPUT_REL html/index.html)
  set (DOXYGEN_OUTPUT_REL ${DOXYGEN_OUTPUT_REL} PARENT_SCOPE)
  set (DOXYGEN_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${DOXYGEN_OUTPUT_REL})
  set (DOXYGEN_OUTPUT ${DOXYGEN_OUTPUT} PARENT_SCOPE)
  add_custom_command (
	OUTPUT ${DOXYGEN_OUTPUT} ${REFMAN_TEX_FULL} ${REFMAN_TEX_OTHERS}
	COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${DOXYGEN_CFG}
	DEPENDS ${DOXYGEN_CFG} ${doc_SOURCES}
	COMMENT "Generating documentation with Doxygen, from '${DOXYGEN_CFG}'...")
  # Add the 'doc' target, depending on the generated HTML documentation
  add_custom_target (doc ALL DEPENDS
	${DOXYGEN_OUTPUT} ${REFMAN_TEX_FULL} ${REFMAN_TEX_OTHERS})

  ##
  # Copy the needed files into the generated HTML directory
  set (htmldoc_DIR ${CMAKE_CURRENT_BINARY_DIR}/html)
  set (pdfdoc_DIR ${CMAKE_CURRENT_BINARY_DIR}/latex)

  # (CSS) Style sheets
  foreach (style_SRC ${style_SOURCES})
	set (CSS_SRC_FULL_DIR ${docstyles_DIR}/${style_SRC})
	set (CSS_GEN_FULL_DIR ${htmldoc_DIR}/${style_SRC})
	add_custom_command (OUTPUT ${CSS_GEN_FULL_DIR}
	  COMMAND ${CMAKE_COMMAND}
	  ARGS -E copy ${CSS_SRC_FULL_DIR} ${CSS_GEN_FULL_DIR}
	  DEPENDS doc ${CSS_SRC_FULL_DIR}
	  COMMENT "Copying style '${CSS_SRC_FULL_DIR}' into '${htmldoc_DIR}'...")

	# Transpose the CSS-related operation into a target, so that CMake
	# can handle it properly
	add_custom_target (css_${style_SRC} ALL DEPENDS ${CSS_GEN_FULL_DIR})
	list (APPEND CSS_ALL_TARGETS css_${style_SRC})
  endforeach (style_SRC)
  set (CSS_ALL_TARGETS ${CSS_ALL_TARGETS} PARENT_SCOPE)
  add_custom_target (css_style)
  add_dependencies (css_style ${CSS_ALL_TARGETS})

  # Images
  foreach (image_SRC ${image_SOURCES})
	set (IMG_SRC_FULL_DIR ${docimages_DIR}/${image_SRC})
	set (IMG_GEN_FULL_DIR ${htmldoc_DIR}/${image_SRC})
	add_custom_command (OUTPUT ${IMG_GEN_FULL_DIR}
	  COMMAND ${CMAKE_COMMAND} 
	  ARGS -E copy ${IMG_SRC_FULL_DIR} ${IMG_GEN_FULL_DIR}
	  DEPENDS doc ${IMG_SRC_FULL_DIR}
	  COMMENT "Copying image '${IMG_SRC_FULL_DIR}' into '${htmldoc_DIR}'...")

	# Transpose the image-related operation into a target, so that CMake
	# can handle it properly
	add_custom_target (img_${image_SRC} ALL DEPENDS ${IMG_GEN_FULL_DIR})
	list (APPEND IMG_ALL_TARGETS img_${image_SRC})
  endforeach (image_SRC)
  set (IMG_ALL_TARGETS ${IMG_ALL_TARGETS} PARENT_SCOPE)
  add_custom_target (img_style)
  add_dependencies (img_style ${IMG_ALL_TARGETS})

  ##
  # PDF, generated by (Pdf)Latex from the Latex source file, itself generated
  # by Doxygen (see above)
  set (REFMAN_IDX ${REFMAN}.idx)
  set (REFMAN_IDX_FULL ${TEX_GEN_DIR}/${REFMAN_IDX})
  set (REFMAN_PDF ${REFMAN}.pdf)
  set (REFMAN_PDF ${REFMAN_PDF} PARENT_SCOPE)
  set (REFMAN_PDF_FULL ${TEX_GEN_DIR}/${REFMAN_PDF})
  set (WARNING_PDF_MSG "Warning: the PDF reference manual ('${REFMAN_PDF_FULL}') has failed to build. You can perform a simple re-build ('make' in the 'doc/latex' sub-directory).")
  # Note the "|| echo" addition to the pdflatex command, as that latter returns
  # as if there were an error.
  add_custom_command (OUTPUT ${REFMAN_IDX_FULL} ${REFMAN_PDF_FULL}
	COMMAND ${CMAKE_COMMAND}
	ARGS -E chdir ${TEX_GEN_DIR} pdflatex -interaction batchmode ${REFMAN_TEX} && echo 'First PDF generation done.' || echo 'First PDF generation done.'
	COMMAND ${CMAKE_COMMAND}
	ARGS -E chdir ${TEX_GEN_DIR} egrep -s -e 'Fatal error occurred' -e 'Rerun to get cross-references right' refman.log && (cd ${TEX_GEN_DIR} && pdflatex -interaction batchmode ${REFMAN_TEX} && echo 'Second PDF generation done.') || echo 'Second PDF generation was not necessary'
	COMMAND ${CMAKE_COMMAND}
	ARGS -E chdir ${TEX_GEN_DIR} egrep -s -e 'Fatal error occurred' -e 'Rerun to get cross-references right' refman.log && (cd ${TEX_GEN_DIR} && pdflatex -interaction batchmode ${REFMAN_TEX} && echo 'Third PDF generation done.') || echo 'Third PDF generation was not necessary'
	COMMAND ${CMAKE_COMMAND}
	ARGS -E chdir ${TEX_GEN_DIR} test ! -f ${REFMAN_PDF} && (cd ${TEX_GEN_DIR} && echo '${WARNING_PDF_MSG}' > ${REFMAN_PDF} && echo '${WARNING_PDF_MSG}') || echo 'The PDF reference manual has been successfully built'
	COMMAND ${CMAKE_COMMAND}
	ARGS -E chdir ${TEX_GEN_DIR} echo 'The file size of the PDF reference manual is: ' && (cd ${TEX_GEN_DIR} && du -sh ${REFMAN_PDF} | cut -f1)
	DEPENDS doc
	COMMENT "Generating PDF Reference Manual ('${REFMAN_TEX}' => '${REFMAN_PDF}')...")

  # Add the 'pdf' target, depending on the generated PDF manual
  add_custom_target (pdf ALL DEPENDS ${REFMAN_IDX_FULL} ${REFMAN_PDF_FULL})
  add_dependencies (pdf css_style img_style)

  # Clean-up $build/html and $build/latex on 'make clean'
  set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
	${htmldoc_DIR} ${pdfdoc_DIR})

  ##
  # Installation of the HTML documentation
  set (DOC_PATH share/doc/${PROJECT_NAME})
  # HTML pages
  install (DIRECTORY ${htmldoc_DIR} DESTINATION ${DOC_PATH})
  # PDF reference manual
  # Note: the 'OPTIONAL' ensures that even when the PDF file fails to be
  # generated, the install process does not complain. If the PDF build fails,
  # a simple re-build ('make' in the 'doc/latex' sub-directory) is usually 
  # enough.
  install (FILES ${REFMAN_PDF_FULL} DESTINATION ${DOC_PATH}/html OPTIONAL)
endmacro (doc_add_web_pages)

##
# Manual pages
##
macro (doc_add_man_pages)
  # Specify the relative path where the manual pages are to be installed.
  # That path is relative to the installation prefix. By default, the prefix
  # is '/usr', and the manual page installation directory is therefore
  # /usr/share/man
  set (MAN_PATH "share/man")

  # Specify the list of manual sections, e.g.:
  #  * Section 1 (general commands)
  #  * Section 3 (development)
  set (man_section_list "")
  foreach (_idx RANGE 1 9)
    list (APPEND man_section_list ${_idx})
  endforeach (_idx RANGE 1 9)

  # Initialise the lists gathering information for each valid manual section
  set (man_dir_list)

  # Parse the arguments
  set (options)
  set (oneValueArgs)

  # Added one argument option for every manual section
  foreach (man_sect ${man_section_list})
    list (APPEND multiValueArgs MAN${man_sect})
  endforeach (man_sect ${man_section_list})

  # When available, use the convenient dedicated CMake function to parse
  # the options. When not, the options must be parsed manually.
  if (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
    cmake_parse_arguments (_man_arg "${options}" "${oneValueArgs}"
      "${multiValueArgs}" ${ARGN})

  else (${CMAKE_VERSION} VERSION_GREATER 2.8.1)
    set (_current_section "")
    set (_man_arg_MAN1 "")
    set (_man_arg_MAN3 "")

    foreach (_option_item ${ARGN})
      string (REGEX MATCH "MAN([1-9])" _current_section_tmp "${_option_item}")
      if ("${CMAKE_MATCH_1}" STREQUAL "")
		list (APPEND _man_arg_MAN${_current_section} ${_option_item})
      else ("${CMAKE_MATCH_1}" STREQUAL "")
		set (_current_section "${CMAKE_MATCH_1}")
      endif ("${CMAKE_MATCH_1}" STREQUAL "")
    endforeach (_option_item ${ARGN})
  endif (${CMAKE_VERSION} VERSION_GREATER 2.8.1)

  # Set the documentation directories for the Doxygen configuration file
  doc_set_directories()

  # Browse all the manual sections
  foreach (man_sect ${man_section_list})
	# If the (current) macro was passed arguments for the current manual 
	# section, process the generation of manual pages (with Doxygen).
	if (NOT "${_man_arg_MAN${man_sect}}" STREQUAL "")

	  # Specify in which sub-directory the manual pages are to be found
	  set (man${man_sect}_DIR ${CMAKE_CURRENT_BINARY_DIR}/man${man_sect})
	  # Add that sub-directory to the dedicated list
	  list (APPEND man_dir_list ${man${man_sect}_DIR})

	  # Convert the Doxygen configuration files (basically, just replace
	  # the @<variable>@ variables).
	  set (man_doxy_cfg doxygen_man${man_sect}.cfg)
	  set (DOXYGEN_CFG${man_sect}_SRC ${man_doxy_cfg}.in)
	  set (DOXYGEN_CFG${man_sect} ${CMAKE_CURRENT_BINARY_DIR}/${man_doxy_cfg})
	  configure_file (${DOXYGEN_CFG${man_sect}_SRC}
		${DOXYGEN_CFG${man_sect}} @ONLY)

	  # Manual page sources for the current manual section
	  foreach (_doc_src ${_man_arg_MAN${man_sect}})
		list (APPEND man${man_sect}_SOURCES ${_doc_src}.doc)
	  endforeach (_doc_src ${_man_arg_MAN${man_sect}})

	  # Add the build rule for Doxygen for section 1 manual pages
	  set (DOXYGEN_OUTPUT${man_sect}
		${man${man_sect}_DIR}/stdair-config.${man_sect})
	  add_custom_command (OUTPUT ${DOXYGEN_OUTPUT${man_sect}}
		COMMAND ${DOXYGEN_EXECUTABLE} ARGS ${DOXYGEN_CFG${man_sect}}
		DEPENDS ${DOXYGEN_CFG${man_sect}} ${man${man_sect}_SOURCES}
		COMMENT "Generating section ${man_sect} manual pages with Doxygen, from '${DOXYGEN_CFG${man_sect}}'...")

	  # Transpose the man-page-related operation into a target, so that CMake
	  # can handle it properly
	  add_custom_target (man_${man_sect}
		ALL DEPENDS ${DOXYGEN_OUTPUT${man_sect}})
	  list (APPEND MAN_ALL_TARGETS man_${man_sect})

	  # Specifiy what to do for the installation of the manual pages
	  install (DIRECTORY "${man${man_sect}_DIR}" DESTINATION ${MAN_PATH})

	endif (NOT "${_man_arg_MAN${man_sect}}" STREQUAL "")
  endforeach (man_sect ${man_section_list})

  # Add the 'man' target, depending on the generated manual page documentation
  set (MAN_ALL_TARGETS ${MAN_ALL_TARGETS} PARENT_SCOPE)
  add_custom_target (man)
  add_dependencies (${MAN_ALL_TARGETS})

  # Clean-up $build/man1 and $build/man3 on 'make clean'
  set_property (DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES 
	${man_dir_list})

endmacro (doc_add_man_pages)


###################################################################
##                            GCOV                               ##
###################################################################

macro (gcov_task)
  if (${RUN_GCOV} STREQUAL "ON")
    set (GCDA_GCNO_PATH
	  "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/CMakeFiles/${PROJECT_NAME}lib.dir")
    set (GCDA_FILE "${GCDA_GCNO_PATH}/command/CmdBomSerialiser.cpp.gcda")
    set (GCNO_FILE "${GCDA_GCNO_PATH}/command/CmdBomSerialiser.cpp.gcno")
	# Removed generated gcda and gcno files relative to the CmdBomSerialiser
	# object: gcov failed processing the CmdBomSerialiser.cpp.gcda file
	# without displaying a clear message
    add_custom_command (TARGET check
	  # This task is post-build and post-check
      POST_BUILD  
      # Because the "-f" option is given, the commands do not fail
	  # when the files are missing
	  COMMAND "rm" "-f" "${GCDA_FILE}"
      COMMAND "rm" "-f" "${GCNO_FILE}"
      ) 
	# Build a coverage report info and html pages using gcda and gcno files
    add_custom_command (TARGET check
      # This task is post-build and post-check
      POST_BUILD 
      # Create a directory for the gcov reports
      COMMAND "mkdir" "-p" "${CMAKE_BINARY_DIR}/gcov" 
      # Generate a global gcov report using the directory containing
	  # the gcda/gcno files
      COMMAND "geninfo" "${GCDA_GCNO_PATH}" "-o"
	  "${CMAKE_BINARY_DIR}/gcov/gcov_tmp_report.info"	
      # Extract from the global report the data relative to the module files
	  # (i, e remove external libraries) and copy them in a second report
	  COMMAND "lcov" "-e" "${CMAKE_BINARY_DIR}/gcov/gcov_tmp_report.info"
	  "'${CMAKE_CURRENT_SOURCE_DIR}/*'" ">>"
	  "${CMAKE_BINARY_DIR}/gcov/gcov_report.info"
      # Generate html documentation about the module files coverage
      COMMAND "genhtml" "-o" "${CMAKE_BINARY_DIR}/gcov" "-p"
	  "${CMAKE_CURRENT_SOURCE_DIR}*" "${CMAKE_BINARY_DIR}/gcov/gcov_report.info"
      # Delete heavy .info files
      COMMAND "rm" "${CMAKE_BINARY_DIR}/gcov/*.info"
	  )
  endif (${RUN_GCOV} STREQUAL "ON")
endmacro (gcov_task)


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
  module_export_install()
  set (${PACKAGE_NAME}_INCLUDE_DIRS "${INSTALL_INCLUDE_DIR}")
  set (${PACKAGE_NAME}_BIN_DIR "${INSTALL_BIN_DIR}")
  set (${PACKAGE_NAME}_LIB_DIR "${INSTALL_LIB_DIR}")
  set (${PACKAGE_NAME}_LIBEXEC_DIR "${INSTALL_LIBEXEC_DIR}")
  set (${PACKAGE_NAME}_PY_LIB_DIR "${INSTALL_PY_LIB_DIR}")
  set (${PACKAGE_NAME}_CMAKE_DIR "${LIB_DEPENDENCY_EXPORT_PATH}")
  # When the project is OpenTREP, OPENTREP_SAMPLE_DIR has
  # already been defined before
  if (NOT "${PROJECT_NAME}" STREQUAL "opentrep")
    set (${PACKAGE_NAME}_SAMPLE_DIR "${INSTALL_SAMPLE_DIR}")
  endif (NOT "${PROJECT_NAME}" STREQUAL "opentrep")
  configure_file (${PROJECT_NAME}-config.cmake.in
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" @ONLY)
  if (NEED_PYTHON)
	configure_file (${PROJECT_NAME}-config-python.cmake.in
	  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-python.cmake" @ONLY)
  endif (NEED_PYTHON)
  configure_file (${PROJECT_NAME}-config-version.cmake.in
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake" @ONLY)
  install (FILES
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
	"${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-version.cmake"
	DESTINATION "${${PACKAGE_NAME}_CMAKE_DIR}" COMPONENT devel)
  if (NEED_PYTHON)
	install (FILES
	  "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config-python.cmake"
	  DESTINATION "${${PACKAGE_NAME}_CMAKE_DIR}" COMPONENT python-devel)
  endif (NEED_PYTHON)
  
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
# Doxygen
macro (display_doxygen)
  message (STATUS)
  message (STATUS "* Doxygen:")
  message (STATUS "  - DOXYGEN_VERSION ............... : ${DOXYGEN_VERSION}")
  message (STATUS "  - DOXYGEN_EXECUTABLE ............ : ${DOXYGEN_EXECUTABLE}")
  message (STATUS "  - DOXYGEN_DOT_EXECUTABLE ........ : ${DOXYGEN_DOT_EXECUTABLE}")
  message (STATUS "  - DOXYGEN_DOT_PATH .............. : ${DOXYGEN_DOT_PATH}")
endmacro (display_doxygen)

# Gcov
macro (display_gcov)
  if (${RUN_GCOV} STREQUAL "ON")
    message (STATUS)
    message (STATUS "* gcov:")
    message (STATUS "  - GCOV_VERSION .................. : ${GCOV_VERSION}")
    message (STATUS "  - GCOV_EXECUTABLE ............... : ${GCOV_EXECUTABLE}")
    message (STATUS "  - GCOV_DOT_EXECUTABLE ........... : ${GCOV_DOT_EXECUTABLE}")
    message (STATUS "  - GCOV_DOT_PATH ................. : ${GCOV_DOT_PATH}")
  endif (${RUN_GCOV} STREQUAL "ON")
endmacro (display_gcov)

# Lcov
macro (display_lcov)
  if (${RUN_GCOV} STREQUAL "ON")
    message (STATUS)
    message (STATUS "* lcov:")
    message (STATUS "  - LCOV_VERSION .................. : ${LCOV_VERSION}")
    message (STATUS "  - LCOV_EXECUTABLE ............... : ${LCOV_EXECUTABLE}")
    message (STATUS "  - LCOV_DOT_EXECUTABLE ........... : ${LCOV_DOT_EXECUTABLE}")
    message (STATUS "  - LCOV_DOT_PATH ................. : ${LCOV_DOT_PATH}")
  endif (${RUN_GCOV} STREQUAL "ON")
endmacro (display_lcov)

# Python
macro (display_python)
  if (NEED_PYTHON)
    message (STATUS)
    message (STATUS "* Python:")
    message (STATUS "  - Python3_VERSION ............... : ${Python3_VERSION}")
    message (STATUS "  - Python3_VERSION_{MJR,MNR,PTCH}  : ${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}.${Python3_VERSION_PATCH}")
    message (STATUS "  - Python3_INCLUDE_DIRS .......... : ${Python3_INCLUDE_DIRS}")
    message (STATUS "  - Python3_LIBRARIES ............. : ${Python3_LIBRARIES}")
    message (STATUS "  - Python3_LIBRARY_DIRS .......... : ${Python3_LIBRARY_DIRS}")
    message (STATUS "  - Python3_RUNTIME_LIBRARY_DIRS .. : ${Python3_RUNTIME_LIBRARY_DIRS}")
  else (NEED_PYTHON)
    message (STATUS)
    message (STATUS "* Python not required")
  endif (NEED_PYTHON)
endmacro (display_python)

# ICU
macro (display_icu)
  if (ICU_FOUND)
    message (STATUS)
    message (STATUS "* ICU:")
    message (STATUS "  - ICU_VERSION ................... : ${ICU_VERSION}")
    message (STATUS "  - ICU_LIBRARIES ................. : ${ICU_LIBRARIES}")
    message (STATUS "  - ICU_INCLUDE_DIRS .............. : ${ICU_INCLUDE_DIR}")
  endif (ICU_FOUND)
endmacro (display_icu)

# ZeroMQ
macro (display_zeromq)
  if (ZEROMQ_FOUND)
    message (STATUS)
	message (STATUS "* ZeroMQ:")
	message (STATUS "  - ZeroMQ_VERSION ................ : ${ZeroMQ_VERSION}")
	message (STATUS "  - ZeroMQ_LIBRARIES .............. : ${ZeroMQ_LIBRARIES}")
	message (STATUS "  - ZeroMQ_INCLUDE_DIR ............ : ${ZeroMQ_INCLUDE_DIR}")
  endif (ZEROMQ_FOUND)
endmacro (display_zeromq)

# Boost
macro (display_boost)
  if (Boost_FOUND)
    message (STATUS)
    message (STATUS "* Boost:")
    message (STATUS "  - Boost_VERSION ................. : ${Boost_VERSION}")
    message (STATUS "  - Boost_VERSION_MACRO ........... : ${Boost_VERSION_MACRO}")
    message (STATUS "  - Boost_LIB_VERSION ............. : ${Boost_LIB_VERSION}")
    message (STATUS "  - Boost_HUMAN_VERSION ........... : ${Boost_HUMAN_VERSION}")
    message (STATUS "  - Boost_INCLUDE_DIRS ............ : ${Boost_INCLUDE_DIRS}")
    if (NEED_PYTHON)
      message (STATUS "  - Boost_PYTHON_VERSION .......... : ${Boost_PYTHON_VERSION}")
    endif (NEED_PYTHON)     
    message (STATUS "  - Boost required components ..... : ${BOOST_REQUIRED_COMPONENTS}")
    message (STATUS "  - Boost required libraries ...... : ${BOOST_REQUIRED_LIBS}")
    message (STATUS "  - Boost required libs for Py ext. : ${PROJ_DEP_LIBS_FOR_PYEXT}")
    message (STATUS "  - Boost required libs for bin ... : ${PROJ_DEP_LIBS_FOR_BIN}")
    message (STATUS "  - Boost required libs for test .. : ${PROJ_DEP_LIBS_FOR_TST}")
  endif (Boost_FOUND)
endmacro (display_boost)

# Protobuf
macro (display_protobuf)
  if (PROTOBUF_FOUND)
    message (STATUS)
    message (STATUS "* Protobuf:")
    message (STATUS "  - PROTOBUF_VERSION .............. : ${PROTOBUF_VERSION}")
    message (STATUS "  - PROTOBUF_INCLUDE_DIR .......... : ${PROTOBUF_INCLUDE_DIR}")
    message (STATUS "  - PROTOBUF_LIBRARY .............. : ${PROTOBUF_LIBRARY}")
    message (STATUS "  - PROTOBUF_PROTOC_EXECUTABLE .... : ${PROTOBUF_PROTOC_EXECUTABLE}")
    message (STATUS "  - PROTOBUF_PROTOC_LIBRARY ....... : ${PROTOBUF_PROTOC_LIBRARY}")
  endif (PROTOBUF_FOUND)
endmacro (display_protobuf)

# Xapian
macro (display_xapian)
  if (XAPIAN_FOUND)
    message (STATUS)
    message (STATUS "* Xapian:")
    message (STATUS "  - XAPIAN_VERSION ................ : ${XAPIAN_VERSION}")
    message (STATUS "  - XAPIAN_LIBRARIES .............. : ${XAPIAN_LIBRARIES}")
    message (STATUS "  - XAPIAN_INCLUDE_DIR ............ : ${XAPIAN_INCLUDE_DIR}")
  endif (XAPIAN_FOUND)
endmacro (display_xapian)

# Readline
macro (display_readline)
  if (READLINE_FOUND)
    message (STATUS)
    message (STATUS "* Readline:")
    message (STATUS "  - READLINE_VERSION .............. : ${READLINE_VERSION}")
    message (STATUS "  - READLINE_INCLUDE_DIR .......... : ${READLINE_INCLUDE_DIR}")
    message (STATUS "  - READLINE_LIBRARY .............. : ${READLINE_LIBRARY}")
  endif (READLINE_FOUND)
endmacro (display_readline)

# (N)Curses
macro (display_curses)
  if (CURSES_FOUND)
    message (STATUS)
    message (STATUS "* (N)Curses:")
    message (STATUS "  - CURSES_VERSION ................ : ${CURSES_VERSION}")
    message (STATUS "  - CURSES_INCLUDE_DIR ............ : ${CURSES_INCLUDE_DIR}")
    message (STATUS "  - CURSES_LIBRARY ................ : ${CURSES_LIBRARY}")
  endif (CURSES_FOUND)
endmacro (display_curses)

# SQLite3
macro (display_sqlite)
  if (SQLITE3_FOUND)
    message (STATUS)
    message (STATUS "* SQLite3:")
    message (STATUS "  - SQLITE3_VERSION ............... : ${SQLITE3_VERSION}")
    message (STATUS "  - SQLITE3_INCLUDE_DIR ........... : ${SQLITE3_INCLUDE_DIR}")
    message (STATUS "  - SQLITE3_LIBRARIES ............. : ${SQLITE3_LIBRARIES}")
  endif (SQLITE3_FOUND)
endmacro (display_sqlite)

# MySQL
macro (display_mysql)
  if (MYSQL_FOUND)
    message (STATUS)
    message (STATUS "* MySQL:")
    message (STATUS "  - MYSQL_VERSION ................. : ${MYSQL_VERSION}")
    message (STATUS "  - MYSQL_INCLUDE_DIR ............. : ${MYSQL_INCLUDE_DIR}")
    message (STATUS "  - MYSQL_LIBRARIES ............... : ${MYSQL_LIBRARIES}")
  endif (MYSQL_FOUND)
endmacro (display_mysql)

# SOCI
macro (display_soci)
  if (SOCI_FOUND)
    message (STATUS)
    message (STATUS "* SOCI:")
    message (STATUS "  - SOCI_VERSION .................. : ${SOCI_VERSION}")
    message (STATUS "  - SOCI_LIB_VERSION .............. : ${SOCI_LIB_VERSION}")
    message (STATUS "  - SOCI_HUMAN_VERSION ............ : ${SOCI_HUMAN_VERSION}")
    message (STATUS "  - SOCI_INCLUDE_DIR .............. : ${SOCI_INCLUDE_DIR}")
    message (STATUS "  - SOCIMYSQL_INCLUDE_DIR ......... : ${SOCIMYSQL_INCLUDE_DIR}")
    message (STATUS "  - SOCISQLITE_INCLUDE_DIR ........ : ${SOCISQLITE_INCLUDE_DIR}")
    message (STATUS "  - SOCI_LIBRARIES ................ : ${SOCI_LIBRARIES}")
    message (STATUS "  - SOCIMYSQL_LIBRARIES ........... : ${SOCIMYSQL_LIBRARIES}")
    message (STATUS "  - SOCISQLITE_LIBRARIES .......... : ${SOCISQLITE_LIBRARIES}")
  endif (SOCI_FOUND)
endmacro (display_soci)

# OpenTravelData (OPTD)
macro (display_optd)
  if (OPTD_POR_DIR)
    message (STATUS)
    message (STATUS "* OPTD:")
    message (STATUS "    - OPTD_POR_DIR ................ : ${OPTD_POR_DIR}")
  endif (OPTD_POR_DIR)
endmacro (display_optd)

# StdAir
macro (display_stdair)
  if (StdAir_FOUND)
    message (STATUS)
    message (STATUS "* StdAir:")
    message (STATUS "  - STDAIR_VERSION ................ : ${STDAIR_VERSION}")
    message (STATUS "  - STDAIR_BINARY_DIRS ............ : ${STDAIR_BINARY_DIRS}")
    message (STATUS "  - STDAIR_EXECUTABLES ............ : ${STDAIR_EXECUTABLES}")
    message (STATUS "  - STDAIR_LIBRARY_DIRS ........... : ${STDAIR_LIBRARY_DIRS}")
    message (STATUS "  - STDAIR_LIBRARIES .............. : ${STDAIR_LIBRARIES}")
    message (STATUS "  - STDAIR_INCLUDE_DIRS ........... : ${STDAIR_INCLUDE_DIRS}")
    message (STATUS "  - STDAIR_SAMPLE_DIR ............. : ${STDAIR_SAMPLE_DIR}")
  endif (StdAir_FOUND)
endmacro (display_stdair)

# SEvMgr
macro (display_sevmgr)
  if (SEvMgr_FOUND)
    message (STATUS)
    message (STATUS "* SEvMgr:")
    message (STATUS "  - SEVMGR_VERSION ................ : ${SEVMGR_VERSION}")
    message (STATUS "  - SEVMGR_BINARY_DIRS ............ : ${SEVMGR_BINARY_DIRS}")
    message (STATUS "  - SEVMGR_EXECUTABLES ............ : ${SEVMGR_EXECUTABLES}")
    message (STATUS "  - SEVMGR_LIBRARY_DIRS ........... : ${SEVMGR_LIBRARY_DIRS}")
    message (STATUS "  - SEVMGR_LIBRARIES .............. : ${SEVMGR_LIBRARIES}")
    message (STATUS "  - SEVMGR_INCLUDE_DIRS ........... : ${SEVMGR_INCLUDE_DIRS}")
  endif (SEvMgr_FOUND)
endmacro (display_sevmgr)

# TraDemGen
macro (display_trademgen)
  if (TraDemGen_FOUND)
    message (STATUS)
    message (STATUS "* TraDemGen:")
    message (STATUS "  - TRADEMGEN_VERSION ............. : ${TRADEMGEN_VERSION}")
    message (STATUS "  - TRADEMGEN_BINARY_DIRS ......... : ${TRADEMGEN_BINARY_DIRS}")
    message (STATUS "  - TRADEMGEN_EXECUTABLES ......... : ${TRADEMGEN_EXECUTABLES}")
    message (STATUS "  - TRADEMGEN_LIBRARY_DIRS ........ : ${TRADEMGEN_LIBRARY_DIRS}")
    message (STATUS "  - TRADEMGEN_LIBRARIES ........... : ${TRADEMGEN_LIBRARIES}")
    message (STATUS "  - TRADEMGEN_INCLUDE_DIRS ........ : ${TRADEMGEN_INCLUDE_DIRS}")
  endif (TraDemGen_FOUND)
endmacro (display_trademgen)

# TravelCCM
macro (display_travelccm)
  if (TravelCCM_FOUND)
    message (STATUS)
    message (STATUS "* TravelCCM:")
    message (STATUS "  - TRAVELCCM_VERSION ............. : ${TRAVELCCM_VERSION}")
    message (STATUS "  - TRAVELCCM_BINARY_DIRS ......... : ${TRAVELCCM_BINARY_DIRS}")
    message (STATUS "  - TRAVELCCM_EXECUTABLES ......... : ${TRAVELCCM_EXECUTABLES}")
    message (STATUS "  - TRAVELCCM_LIBRARY_DIRS ........ : ${TRAVELCCM_LIBRARY_DIRS}")
    message (STATUS "  - TRAVELCCM_LIBRARIES ........... : ${TRAVELCCM_LIBRARIES}")
    message (STATUS "  - TRAVELCCM_INCLUDE_DIRS ........ : ${TRAVELCCM_INCLUDE_DIRS}")
  endif (TravelCCM_FOUND)
endmacro (display_travelccm)

# AirTSP
macro (display_airtsp)
  if (AirTSP_FOUND)
    message (STATUS)
    message (STATUS "* AirTSP:")
    message (STATUS "  - AIRTSP_VERSION .............. : ${AIRTSP_VERSION}")
    message (STATUS "  - AIRTSP_BINARY_DIRS .......... : ${AIRTSP_BINARY_DIRS}")
    message (STATUS "  - AIRTSP_EXECUTABLES .......... : ${AIRTSP_EXECUTABLES}")
    message (STATUS "  - AIRTSP_LIBRARY_DIRS ......... : ${AIRTSP_LIBRARY_DIRS}")
    message (STATUS "  - AIRTSP_LIBRARIES ............ : ${AIRTSP_LIBRARIES}")
    message (STATUS "  - AIRTSP_INCLUDE_DIRS ......... : ${AIRTSP_INCLUDE_DIRS}")
  endif (AirTSP_FOUND)
endmacro (display_airtsp)

# AirRAC
macro (display_airrac)
  if (AirRAC_FOUND)
    message (STATUS)
    message (STATUS "* AirRAC:")
    message (STATUS "  - AIRRAC_VERSION ................ : ${AIRRAC_VERSION}")
    message (STATUS "  - AIRRAC_BINARY_DIRS ............ : ${AIRRAC_BINARY_DIRS}")
    message (STATUS "  - AIRRAC_EXECUTABLES ............ : ${AIRRAC_EXECUTABLES}")
    message (STATUS "  - AIRRAC_LIBRARY_DIRS ........... : ${AIRRAC_LIBRARY_DIRS}")
    message (STATUS "  - AIRRAC_LIBRARIES .............. : ${AIRRAC_LIBRARIES}")
    message (STATUS "  - AIRRAC_INCLUDE_DIRS ........... : ${AIRRAC_INCLUDE_DIRS}")
  endif (AirRAC_FOUND)
endmacro (display_airrac)

# RMOL
macro (display_rmol)
  if (RMOL_FOUND)
    message (STATUS)
    message (STATUS "* RMOL:")
    message (STATUS "  - RMOL_VERSION .................. : ${RMOL_VERSION}")
    message (STATUS "  - RMOL_BINARY_DIRS .............. : ${RMOL_BINARY_DIRS}")
    message (STATUS "  - RMOL_EXECUTABLES .............. : ${RMOL_EXECUTABLES}")
    message (STATUS "  - RMOL_LIBRARY_DIRS ............. : ${RMOL_LIBRARY_DIRS}")
    message (STATUS "  - RMOL_LIBRARIES ................ : ${RMOL_LIBRARIES}")
    message (STATUS "  - RMOL_INCLUDE_DIRS ............. : ${RMOL_INCLUDE_DIRS}")
  endif (RMOL_FOUND)
endmacro (display_rmol)

# AirInv
macro (display_airinv)
  if (AirInv_FOUND)
    message (STATUS)
    message (STATUS "* AirInv:")
    message (STATUS "  - AIRINV_VERSION ................ : ${AIRINV_VERSION}")
    message (STATUS "  - AIRINV_BINARY_DIRS ............ : ${AIRINV_BINARY_DIRS}")
    message (STATUS "  - AIRINV_EXECUTABLES ............ : ${AIRINV_EXECUTABLES}")
    message (STATUS "  - AIRINV_LIBRARY_DIRS ........... : ${AIRINV_LIBRARY_DIRS}")
    message (STATUS "  - AIRINV_LIBRARIES .............. : ${AIRINV_LIBRARIES}")
    message (STATUS "  - AIRINV_INCLUDE_DIRS ........... : ${AIRINV_INCLUDE_DIRS}")
  endif (AirInv_FOUND)
endmacro (display_airinv)

# AvlCal
macro (display_avlcal)
  if (AvlCal_FOUND)
    message (STATUS)
    message (STATUS "* AvlCal:")
    message (STATUS "  - AVLCAL_VERSION ................ : ${AVLCAL_VERSION}")
    message (STATUS "  - AVLCAL_BINARY_DIRS ............ : ${AVLCAL_BINARY_DIRS}")
    message (STATUS "  - AVLCAL_EXECUTABLES ............ : ${AVLCAL_EXECUTABLES}")
    message (STATUS "  - AVLCAL_LIBRARY_DIRS ........... : ${AVLCAL_LIBRARY_DIRS}")
    message (STATUS "  - AVLCAL_LIBRARIES .............. : ${AVLCAL_LIBRARIES}")
    message (STATUS "  - AVLCAL_INCLUDE_DIRS ........... : ${AVLCAL_INCLUDE_DIRS}")
  endif (AvlCal_FOUND)
endmacro (display_avlcal)

# SimFQT
macro (display_simfqt)
  if (SimFQT_FOUND)
    message (STATUS)
    message (STATUS "* SimFQT:")
    message (STATUS "  - SIMFQT_VERSION ................ : ${SIMFQT_VERSION}")
    message (STATUS "  - SIMFQT_BINARY_DIRS ............ : ${SIMFQT_BINARY_DIRS}")
    message (STATUS "  - SIMFQT_EXECUTABLES ............ : ${SIMFQT_EXECUTABLES}")
    message (STATUS "  - SIMFQT_LIBRARY_DIRS ........... : ${SIMFQT_LIBRARY_DIRS}")
    message (STATUS "  - SIMFQT_LIBRARIES .............. : ${SIMFQT_LIBRARIES}")
    message (STATUS "  - SIMFQT_INCLUDE_DIRS ........... : ${SIMFQT_INCLUDE_DIRS}")
  endif (SimFQT_FOUND)
endmacro (display_simfqt)

# SimLFS
macro (display_simlfs)
  if (SimLFS_FOUND)
    message (STATUS)
    message (STATUS "* SimLFS:")
    message (STATUS "  - SIMLFS_VERSION ................ : ${SIMLFS_VERSION}")
    message (STATUS "  - SIMLFS_BINARY_DIRS ............ : ${SIMLFS_BINARY_DIRS}")
    message (STATUS "  - SIMLFS_EXECUTABLES ............ : ${SIMLFS_EXECUTABLES}")
    message (STATUS "  - SIMLFS_LIBRARY_DIRS ........... : ${SIMLFS_LIBRARY_DIRS}")
    message (STATUS "  - SIMLFS_LIBRARIES .............. : ${SIMLFS_LIBRARIES}")
    message (STATUS "  - SIMLFS_INCLUDE_DIRS ........... : ${SIMLFS_INCLUDE_DIRS}")
  endif (SimLFS_FOUND)
endmacro (display_simlfs)

# SimCRS
macro (display_simcrs)
  if (SimCRS_FOUND)
    message (STATUS)
    message (STATUS "* SimCRS:")
    message (STATUS "  - SIMCRS_VERSION ................ : ${SIMCRS_VERSION}")
    message (STATUS "  - SIMCRS_BINARY_DIRS ............ : ${SIMCRS_BINARY_DIRS}")
    message (STATUS "  - SIMCRS_EXECUTABLES ............ : ${SIMCRS_EXECUTABLES}")
    message (STATUS "  - SIMCRS_LIBRARY_DIRS ........... : ${SIMCRS_LIBRARY_DIRS}")
    message (STATUS "  - SIMCRS_LIBRARIES .............. : ${SIMCRS_LIBRARIES}")
    message (STATUS "  - SIMCRS_INCLUDE_DIRS ........... : ${SIMCRS_INCLUDE_DIRS}")
  endif (SimCRS_FOUND)
endmacro (display_simcrs)

# TvlSim
macro (display_tvlsim)
  if (TvlSim_FOUND)
    message (STATUS)
    message (STATUS "* TvlSim:")
    message (STATUS "  - TVLSIM_VERSION .................. : ${TVLSIM_VERSION}")
    message (STATUS "  - TVLSIM_BINARY_DIRS .............. : ${TVLSIM_BINARY_DIRS}")
    message (STATUS "  - TVLSIM_EXECUTABLES .............. : ${TVLSIM_EXECUTABLES}")
    message (STATUS "  - TVLSIM_LIBRARY_DIRS ............. : ${TVLSIM_LIBRARY_DIRS}")
    message (STATUS "  - TVLSIM_LIBRARIES ................ : ${TVLSIM_LIBRARIES}")
    message (STATUS "  - TVLSIM_INCLUDE_DIRS ............. : ${TVLSIM_INCLUDE_DIRS}")
  endif (TvlSim_FOUND)
endmacro (display_tvlsim)

##
macro (display_status_all_modules)
  message (STATUS)
  foreach (_module_name ${PROJ_ALL_MOD_FOR_BLD})
    message (STATUS "* Module .......................... : ${_module_name}")
    message (STATUS "  + Layers to build ............... : ${${_module_name}_ALL_LAYERS}")
    message (STATUS "  + Dependencies on other layers .. : ${${_module_name}_INTER_TARGETS}")
    message (STATUS "  + Libraries to build/install .... : ${${_module_name}_ALL_LIBS}")
    message (STATUS "  + Executables to build/install .. : ${${_module_name}_ALL_EXECS}")
    message (STATUS "  + Tests to perform .............. : ${${_module_name}_ALL_TESTS}")
  endforeach (_module_name)
endmacro (display_status_all_modules)

##
macro (display_status_all_test_suites)
  message (STATUS)
  foreach (_test_suite ${PROJ_ALL_SUITES_FOR_TST})
    message (STATUS "* Test Suite ...................... : ${_test_suite}")
    message (STATUS "  + Dependencies on other layers .. : ${${_test_suite}_INTER_TARGETS}")
    message (STATUS "  + Library dependencies .......... : ${${_test_suite}_ALL_LIBS}")
    message (STATUS "  + Tests to perform .............. : ${${_test_suite}_ALL_TESTS}")
  endforeach (_test_suite)
endmacro (display_status_all_test_suites)

##
macro (display_doc_generation)
  message (STATUS)
  message (STATUS "* Documentation to be generated ... :")
  if (INSTALL_DOC)
    message (STATUS "  + HTML main page ................ : ${DOXYGEN_OUTPUT_REL}")
    message (STATUS "  + CSS-related files ............. : ${CSS_ALL_TARGETS}")
    message (STATUS "  + Image-related files ........... : ${IMG_ALL_TARGETS}")
    message (STATUS "  + PDF reference manual .......... : ${REFMAN_TEX} => ${REFMAN_PDF}")
  endif (INSTALL_DOC)
  message (STATUS "  + Man page sections ............. : ${MAN_ALL_TARGETS}")
endmacro (display_doc_generation)

##
macro (display_status_all_external_libraries)
  message (STATUS)
  message (STATUS "* All required external libs ...... : ${PROJ_DEP_LIBS_FOR_LIB}")
endmacro (display_status_all_external_libraries)

##
macro (display_status)
  message (STATUS)
  message (STATUS "=============================================================")
  message (STATUS "-------------------------------------")
  message (STATUS "---      Project Information      ---")
  message (STATUS "-------------------------------------")
  message (STATUS "PROJECT_NAME ...................... : ${PROJECT_NAME}")
  message (STATUS "PACKAGE_PRETTY_NAME ............... : ${PACKAGE_PRETTY_NAME}")
  message (STATUS "PACKAGE ........................... : ${PACKAGE}")
  message (STATUS "PACKAGE_NAME ...................... : ${PACKAGE_NAME}")
  message (STATUS "PACKAGE_BRIEF ..................... : ${PACKAGE_BRIEF}")
  message (STATUS "PACKAGE_VERSION ................... : ${PACKAGE_VERSION}")
  message (STATUS "GENERIC_LIB_VERSION ............... : ${GENERIC_LIB_VERSION}")
  message (STATUS "GENERIC_LIB_SOVERSION ............. : ${GENERIC_LIB_SOVERSION}")
  message (STATUS)
  message (STATUS "-------------------------------------")
  message (STATUS "---       Build Configuration     ---")
  message (STATUS "-------------------------------------")
  message (STATUS "Modules to build .................. : ${PROJ_ALL_MOD_FOR_BLD}")
  message (STATUS "Libraries to build/install ........ : ${PROJ_ALL_LIB_TARGETS}")
  message (STATUS "Binaries to build/install ......... : ${PROJ_ALL_BIN_TARGETS}")
  message (STATUS "Test suites to check .............. : ${PROJ_ALL_SUITES_FOR_TST}")
  message (STATUS "Binaries to test .................. : ${PROJ_ALL_TST_TARGETS}")
  display_status_all_modules ()
  display_status_all_test_suites ()
  display_doc_generation ()
  message (STATUS)
  message (STATUS "BUILD_SHARED_LIBS ................. : ${BUILD_SHARED_LIBS}")
  message (STATUS "CMAKE_BUILD_TYPE .................. : ${CMAKE_BUILD_TYPE}")
  message (STATUS " * CMAKE_VERSION .................. : ${CMAKE_VERSION}")
  message (STATUS " * CMAKE_C_FLAGS .................. : ${CMAKE_C_FLAGS}")
  message (STATUS " * CMAKE_CXX_FLAGS ................ : ${CMAKE_CXX_FLAGS}")
  message (STATUS " * BUILD_FLAGS .................... : ${BUILD_FLAGS}")
  message (STATUS " * COMPILE_FLAGS .................. : ${COMPILE_FLAGS}")
  message (STATUS "ENABLE_TEST ....................... : ${ENABLE_TEST}" )
  message (STATUS "RUN_GCOV .......................... : ${RUN_GCOV}" )
  message (STATUS "CMAKE_MODULE_PATH ................. : ${CMAKE_MODULE_PATH}")
  message (STATUS "CMAKE_INSTALL_PREFIX .............. : ${CMAKE_INSTALL_PREFIX}")
  display_doxygen ()
  display_gcov ()
  display_lcov ()
  message (STATUS)
  message (STATUS "-------------------------------------")
  message (STATUS "---  Installation Configuration   ---")
  message (STATUS "-------------------------------------")
  message (STATUS "INSTALL_LIB_DIR ................... : ${INSTALL_LIB_DIR}")
  message (STATUS "INSTALL_PY_LIB_DIR ................ : ${INSTALL_PY_LIB_DIR}")
  message (STATUS "INSTALL_BIN_DIR ................... : ${INSTALL_BIN_DIR}")
  message (STATUS "INSTALL_LIBEXEC_DIR ............... : ${INSTALL_LIBEXEC_DIR}")
  message (STATUS "CMAKE_INSTALL_RPATH ............... : ${CMAKE_INSTALL_RPATH}")
  message (STATUS "CMAKE_INSTALL_RPATH_USE_LINK_PATH . : ${CMAKE_INSTALL_RPATH_USE_LINK_PATH}")
  message (STATUS "INSTALL_INCLUDE_DIR ............... : ${INSTALL_INCLUDE_DIR}")
  message (STATUS "INSTALL_DATA_DIR .................. : ${INSTALL_DATA_DIR}")
  message (STATUS "INSTALL_SAMPLE_DIR ................ : ${INSTALL_SAMPLE_DIR}")
  message (STATUS "INSTALL_DOC ....................... : ${INSTALL_DOC}" )
  message (STATUS)
  message (STATUS "-------------------------------------")
  message (STATUS "---    Packaging Configuration    ---")
  message (STATUS "-------------------------------------")
  message (STATUS "CPACK_PACKAGE_CONTACT ............. : ${CPACK_PACKAGE_CONTACT}")
  message (STATUS "CPACK_PACKAGE_VENDOR .............. : ${CPACK_PACKAGE_VENDOR}")
  message (STATUS "CPACK_PACKAGE_VERSION ............. : ${CPACK_PACKAGE_VERSION}")
  message (STATUS "CPACK_PACKAGE_DESCRIPTION_FILE .... : ${CPACK_PACKAGE_DESCRIPTION_FILE}")
  message (STATUS "CPACK_RESOURCE_FILE_LICENSE ....... : ${CPACK_RESOURCE_FILE_LICENSE}")
  message (STATUS "CPACK_GENERATOR ................... : ${CPACK_GENERATOR}")
  message (STATUS "CPACK_DEBIAN_PACKAGE_DEPENDS ...... : ${CPACK_DEBIAN_PACKAGE_DEPENDS}")
  message (STATUS "CPACK_SOURCE_GENERATOR ............ : ${CPACK_SOURCE_GENERATOR}")
  message (STATUS "CPACK_SOURCE_PACKAGE_FILE_NAME .... : ${CPACK_SOURCE_PACKAGE_FILE_NAME}")
  #
  message (STATUS)
  message (STATUS "------------------------------------")
  message (STATUS "---      External libraries      ---")
  message (STATUS "------------------------------------")
  #
  display_python ()
  display_icu ()
  display_zeromq ()
  display_boost ()
  display_protobuf ()
  display_xapian ()
  display_readline ()
  display_curses ()
  display_sqlite ()
  display_mysql ()
  display_soci ()
  display_optd ()
  display_stdair ()
  display_sevmgr ()
  display_trademgen ()
  display_travelccm ()
  display_airtsp ()
  display_airrac ()
  display_rmol ()
  display_airinv ()
  display_avlcal ()
  display_simfqt ()
  display_simlfs ()
  display_simcrs ()
  display_tvlsim ()
  display_status_all_external_libraries ()
  #
  message (STATUS)
  message (STATUS "Change a value with: cmake -D<Variable>=<Value>" )
  message (STATUS "=============================================================")
  message (STATUS)

endmacro (display_status)
