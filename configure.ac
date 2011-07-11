# Process this file with autoconf to produce a configure script
#-------------------------------------------------------------------
AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (C) 2007-2011 Denis Arnaud <denis_arnaud@users.sourceforge.net>])
AC_INIT([RMOL],[99.99.99],[denis_arnaud@users.sourceforge.net],[rmol])
AC_CONFIG_HEADER([rmol/config.h])
AC_CONFIG_SRCDIR([rmol/basic/BasConst.cpp])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([config])
AM_INIT_AUTOMAKE
AM_PATH_CPPUNIT(1.10)
AM_CONDITIONAL([HAVE_CPPUNIT], [test "x$CPPUNIT_LIBS" != x])

# Package name
PACKAGE_PRETTY_NAME="RMOL"
AC_SUBST(PACKAGE_PRETTY_NAME)

# Shared library versioning
GENERIC_LIBRARY_VERSION="99:99:99"
#                        | | |
#                 +------+ | +---+
#                 |        |     |
#              current:revision:age
#                 |        |     |
#                 |        |     +- increment if interfaces have been added;
#                 |        |        set to zero if interfaces have been 
#                 |        |        removed or changed
#                 |        +- increment if source code has changed;
#                 |           set to zero if current is incremented
#                 +- increment if interfaces have been added, removed
#                    or changed
AC_SUBST(GENERIC_LIBRARY_VERSION)

# Upload command for SourceForge
UPLOAD_COMMAND="ncftpput -v upload.sourceforge.net /incoming"
AC_SUBST(UPLOAD_COMMAND)

# Check for host and disable building a shared library in Windows
AC_CANONICAL_HOST
case $host in
  *-*-msdos* | *-*-go32* | *-*-mingw32* | *-*-cygwin* | *-*-windows*) 
    AC_DISABLE_SHARED
    AC_ENABLE_STATIC
    ;;
  *)  
    AC_ENABLE_SHARED
    AC_DISABLE_STATIC
    ;;
esac

# Checks for programs
save_CFLAGS="$CFLAGS"
save_CXXFLAGS="$CXXFLAGS"
save_FFLAGS="$FFLAGS"
AC_PROG_CXX
AC_PROG_CXXCPP
CXXFLAGS="$save_CXXFLAGS"
CFLAGS="$save_CFLAGS"
FFLAGS="$save_FFLAGS"
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Set default language to C++
AC_LANG([C++])

# Check for exceptions switch
AC_ARG_ENABLE(exceptions,
              [AS_HELP_STRING([--enable-exceptions],
                              [enable exceptions handling mechanism])],
              [AC_DEFINE([RMOL_EXCEPTIONS], [1],
                         [Define if you want exceptions handling])])
test "x$enable_exceptions" != xno && enable_exceptions=yes

# Set the data directory for RMOL
pkgdatadir="${datadir}/rmol"
AC_SUBST(pkgdatadir)
# Set the directory for data samples exported by RMOL
sampledir="${pkgdatadir}/samples"
AC_SUBST(sampledir)

# Check for info pages
AC_ARG_ENABLE(info-doc, 
              [AS_HELP_STRING([--disable-info-doc],
                              [do not generate Info documentation])])
test "x$enable_info_doc" != xno && enable_info_doc=yes


# Check for html-doc switch
AC_ARG_ENABLE(html-doc, 
              [AS_HELP_STRING([--disable-html-doc],
                              [do not generate HTML documentation])])
test "x$enable_html_doc" != xno && enable_html_doc=yes


# Provide --with-docdir
AC_ARG_WITH(docdir,
            [AS_HELP_STRING([--with-docdir=DIR],
                            [set documentation directory to DIR])],
            [DOC_DIR="$withval"],
            [DOC_DIR=""])
if test "x$DOC_DIR" != x; then
  docdir="$DOC_DIR"
else
  docdir="${datadir}/doc/$PACKAGE-$VERSION"
fi
AC_SUBST(docdir)


# Default compilation flags
if test -z "${CFLAGS}"; then
   CFLAGS="-g -Wall"
fi

if test -z "${CXXFLAGS}"; then
   CXXFLAGS="-g -Wall"
fi


# ---------------------------------------------------------
# GSL (GNU Scientific Library: http://gnu.org/projects/gsl)
# ---------------------------------------------------------
# Note: GSL is now used only to be compared with Boost.Maths, in the tests
AM_PATH_GSL([1.8])

# -----------------------------------------------------------
# Python: http://www.python.org
# -----------------------------------------------------------
PGAC_CHECK_PYTHON_EMBED_SETUP
AC_SUBST(PYTHON_VERSION)
AC_SUBST(PYTHON_LIBS)
AC_SUBST(PYTHON_CFLAGS)
AC_SUBST(PYTHON_ADD_LIBS)

