
dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(src/test/optimise.cpp)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

RMOL_LIBRARY_NAME=rmollib

#release versioning
RMOL_MAJOR_VERSION=1
RMOL_MINOR_VERSION=1
RMOL_MICRO_VERSION=0

#API version (often = RMOL_MAJOR_VERSION.RMOL_MINOR_VERSION)
RMOL_API_VERSION=1.1
AC_SUBST(RMOL_API_VERSION)

#shared library versioning
RMOL_LIBRARY_VERSION=1:1:0
#                       | | |
#                +------+ | +---+
#                |        |     |
#             current:revision:age
#                |        |     |
#                |        |     +- increment if interfaces have been added
#                |        |        set to zero if interfaces have been removed
#                                  or changed
#                |        +- increment if source code has changed
#                |           set to zero if current is incremented
#                +- increment if interfaces have been added, removed or changed


dnl --------------------------------
dnl Package name and version number
dnl --------------------------------

AC_SUBST(RMOL_LIBRARY_VERSION)

PACKAGE=$RMOL_LIBRARY_NAME
AC_SUBST(RMOL_LIBRARY_NAME)

RMOL_VERSION=$RMOL_MAJOR_VERSION.$RMOL_MINOR_VERSION.$RMOL_MICRO_VERSION
RMOL_RELEASE=$RMOL_MAJOR_VERSION.$RMOL_MINOR_VERSION
AC_SUBST(RMOL_RELEASE)
AC_SUBST(RMOL_VERSION)

VERSION=$RMOL_VERSION

AM_INIT_AUTOMAKE($PACKAGE, $VERSION, no-define)

dnl -----------------------------------------------
dnl Checks for programs.
dnl -----------------------------------------------

AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL
AM_SANITY_CHECK

AC_LANG_CPLUSPLUS

dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile rmollib-1.1.pc src/Makefile \
          src/basic/Makefile src/field/Makefile src/bom/Makefile \
          src/factory/Makefile src/command/Makefile src/service/Makefile \
          src/test/Makefile)

