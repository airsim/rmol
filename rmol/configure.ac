
dnl --------------------------------
dnl Initialization macros.
dnl --------------------------------

AC_INIT(rmollib/RMOL_Service.hpp)
AM_CONFIG_HEADER(config.h)

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

PACKAGE_NAME=rmol
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

dnl PKG_CHECK_MODULES(DEPS, gsl-1.7 >= 1.7)
dnl AC_SUBST(DEPS_CFLAGS)
dnl AC_SUBST(DEPS_LIBS)

dnl -----------------------------------------------
dnl Support for the GSL (GNU Scientific Library)
dnl -----------------------------------------------
GSL_CFLAGS=`gsl-config --cflags`
GSL_LIBS=`gsl-config --libs`
AC_SUBST(GSL_CFLAGS)
AC_SUBST(GSL_LIBS)


dnl -----------------------------------------------
dnl Generates Makefile's, configuration files and scripts
dnl -----------------------------------------------

AC_OUTPUT(Makefile rmol-config rmollib-1.1.pc rmollib/Makefile \
          rmollib/basic/Makefile rmollib/field/Makefile rmollib/bom/Makefile \
          rmollib/factory/Makefile rmollib/command/Makefile \
          test/Makefile)

