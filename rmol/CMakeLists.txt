##
# RMOL module
module_set_name (rmol)

##
# Convert the configuration headers (basically, just replace the @<variable>@
# variables).
module_generate_config_helpers ()

##
# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
# The libraries could then be assembled as CMake modules.
module_define_sources (basic bom factory command service)

##
# Assembling
# The parameters correspond to the names of the modules this current
# module depends upon. Dependencies on the external libraries (e.g.,
# Boost, SOCI, StdAir) are automatically appended, thanks to the
# get_external_libs() macro.
module_library_add_standard (airrac)

##
# Library installation
# The parameter corresponds to additional libraries to be installed.
# When no parameter is given, only the standard library is installed.
module_library_install_all ()

##
# Assembling: specify the standard binary target for the current module.
module_binary_add_standard ()

##
# Binary installation
# The parameter corresponds to additional binaries to be installed.
# When no parameter is given, only the standard binary is installed.
module_binary_install_all ()

##
# Install the CMake import helper, so that third party projects can refer to it
# (for libraries, header files and binaries)
module_export_install ()
