##
set (LOCAL_PACKAGE rmol)
set (LOCAL_PROJECT_NAME rmol)

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
# Library target. It is specified here because both the rmol/config (for
# the library target) and rmol/batches (for the binary target)
# sub-directories need it.
set (RMOL_LIB_TARGET ${LOCAL_PROJECT_NAME}lib)
# Library names
set (RMOL_LIB_NAME ${LOCAL_PROJECT_NAME})

##
# Assembling
# Source files for the library
add_library (${RMOL_LIB_TARGET} SHARED ${rmollib_SOURCES})
# Dependencies on other libraries (Boost, MySQL, SOCI, StdAir)
target_link_libraries (${RMOL_LIB_TARGET} 
  ${BOOST_LIBS_FOR_LIB} ${MYSQL_LIBRARIES}
  ${SOCI_LIBRARIES} ${SOCIMYSQL_LIBRARIES}
  ${STDAIR_LIBRARIES})
#
add_dependencies (${RMOL_LIB_TARGET} hdr_cfg_${LOCAL_PACKAGE})
# Filename and SONAME
if (WIN32)
  set_target_properties (${RMOL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${RMOL_LIB_NAME} 
	VERSION ${GENERIC_LIB_VERSION}
	PUBLIC_HEADER "${rmollib_root_HEADERS}")
else (WIN32)
  set_target_properties (${RMOL_LIB_TARGET} PROPERTIES 
	OUTPUT_NAME ${RMOL_LIB_NAME}
	VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION}
	PUBLIC_HEADER "${rmollib_root_HEADERS}")
endif (WIN32)

##
# Add the (local) library to the list of all the libraries built
# by the overall project.
# Note the LOCAL_LIB_TARGET variable is defined by the caller CMake script only,
# i.e. by the root-directory CMake file.
if (NOT LOCAL_LIB_TARGET)
  set (LOCAL_LIB_TARGET ${RMOL_LIB_TARGET} PARENT_SCOPE)
else (NOT LOCAL_LIB_TARGET)
  set (LOCAL_LIB_TARGET ${LOCAL_LIB_TARGET} ${RMOL_LIB_TARGET} PARENT_SCOPE)
endif (NOT LOCAL_LIB_TARGET)

## Installation
# Library
install (TARGETS ${RMOL_LIB_TARGET}
  EXPORT RmolLibraryDepends
  RUNTIME DESTINATION "${INSTALL_BIN_DIR}" COMPONENT bin
  LIBRARY DESTINATION "${INSTALL_LIB_DIR}" COMPONENT shlib
  PUBLIC_HEADER DESTINATION "${INSTALL_INCLUDE_DIR}/${LOCAL_PACKAGE}"
  COMPONENT dev)

##
# Binary
add_subdirectory (batches)