# -----------------------------------------------------------
# OpenMPI: http://www.open-mpi.org
# -----------------------------------------------------------
#AX_OPENMPI
#AC_SUBST(MPIGEN_VERSION)
#AC_SUBST(MPIGEN_CFLAGS)
#AC_SUBST(MPIGEN_LIBS)

# -----------------------------------------------------------
# MPICH2: http://www.mcs.anl.gov/research/projects/mpich2
# -----------------------------------------------------------
#AX_MPICH2
#AC_SUBST(MPIGEN_VERSION)
#AC_SUBST(MPIGEN_CFLAGS)
#AC_SUBST(MPIGEN_LIBS)

# --------------------------------------------------------
# Boost (STL Extensions: http://www.boost.org)
# --------------------------------------------------------
AX_BOOST([1.33])

# --------------------------------------------------------------------
# Support for MySQL (C client API): http://www.mysql.org
# --------------------------------------------------------------------
AX_MYSQL

# --------------------------------------------------------
# SOCI (Database API: http://soci.sourceforge.net)
# --------------------------------------------------------
AX_SOCI([3.0])

# -----------------------------------------------------------------------------
# Support for StdAir (): http://sf.net/projects/stdair
# -----------------------------------------------------------------------------
AM_PATH_STDAIR([0.10.0])

# -------------------------------------------------------------------
# Support for documentation
# -------------------------------------------------------------------
# Checks for documentation build tools
#AC_CHECK_PROG([texinfo_ok], [texinfo], [yes], [no])
#if test "x$enable_info_doc" != xno; then
#  test "x$texinfo_ok" != xyes && enable_info_doc=no
#  AC_PATH_PROG([PERL], [perl], [])
#fi
AM_CONDITIONAL([INFO_DOC], [test "x$enable_info_doc" = xyes])

# Checks for documentation build tools
AC_CHECK_PROG([doxygen_ok], [doxygen], [yes], [no])
AC_CHECK_PROG([latex_ok], [latex], [yes], [no])
AC_CHECK_PROG([dvips_ok], [dvips], [yes], [no])
AC_CHECK_PROG([gs_ok], [gs], [yes], [no])
if test "x$enable_html_doc" != xno; then
  test "x$doxygen_ok" != xyes && enable_html_doc=no
  test "x$latex_ok" != xyes && enable_html_doc=no
  test "x$dvips_ok" != xyes && enable_html_doc=no
  test "x$gs_ok" != xyes && enable_html_doc=no
  AC_PATH_PROG([PERL], [perl], [])
fi
AM_CONDITIONAL([HTML_DOC], [test "x$enable_html_doc" = xyes])


# Check for diff program used for tests
AC_CHECK_PROG([diff_ok], [diff], [yes], [no])
AC_CHECK_PROG([sed_ok], [sed], [yes], [no])
enable_tests=yes
test "x$diff_ok" != xyes && enable_tests=no
test "x$sed_ok" != xyes && enable_tests=no
AM_CONDITIONAL([RUN_TESTS], [test "x$enable_tests" = xyes])


# Checks for header files
AC_HEADER_STDC
AC_HEADER_TIME
AC_CHECK_HEADERS([cmath \
  deque \
  fstream \
  ieeefp.h \
  iomanip \
  iostream \
  sstream \
  limits \
  list \
  vector \
  map \
  queue \
  stdexcept \
  string])


