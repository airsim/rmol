# Process this file with autoconf to produce a configure script
#-------------------------------------------------------------------
AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (C) 2007  Denis Arnaud <denis_arnaud@users.sourceforge.net>])
AC_INIT([RMOL],[0.12.0],[denis_arnaud@users.sourceforge.net],[rmol])
AC_CONFIG_HEADER([rmol/config.h])
AC_CONFIG_SRCDIR([rmol/basic/BasConst.cpp])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE

# RPM release number
RPM_RELEASE="1"
AC_SUBST(RPM_RELEASE)

# RMOL External version
RMOL_EXTERNAL_VERSION="1.00.1"
AC_SUBST(RMOL_EXTERNAL_VERSION)

# Shared library versioning
GENERIC_LIBRARY_VERSION="0:0:0"
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
save_CXXFLAGS="$CXXFLAGS"
AC_PROG_CXX
AC_PROG_CXXCPP
CXXFLAGS="$save_CXXFLAGS"
AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Set default language to C++
AC_LANG([C++])

# Check for debug switch
AC_ARG_ENABLE(debug,
              [AS_HELP_STRING([--enable-debug],
                              [build additional debugging library])])
test "x$enable_debug" != xyes && enable_debug=no
AM_CONDITIONAL([ENABLE_DEBUG], [test "x$enable_debug" = xyes])

# Check for exceptions switch
AC_ARG_ENABLE(exceptions,
              [AS_HELP_STRING([--enable-exceptions],
                              [enable exceptions handling mechanizm])],
              [AC_DEFINE([RMOL_EXCEPTIONS], [1],
                         [Define if you want exceptions handling])])
test "x$enable_exceptions" != xyes && enable_exceptions=no

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


PACKAGE_DEBUG="$PACKAGE"
# Set debug flags
if test "x$enable_debug" = xyes; then
  PACKAGE_DEBUG="$PACKAGE"_debug
  CXXFLAGS_DEBUG="-DASSERT_LEVEL=2 -g"
  # Only for GCC compiler 
  if test "x$GXX" = xyes; then
    if test "x$enable_exceptions" = xno; then
      CXXFLAGS_DEBUG="$CXXFLAGS_DEBUG -fno-exceptions"
    fi
    CXXFLAGS_DEBUG="$CXXFLAGS_DEBUG -Wall -pipe"
  fi
fi
AC_SUBST(CXXFLAGS_DEBUG)
AC_SUBST(PACKAGE_DEBUG)

# Set optimised flags
if test "x$CXXFLAGS" = x; then
  CXXFLAGS_OPT="-DASSERT_LEVEL=1 -O3" 
  # Only for GCC compiler 
  if test "x$GXX" = xyes; then
    if test "x$enable_exceptions" = xno; then
      CXXFLAGS_OPT="$CXXFLAGS_OPT -fno-exceptions"
    fi
    CXXFLAGS_OPT="$CXXFLAGS_OPT -pipe"
  fi
else
  CXXFLAGS_OPT="$CXXFLAGS"
  CXXFLAGS=""
fi
AC_SUBST(CXXFLAGS_OPT)

# -----------------------------------------------
# Support for the GSL (GNU Scientific Library)
# -----------------------------------------------
# Provide --with-gsl
AM_PATH_GSL([1.8])
GSL_VERSION=`${GSL_CONFIG} --version`
AC_SUBST(GSL_CFLAGS)
AC_SUBST(GSL_LIBS)

AX_BOOST([1.33])
AC_SUBST(BOOST_CPPFLAGS)
AC_SUBST(BOOST_LDFLAGS)
AC_SUBST(BOOST_DATE_TIME_LIB)

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


# I18n
AM_GNU_GETTEXT([external], [need-formatstring-macros])
AM_GNU_GETTEXT_VERSION([0.14])

# Define configured files
AC_CONFIG_FILES(
	Makefile
	rmol-config
	rmol.pc
	rmol.spec
	rmol/Makefile
	rmol/basic/Makefile
	rmol/field/Makefile
	rmol/bom/Makefile
	rmol/factory/Makefile
	rmol/command/Makefile
	rmol/service/Makefile
	man/Makefile
	info/Makefile
	doc/Makefile
	doc/images/Makefile
	doc/tutorial/Makefile
	doc/tutorial/src/Makefile
	doc/local/Makefile
	doc/local/index.doc
	doc/doxygen_html.cfg
	doc/sourceforge/howto_release_rmol.html
	po/Makefile.in
	test/Makefile
	win32/Makefile)
AC_OUTPUT

echo "
------------------------------------------------------------------------------
$PACKAGE-$VERSION library configuration:
------------------------------------------------------------------------------

Directories:
  - prefix ......... : ${prefix}
  - exec_prefix .... : ${exec_prefix}
  - includedir ..... : ${includedir}
  - libdir ......... : ${libdir}
  - docdir ......... : ${docdir}
  - mandir ......... : ${mandir}
  - infodir ........ : ${infodir}

Switches:
  - debug .......... : ${enable_debug}
  - exceptions ..... : ${enable_exceptions}
  - info-doc ....... : ${enable_info_doc}
  - html-doc ....... : ${enable_html_doc}
  - shared ......... : ${enable_shared}
  - static ......... : ${enable_static}

Documentation tools:
  - texinfo ........ : ${texinfo_ok}
  - doxygen ........ : ${doxygen_ok}
  - latex .......... : ${latex_ok}
  - dvips .......... : ${dvips_ok}
  - ghostscript .... : ${gs_ok}

Testing tools:
  - diff ........... : ${diff_ok}
  - sed ............ : ${sed_ok}

Compiler/linker flags/libs/defs:
  - CXX ............ : ${CXX}
  - CXXFLAGS ....... : ${CXXFLAGS_OPT}
  - CXXFLAGS_DEBUG . : ${CXXFLAGS_DEBUG}
  - CPPFLAGS ....... : ${CPPFLAGS}
  - LDFLAGS ........ : ${LDFLAGS}
  - LIBS ........... : ${LIBS}

External libraries:
  - GSL ............ : ${GSL_CONFIG}
    o GSL_VERSION .. : ${GSL_VERSION}
    o GSL_CFLAGS ... : ${GSL_CFLAGS}
    o GSL_LIBS ..... : ${GSL_LIBS}

  - Boost .......... :
    o BOOST_VERSION. : ${boost_lib_version_shorten}
    o BOOST_CPPFLAGS : ${BOOST_CPPFLAGS}
    o BOOST_LDFLAGS. : ${BOOST_LDFLAGS}
    o BOOST_DT_LIB.. : ${BOOST_DATE_TIME_LIB}

------------------------------------------------------------------------------
Now type 'make && make install' to build and install $PACKAGE-$VERSION library
------------------------------------------------------------------------------
"
