# Process this file with autoconf to produce a configure script
#-------------------------------------------------------------------
AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (C) 2007-2010  Denis Arnaud <denis_arnaud@users.sourceforge.net>])
AC_INIT([STDAIR],[99.99.99],[denis_arnaud@users.sourceforge.net],[stdair])
AC_CONFIG_HEADER([stdair/config.h])
AC_CONFIG_SRCDIR([stdair/bom/BomRoot.hpp])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE
AM_PATH_CPPUNIT(1.10)
AM_CONDITIONAL([HAVE_CPPUNIT], [test "x$CPPUNIT_LIBS" != x])

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
              [AC_DEFINE([STDAIR_EXCEPTIONS], [1],
                         [Define if you want exceptions handling])])
test "x$enable_exceptions" != xno && enable_exceptions=yes

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

# -----------------------------------------------------------------------------
# Support for ExtraCC (Extra-CruiseControl): http://sf.net/projects/extracc
# -----------------------------------------------------------------------------
AM_PATH_EXTRACC
AC_SUBST(EXTRACC_VERSION)
AC_SUBST(EXTRACC_CFLAGS)
AC_SUBST(EXTRACC_LIBS)

# --------------------------------------------------------
# Boost (STL Extensions: http://www.boost.org)
# --------------------------------------------------------
AX_BOOST([1.33])
AC_SUBST(BOOST_VERSION)
AC_SUBST(BOOST_CFLAGS)
AC_SUBST(BOOST_LIBS)
AC_SUBST(BOOST_DATE_TIME_LIB)
AC_SUBST(BOOST_PROGRAM_OPTIONS_LIB)
AC_SUBST(BOOST_FILESYSTEM_LIB)

# --------------------------------------------------------------------
# Support for MySQL (C client API): http://www.mysql.org
# --------------------------------------------------------------------
AX_MYSQL
AC_SUBST(MYSQL_VERSION)
AC_SUBST(MYSQL_CFLAGS)
AC_SUBST(MYSQL_LIBS)

# --------------------------------------------------------------------
# Support for SOCI http://soci.sourceforge.net
# --------------------------------------------------------------------
AX_SOCI
AC_SUBST(SOCI_VERSION)
AC_SUBST(SOCI_CFLAGS)
AC_SUBST(SOCI_LIBS)

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
AC_CHECK_HEADERS([fstream iomanip iostream sstream limits list vector map \
  queue stdexcept string])


# config.h top and bottom
AH_TOP([
#ifndef CONFIG_H
#define CONFIG_H
])


# --------------------------------------------------------
# I18n (internationalisation) with GNU Gettext
# --------------------------------------------------------
#AM_GNU_GETTEXT([external], [need-formatstring-macros])
#AM_GNU_GETTEXT_VERSION([0.14])
# Force the usage of the i18n feature: on 64bit architecture,
# as gettext uses conversions from int to char*, there may be
# some issues. However, for regular translation (e.g., to German 
# or French), the PO files are correctly transformed into GMO.
#USE_NLS=yes


# Define configured files
AC_CONFIG_FILES(
	Makefile
	stdair-config
	stdair.pc
	stdair.m4
	stdair/Makefile
	stdair/basic/Makefile
	stdair/bom/Makefile
	stdair/dbadaptor/Makefile
	stdair/factory/Makefile
	stdair/command/Makefile
	stdair/config/Makefile
	stdair/service/Makefile
	batches/Makefile
	man/Makefile
	doc/Makefile
	doc/images/Makefile
	doc/tutorial/Makefile
	doc/tutorial/src/Makefile
	doc/local/Makefile
	doc/doxygen_html.cfg
	test/Makefile
	test/samples/Makefile
	test/inheritance/Makefile
	test/architecture/Makefile
	test/archi_intru/Makefile
	test/archi_static_cast/Makefile
	test/mpl/Makefile
	test/mpl/contrib/Makefile
	test/stdair/Makefile
)
AC_OUTPUT

echo "
------------------------------------------------------------------------------
$PACKAGE-$VERSION library configuration:
------------------------------------------------------------------------------

Directories:
  - prefix ............ : ${prefix}
  - exec_prefix ....... : ${exec_prefix}
  - includedir ........ : ${includedir}
  - libdir ............ : ${libdir}
  - docdir ............ : ${docdir}
  - mandir ............ : ${mandir}
  - infodir ........... : ${infodir}

Switches:
  - exceptions ........ : ${enable_exceptions}
  - use-nls ........... : ${USE_NLS}
  - info-doc .......... : ${enable_info_doc}
  - html-doc .......... : ${enable_html_doc}
  - shared ............ : ${enable_shared}
  - static ............ : ${enable_static}

Documentation tools:
  - texinfo ........... : ${texinfo_ok}
  - doxygen ........... : ${doxygen_ok}
  - latex ............. : ${latex_ok}
  - dvips ............. : ${dvips_ok}
  - ghostscript ....... : ${gs_ok}

Testing tools:
  - diff .............. : ${diff_ok}
  - sed ............... : ${sed_ok}

Compiler/linker flags/libs/defs:
  - CXX ............... : ${CXX}
  - CFLAGS ............ : ${CFLAGS}
  - CXXFLAGS .......... : ${CXXFLAGS}
  - CPPFLAGS .......... : ${CPPFLAGS}
  - FFLAGS ............ : ${FFLAGS}
  - LDFLAGS ........... : ${LDFLAGS}
  - LIBS .............. : ${LIBS}

External libraries:
  - Boost ............. :
    o BOOST_VERSION ... : ${BOOST_VERSION}
    o BOOST_CFLAGS .... : ${BOOST_CFLAGS}
    o BOOST_LIBS ...... : ${BOOST_LIBS}
    o BOOST_DT_LIB .... : ${BOOST_DATE_TIME_LIB}
    o BOOST_PO_LIB .... : ${BOOST_PROGRAM_OPTIONS_LIB}
    o BOOST_FS_LIB .... : ${BOOST_FILESYSTEM_LIB}

  - MySQL ............. :
    o MYSQL_version ... : ${MYSQL_VERSION}
    o MYSQL_CFLAGS .... : ${MYSQL_CFLAGS}
    o MYSQL_LIBS ...... : ${MYSQL_LIBS} 

  - SOCI .............. :	
    o SOCI_version .... : ${SOCI_VERSION}
    o SOCI_CFLAGS ..... : ${SOCI_CFLAGS}
    o SOCI_LIBS ....... : ${SOCI_LIBS}

  - ExtraCC ........... :
    o EXTRACC_VERSION . : ${EXTRACC_VERSION}
    o EXTRACC_CFLAGS .. : ${EXTRACC_CFLAGS}
    o EXTRACC_LIBS .... : ${EXTRACC_LIBS}

  - CPPUNIT ........... :
    o CPPUNIT_VERSION . : ${CPPUNIT_VERSION}
    o CPPUNIT_CFLAGS .. : ${CPPUNIT_CFLAGS}
    o CPPUNIT_LIBS .... : ${CPPUNIT_LIBS}

------------------------------------------------------------------------------
Now type 'make && make install' to build and install $PACKAGE-$VERSION library
------------------------------------------------------------------------------
"
