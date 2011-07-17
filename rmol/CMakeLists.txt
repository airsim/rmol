##
#
set (MODULE_NAME rmol)

##
# Convert the configuration headers (basically, just replace the @<variable>@
# variables).
if (EXISTS config.h.in)
  configure_file (config.h.in config.h @ONLY)
endif (EXISTS config.h.in)
set (PROJ_PATH_CFG_SRC config/${MODULE_NAME}-paths.hpp.in)
set (PROJ_PATH_CFG ${CMAKE_CURRENT_BINARY_DIR}/config/${MODULE_NAME}-paths.hpp)
configure_file (${PROJ_PATH_CFG_SRC} ${PROJ_PATH_CFG} @ONLY)

# Add the 'hdr_cfg_${MODULE_NAME}' target, depending on the converted header
add_custom_target (hdr_cfg_${MODULE_NAME} ALL DEPENDS ${PROJ_PATH_CFG})


##
# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
# The libraries could then be assembled as CMake modules.
file (GLOB rmollib_root_HEADERS *.hpp)
file (GLOB rmollib_basic_HEADERS basic/*.hpp)
file (GLOB rmollib_bom_HEADERS bom/*.hpp)
file (GLOB rmollib_factory_HEADERS factory/*.hpp)
file (GLOB rmollib_command_HEADERS command/*.hpp)
file (GLOB rmollib_service_HEADERS service/*.hpp)
set (rmollib_HEADERS
  ${rmollib_root_HEADERS} ${rmollib_basic_HEADERS}
  ${rmollib_bom_HEADERS} ${rmollib_factory_HEADERS}
  ${rmollib_dbadaptor_HEADERS} ${rmollib_command_HEADERS}
  ${rmollib_service_HEADERS} ${PROJ_PATH_CFG})
file (GLOB rmollib_SOURCES
  *.cpp basic/*.cpp bom/*.cpp factory/*.cpp command/*.cpp service/*.cpp)
set (rmollib_SOURCES ${rmollib_HEADERS} ${rmollib_SOURCES})

##
# Assembling
# Source files for the library.
# The library target is specified within the parent directory.
set (MODULE_LIB_TARGET ${MODULE_NAME}lib)
add_library (${MODULE_LIB_TARGET} SHARED ${rmollib_SOURCES})
# Dependencies on other libraries (Boost, MySQL, SOCI, StdAir)
target_link_libraries (${MODULE_LIB_TARGET} 
  ${BOOST_LIBS_FOR_LIB} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES}
  ${STDAIR_LIBRARIES} airraclib)
#
add_dependencies (${MODULE_LIB_TARGET} hdr_cfg_${MODULE_NAME})

##
# Library name (and soname)
set (RMOL_LIB_NAME ${MODULE_NAME})
if (WIN32)
  set_target_properties (${MODULE_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${RMOL_LIB_NAME} 
	VERSION ${GENERIC_LIB_VERSION}
	PUBLIC_HEADER "${rmollib_root_HEADERS}")
else (WIN32)
  set_target_properties (${MODULE_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${RMOL_LIB_NAME}
	VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
	PUBLIC_HEADER "${rmollib_root_HEADERS}")
endif (WIN32)

##
# Installation
# Library
install (TARGETS ${MODULE_LIB_TARGET}
  EXPORT ${LIB_DEPENDENCY_EXPORT}
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT runtime
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT runtime
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${MODULE_NAME}"
  COMPONENT devel)

##
# Binary
add_subdirectory (batches)

##
# Install the CMake import helper, so that third party projects can refer to it
# (for libraries, header files and binaries)
install (EXPORT ${LIB_DEPENDENCY_EXPORT} DESTINATION
  "${INSTALL_DATA_DIR}/${PACKAGE}/CMake" COMPONENT devel)
