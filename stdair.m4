#
# Configure paths and flags for the StdAir library.
# Denis Arnaud <denis_arnaud at users dot sourceforge dot net>, July 2008
#
# Note: the STDAIR library depends upon BOOST to build.
# Your configure.ac must therefore define appropriately the BOOST
# variables (i.e., BOOST_CFLAGS, BOOST_LIBS, BOOST_DATE_TIME_LIB).
#
# Variables set by this macro:
#  * STDAIR_VERSION
#  * STDAIR_CFLAGS
#  * STDAIR_LIBS
#  * STDAIR_SAMPLE_DIR
#

AC_DEFUN([AM_PATH_STDAIR],
[
AC_LANG_SAVE
AC_LANG([C++])

##
AC_ARG_WITH(stdair,
	[ --with-stdair=PFX Prefix where StdAir is installed (optional) ],
	    stdair_dir="$withval",
	    stdair_dir="")

  if test "x${STDAIR_CONFIG+set}" != xset ; then
     if test "x$stdair_dir" != x ; then
         STDAIR_CONFIG="$stdair_dir/bin/stdair-config"
     fi
  fi

  AC_PATH_PROG(STDAIR_CONFIG, stdair-config, no)

  ## Check whether Boost flags and libraries are defined
  # General Boost compilation flags
  AC_MSG_CHECKING(for BOOST_CFLAGS environment variable)
  if test x"${BOOST_CFLAGS}" = x; then
	AC_MSG_RESULT([Warning: StdAir needs Boost, and the BOOST_CFLAGS environment variable does not appear to be set. It may not be a problem, though, if your Unix distribution is standard, that is, if Boost is installed in /usr. Otherwise, the StdAir will fail to compile.])
  else
	AC_MSG_RESULT([ok (set to ${BOOST_CFLAGS})])
  fi

  # Boost Date-Time library
  AC_MSG_CHECKING(for BOOST_DATE_TIME_LIB environment variable)
  if test x"${BOOST_DATE_TIME_LIB}" = x; then
	AC_MSG_RESULT([Warning: StdAir needs the Boost Date-Time library, and the BOOST_DATE_TIME_LIB environment variable does not appears to be set. The StdAir may fail to link.])
  else
	AC_MSG_RESULT([ok (set to ${BOOST_DATE_TIME_LIB})])
  fi

  # Boost Program Options library
  AC_MSG_CHECKING(for BOOST_PROGRAM_OPTIONS_LIB environment variable)
  if test x"${BOOST_PROGRAM_OPTIONS_LIB}" = x; then
	AC_MSG_RESULT([Warning: StdAir needs the Boost Program Options library, and the BOOST_PROGRAM_OPTIONS_LIB environment variable does not appears to be set. The StdAir may fail to link.])
  else
	AC_MSG_RESULT([ok (set to ${BOOST_PROGRAM_OPTIONS_LIB})])
  fi

  # Boost File System library
  AC_MSG_CHECKING(for BOOST_FILESYSTEM_LIB environment variable)
  if test x"${BOOST_FILESYSTEM_LIB}" = x; then
	AC_MSG_RESULT([Warning: StdAir needs the Boost Date-Time library, and the BOOST_FILESYSTEM_LIB environment variable does not appears to be set. The StdAir may fail to link.])
  else
	AC_MSG_RESULT([ok (set to ${BOOST_FILESYSTEM_LIB})])
  fi

  ## StdAir version
  min_stdair_version=ifelse([$1], ,0.9.0,$1)
  AC_MSG_CHECKING(for StdAir - version >= $min_stdair_version)
  no_stdair=""
  if test "${STDAIR_CONFIG}" = "no" ; then
     no_stdair=yes
     AC_MSG_RESULT([no])
  else
     STDAIR_VERSION=`${STDAIR_CONFIG} --version`
     STDAIR_CFLAGS=`${STDAIR_CONFIG} --cflags`
     STDAIR_CFLAGS="${BOOST_CFLAGS} ${STDAIR_CFLAGS}"
     STDAIR_LIBS=`${STDAIR_CONFIG} --libs`
     STDAIR_LIBS="${BOOST_LIBS} ${BOOST_DATE_TIME_LIB} ${STDAIR_LIBS}"
     STDAIR_SAMPLE_DIR=`${STDAIR_CONFIG} --sampledir`

     AC_SUBST([STDAIR_VERSION])
     AC_SUBST([STDAIR_CFLAGS])
     AC_SUBST([STDAIR_LIBS])
     AC_SUBST([STDAIR_SAMPLE_DIR])

    stdair_major_version=`echo ${STDAIR_VERSION} | sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${stdair_major_version}" = "x" ; then
       stdair_major_version=0
    fi

    stdair_minor_version=`echo ${STDAIR_VERSION} | \
						sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${stdair_minor_version}" = "x" ; then
       stdair_minor_version=0
    fi

    stdair_micro_version=`echo ${STDAIR_VERSION} | \
          sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${stdair_micro_version}" = "x" ; then
       stdair_micro_version=0
    fi

    ## Simple test of compilation and link
    SAVED_CPPFLAGS="${CPPFLAGS}"
    SAVED_LDFLAGS="${LDFLAGS}"
    CPPFLAGS="${CPPFLAGS} ${BOOST_CFLAGS} ${STDAIR_CFLAGS}"
    LDFLAGS="${LDFLAGS} ${STDAIR_LIBS}"


    AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM([[#include <stdair/STDAIR_Service.hpp>
				]],
				[[int i=0;]]
		)]
		,

    	[AC_MSG_RESULT([yes (${STDAIR_VERSION})])],

	[AC_MSG_ERROR([We could not compile a simple StdAir example. See config.log.])]
    )

    CPPFLAGS="${SAVED_CPPFLAGS}"
    LDFLAGS="${SAVED_LDFLAGS}"

  fi

AC_LANG_RESTORE
])