# Checks for global declarations
AC_CHECK_DECLS(signgam, , , [#include <cmath>])


# Checks for functions
AC_CHECK_FUNCS([erf \
  erfc \
  finite \
  fpclass \
  isfinite \
  isinf \
  isnan \
  lgamma \
  log1p \
  rint \
  tgamma])


# Check for finite and fpclass on Solaris
AC_CHECK_FUNC(finite, ,
  [AC_CHECK_FUNC(isfinite, ,
    [AC_TRY_LINK([[#include <ieeefp.h>]], [[float f = 0.0; isfinite(f);]],
      [AC_DEFINE(HAVE_ISFINITE)])])])
AC_CHECK_FUNC(fpclass, ,
  [AC_TRY_LINK([[#include <ieeefp.h>]], [[float f = 0.0; fpclass(f);]],
    [AC_DEFINE(HAVE_FPCLASS)])])


# config.h top and bottom
AH_TOP([
#ifndef CONFIG_H
#define CONFIG_H
])

AH_BOTTOM([
#if HAVE_CMATH
#  include <cmath>
#endif

/* Solaris uses <ieeefp.h> for declaring isnan() and finite() functions */
#if HAVE_IEEEFP_H
#  include <ieeefp.h>
#endif

/* Microsoft Visual C++ .NET underscore prefixed functions */
#if _MSC_VER
#  include <cfloat>
#  define HAVE_FINITE 1
#  define finite(x) _finite(x)
#  define HAVE_ISNAN 1
#  define isnan(x) _isnan(x)
#  define HAVE_FPCLASS 1
#  define fpclass(x) _fpclass(x)
#  define HAVE_JN 1
#  define jn(a, b) _jn(a, b)
#  define HAVE_YN 1
#  define yn(a, b) _yn(a, b)
#  define HAVE_J0 1
#  define j0(a) _j0(a)
#  define HAVE_J1 1
#  define j1(a) _j1(a)
#endif

#if (! defined(HAVE_ISINF) && defined(HAVE_FPCLASS))
#  define HAVE_ISINF 1
#  define isinf(a) (fpclass(a) == FP_NINF || fpclass(a) == FP_PINF)
#endif

#if (! defined (HAVE_FINITE) && defined (HAVE_ISFINITE))
#  define HAVE_FINITE 1
#  define finite(a) isfinite(a)
#endif

#if (! defined(HAVE_FINITE) && defined(HAVE_ISNAN) && defined(HAVE_ISINF))
#  define HAVE_FINITE 1
#  define finite(a) (! isnan(a) && ! isinf(a))
#endif

#endif /* #ifndef CONFIG_H */
])


# --------------------------------------------------------
# I18n (internationalisation) with GNU Gettext
# --------------------------------------------------------
AM_GNU_GETTEXT([external], [need-formatstring-macros])
AM_GNU_GETTEXT_VERSION([0.14])
# Force the usage of the i18n feature: on 64bit architecture,
# as gettext uses conversions from int to char*, there may be
# some issues. However, for regular translation (e.g., to German 
# or French), the PO files are correctly transformed into GMO.
USE_NLS=yes


# Define configured files
AC_CONFIG_FILES(
	Makefile
	rmol-config
	rmol.pc
	rmol.m4
	airrac/Makefile
	airrac/basic/Makefile
	airrac/bom/Makefile
	airrac/factory/Makefile
	airrac/command/Makefile
	airrac/service/Makefile
	airrac/config/Makefile
	airrac/config/airrac-paths.hpp
	airrac/core/Makefile
	airrac/batches/Makefile
	rmol/Makefile
	rmol/basic/Makefile
	rmol/bom/Makefile
	rmol/factory/Makefile
	rmol/command/Makefile
	rmol/service/Makefile
	rmol/core/Makefile
	rmol/config/Makefile
	rmol/config/rmol-paths.hpp
	rmol/batches/Makefile
	man/Makefile
	info/Makefile
	doc/Makefile
	doc/images/Makefile
	doc/tutorial/Makefile
	doc/tutorial/src/Makefile
	doc/local/Makefile
	doc/doxygen_html.cfg
	po/Makefile.in
	samples/Makefile
	samples/RDS01/Makefile
	test/Makefile
	test/architecture/Makefile
	test/gsl_vs_boost/Makefile
	test/valarrays/Makefile
	test/airrac/Makefile
	test/rmol/Makefile
	win32/Makefile)
AC_OUTPUT

# OpenMPI
if test "x$HAVE_OPENMPI" = "x1"; then
   OPENMPI_OUTPUT="  - OPENMPI ................ :
    o OPENMPI_VERSION ...... : ${MPIGEN_VERSION}
    o OPENMPI_CFLAGS ....... : ${MPIGEN_CFLAGS}
    o OPENMPI_LIBS ......... : ${MPIGEN_LIBS}"
else
   OPENMPI_OUTPUT="  - OPENMPI ................ : No"
fi

# MPICH2
if test "x$HAVE_MPICH2" = "x1"; then
   MPICH2_OUTPUT="  - MPICH2 ................. :
    o MPICH2_VERSION ....... : ${MPIGEN_VERSION}
    o MPICH2_CFLAGS ........ : ${MPIGEN_CFLAGS}
    o MPICH2_LIBS .......... : ${MPIGEN_LIBS}"
else
   MPICH2_OUTPUT="  - MPICH2 ................. : No"
fi

echo "
------------------------------------------------------------------------------
$PACKAGE-$VERSION library configuration:
------------------------------------------------------------------------------

Directories:
  - prefix ................. : ${prefix}
  - exec_prefix ............ : ${exec_prefix}
  - includedir ............. : ${includedir}
  - libdir ................. : ${libdir}
  - datarootdir ............ : ${datarootdir}
  - datadir ................ : ${datadir}
  - pkgdatadir ............. : ${pkgdatadir}
  - sampledir .............. : ${sampledir}
  - docdir ................. : ${docdir}
  - mandir ................. : ${mandir}
  - infodir ................ : ${infodir}

Switches:
  - exceptions ............. : ${enable_exceptions}
  - use-nls ................ : ${USE_NLS}
  - info-doc ............... : ${enable_info_doc}
  - html-doc ............... : ${enable_html_doc}
  - shared ................. : ${enable_shared}
  - static ................. : ${enable_static}

Documentation tools:
  - texinfo ................ : ${texinfo_ok}
  - doxygen ................ : ${doxygen_ok}
  - latex .................. : ${latex_ok}
  - dvips .................. : ${dvips_ok}
  - ghostscript ............ : ${gs_ok}

Testing tools:
  - diff ................... : ${diff_ok}
  - sed .................... : ${sed_ok}

Compiler/linker flags/libs/defs:
  - CXX .................... : ${CXX}
  - CXXFLAGS ............... : ${CXXFLAGS}
  - CPPFLAGS ............... : ${CPPFLAGS}
  - LDFLAGS ................ : ${LDFLAGS}
  - LIBS ................... : ${LIBS}

External libraries:
  - GSL .................... : ${GSL_CONFIG}
    o GSL_VERSION .......... : ${GSL_VERSION}
    o GSL_CFLAGS ........... : ${GSL_CFLAGS}
    o GSL_LIBS ............. : ${GSL_LIBS}

${OPENMPI_OUTPUT}

${MPICH2_OUTPUT}

  - Python .................. :
    o PYTHON_VERSION ........ : ${PYTHON_VERSION}
    o PYTHON_CFLAGS ......... : ${PYTHON_CFLAGS}
    o PYTHON_LIBS ........... : ${PYTHON_LIBS} 
    o PYTHON_ADD_LIBS ....... : ${PYTHON_ADD_LIBS} 

  - Boost .................. :
    o BOOST_VERSION ........ : ${BOOST_VERSION}
    o BOOST_CFLAGS ......... : ${BOOST_CFLAGS}
    o BOOST_LIBS ........... : ${BOOST_LIBS}
    o BOOST_UTF_LIB ........ : ${BOOST_UNIT_TEST_FRAMEWORK_LIB}
    o BOOST_DATE_TIME_LIB .. : ${BOOST_DATE_TIME_LIB}
    o BOOST_PO_LIB ......... : ${BOOST_PROGRAM_OPTIONS_LIB}
    o BOOST_SYSTEM_LIB ..... : ${BOOST_SYSTEM_LIB}
    o BOOST_FILESYSTEM_LIB . : ${BOOST_FILESYSTEM_LIB}
    o BOOST_THREAD_LIB ..... : ${BOOST_THREAD_LIB}
    o BOOST_PYTHON_LIB ..... : ${BOOST_PYTHON_LIB}
    o BOOST_ASIO_LIB ....... : ${BOOST_ASIO_LIB}
    o BOOST_MPI_LIB ........ : ${BOOST_MPI_LIB}
    o BOOST_MPI_PYTHON_LIB . : ${BOOST_MPI_PYTHON_LIB}
    o BOOST_IOSTREAMS_LIB .. : ${BOOST_IOSTREAMS_LIB}
    o BOOST_SIGNALS_LIB .... : ${BOOST_SIGNALS_LIB}
    o BOOST_SERIAL_LIB ..... : ${BOOST_SERIALIZATION_LIB}
    o BOOST_WSERIAL_LIB .... : ${BOOST_WSERIALIZATION_LIB}
    o BOOST_REGEX_LIB ...... : ${BOOST_REGEX_LIB}

  - MySQL .................. :
    o MYSQL_VERSION ........ : ${MYSQL_VERSION}
    o MYSQL_CFLAGS ......... : ${MYSQL_CFLAGS}
    o MYSQL_LIBS ........... : ${MYSQL_LIBS} 

  - Soci ................... :
    o SOCI_VERSION ......... : ${SOCI_VERSION}
    o SOCI_CFLAGS .......... : ${SOCI_CFLAGS}
    o SOCI_LIBS ............ : ${SOCI_LIBS}

  - StdAir ................. :
    o STDAIR_VERSION ....... : ${STDAIR_VERSION}
    o STDAIR_CFLAGS ........ : ${STDAIR_CFLAGS}
    o STDAIR_LIBS .......... : ${STDAIR_LIBS}
    o STDAIR_SAMPLE_DIR .... : ${STDAIR_SAMPLE_DIR}

------------------------------------------------------------------------------
Now type 'make && make install' to build and install $PACKAGE-$VERSION library
------------------------------------------------------------------------------
"

