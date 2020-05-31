##
# RMOL module
module_set_name (rmol)

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
module_library_add_standard (".;basic;bom;factory;command;service")

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
module_library_add_specific (pyrmol python "na" python/pyrmol.cpp)

##
# Building and installation of the executables/binaries.
# The two parameters (among which only the first one is mandatory) are:
#  * The path/directory where the header and source files can be found
#    in order to build the executable.
#  * If specified, the name to be given to the executable. If no such name
#    is given as parameter, the executable is given the name of the current
#    module.
module_binary_add (batches rmol)

##
# Installing Python and Shell scripts
module_script_add (python/pyrmol)
python_module_add (python/__init__.py)
module_script_add (python/rmol_drawBPC)
module_script_add (tools/rmol_extractBPC)


