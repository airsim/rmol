##
set (LOCAL_PACKAGE airrac)
set (LOCAL_PROJECT_NAME airrac)

##
# Convert the configuration headers (basically, just replace the @<variable>@
# variables).
if (EXISTS config.h.in)
  configure_file (config.h.in config.h @ONLY)
endif (EXISTS config.h.in)
set (PROJ_PATH_CFG_SRC config/${LOCAL_PACKAGE}-paths.hpp.in)
set (PROJ_PATH_CFG ${CMAKE_CURRENT_BINARY_DIR}/config/${LOCAL_PACKAGE}-paths.hpp)
configure_file (${PROJ_PATH_CFG_SRC} ${PROJ_PATH_CFG} @ONLY)

# Add the 'hdr_cfg_${LOCAL_PACKAGE}' target, depending on the converted header
add_custom_target (hdr_cfg_${LOCAL_PACKAGE} ALL DEPENDS ${PROJ_PATH_CFG})


##
# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
# The libraries could then be assembled as CMake modules.
file (GLOB airraclib_root_HEADERS *.hpp)
file (GLOB airraclib_basic_HEADERS basic/*.hpp)
file (GLOB airraclib_bom_HEADERS bom/*.hpp)
file (GLOB airraclib_factory_HEADERS factory/*.hpp)
file (GLOB airraclib_command_HEADERS command/*.hpp)
file (GLOB airraclib_service_HEADERS service/*.hpp)
set (airraclib_HEADERS
  ${airraclib_root_HEADERS} ${airraclib_basic_HEADERS}
  ${airraclib_bom_HEADERS} ${airraclib_factory_HEADERS}
  ${airraclib_dbadaptor_HEADERS} ${airraclib_command_HEADERS}
  ${airraclib_service_HEADERS} ${PROJ_PATH_CFG})
file (GLOB airraclib_SOURCES
  *.cpp basic/*.cpp bom/*.cpp factory/*.cpp command/*.cpp service/*.cpp)
set (airraclib_SOURCES ${airraclib_HEADERS} ${airraclib_SOURCES})

##
# Assembling
# Source files for the library.
# The library target is specified within the parent directory.
add_library (${LOCAL_LIB_TARGET} SHARED ${airraclib_SOURCES})
# Dependencies on other libraries (Boost, MySQL, SOCI, StdAir)
target_link_libraries (${LOCAL_LIB_TARGET} 
  ${BOOST_LIBS_FOR_LIB} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES}
  ${STDAIR_LIBRARIES} ${EXTRA_LIBS})
#
add_dependencies (${LOCAL_LIB_TARGET} hdr_cfg_${LOCAL_PACKAGE})

##
# Library name (and soname)
set (AIRRAC_LIB_NAME ${LOCAL_PROJECT_NAME})
if (WIN32)
  set_target_properties (${LOCAL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${AIRRAC_LIB_NAME} 
	VERSION ${GENERIC_LIB_VERSION}
	PUBLIC_HEADER "${airraclib_root_HEADERS}")
else (WIN32)
  set_target_properties (${LOCAL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${AIRRAC_LIB_NAME}
	VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
	PUBLIC_HEADER "${airraclib_root_HEADERS}")
endif (WIN32)

##
# Installation
# Library
install (TARGETS ${LOCAL_LIB_TARGET}
  EXPORT ${LIB_DEPENDENCY_EXPORT}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${LOCAL_PACKAGE}"
  COMPONENT dev)

##
# Install the export set for use with the install-tree
install (EXPORT ${LIB_DEPENDENCY_EXPORT} DESTINATION
  "${INSTALL_DATA_DIR}/${PACKAGE}/CMake" COMPONENT dev)

##
# Binary
add_subdirectory (batches)
