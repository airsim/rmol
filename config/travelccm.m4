#
# Configure path for the TRAVELCCM library.
# Denis Arnaud <denis_arnaud@users.sourceforge.net>, July 2008
#
# Note: as the TRAVELCCM library depends upon GSL (and
# potentially BOOST) to build. Your configure.ac must define
# appropriately the GSL_CFLAGS (and potentially BOOST_CFLAGS)
# variables.
#


AC_DEFUN([AM_PATH_TRAVELCCM],
[
AC_LANG_SAVE
AC_LANG([C++])

AC_ARG_WITH(travelccm,
	[ --with-travelccm=PFX   Prefix where TRAVELCCM is installed (optional)],
    travelccm_dir="$withval",
	travelccm_dir="")

  if test "x${TRAVELCCM_CONFIG+set}" != xset ; then
     if test "x$travelccm_dir" != x ; then
         TRAVELCCM_CONFIG="$travelccm_dir/bin/travelccm-config"
     fi
  fi

  AC_PATH_PROG(TRAVELCCM_CONFIG, travelccm-config, no)

  # Check whether Boost flags and libraries are defined
  AC_MSG_CHECKING(for GSL_CFLAGS environment variable)
  if test x"${GSL_CFLAGS}" = x; then
	AC_MSG_RESULT([Warning: TRAVELCCM needs the GSL, and the GSL_CFLAGS environment variable does not appear to be set. It may not be a problem, though, if your Unix distribution is standard, that is, if GSL is installed in /usr/local. Otherwise, the TRAVELCCM will fail to compile.])
	else
	AC_MSG_RESULT([ok (set to ${GSL_CFLAGS})])
  fi

  AC_MSG_CHECKING(for GSL_LIBS environment variable)
  if test x"${GSL_LIBS}" = x; then
	AC_MSG_RESULT([Warning: TRAVELCCM needs the GSL library, and the GSL_LIBS environment variable does not appears to be set. The TRAVELCCM may fail to link.])
	else
	AC_MSG_RESULT([ok (set to ${GSL_LIBS})])
  fi

  # Check whether Boost flags and libraries are defined
#  AC_MSG_CHECKING(for BOOST_CFLAGS environment variable)
#  if test x"${BOOST_CFLAGS}" = x; then
#	AC_MSG_RESULT([Warning: TRAVELCCM needs Boost, and the BOOST_CFLAGS environment variable does not appear to be set. It may not be a problem, though, if your Unix distribution is standard, that is, if Boost is installed in /usr/local. Otherwise, the TRAVELCCM will fail to compile.])
#	else
#	AC_MSG_RESULT([ok (set to ${BOOST_CFLAGS})])
#  fi

#  AC_MSG_CHECKING(for BOOST_DATE_TIME_LIB environment variable)
#  if test x"${BOOST_DATE_TIME_LIB}" = x; then
#	AC_MSG_RESULT([Warning: TRAVELCCM needs Boost Date-Time library, and the BOOST_DATE_TIME_LIB environment variable does not appears to be set. The TRAVELCCM may fail to link.])
#	else
#	AC_MSG_RESULT([ok (set to ${BOOST_DATE_TIME_LIB})])
#  fi

  min_travelccm_version=ifelse([$1], ,0.11.0,$1)
  AC_MSG_CHECKING(for TRAVELCCM - version >= $min_travelccm_version)
  no_travelccm=""
  if test "${TRAVELCCM_CONFIG}" = "no" ; then
    no_travelccm=yes
	AC_MSG_RESULT([no])
  else
	TRAVELCCM_VERSION=`${TRAVELCCM_CONFIG} --version`
    TRAVELCCM_CFLAGS=`${TRAVELCCM_CONFIG} --cflags`
    TRAVELCCM_CFLAGS="${GSL_CFLAGS} ${TRAVELCCM_CFLAGS}"
#    TRAVELCCM_CFLAGS="${BOOST_CFLAGS} ${TRAVELCCM_CFLAGS}"
    TRAVELCCM_LIBS=`${TRAVELCCM_CONFIG} --libs`
    TRAVELCCM_LIBS="${GSL_LIBS} ${TRAVELCCM_LIBS}"
#    TRAVELCCM_LIBS="${BOOST_LIBS} ${BOOST_DATE_TIME_LIB} ${TRAVELCCM_LIBS}"

	AC_SUBST([TRAVELCCM_VERSION])
	AC_SUBST([TRAVELCCM_CFLAGS])
	AC_SUBST([TRAVELCCM_LIBS])

    travelccm_major_version=`echo ${TRAVELCCM_VERSION} | sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${travelccm_major_version}" = "x" ; then
       travelccm_major_version=0
    fi

    travelccm_minor_version=`echo ${TRAVELCCM_VERSION} | \
						sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${travelccm_minor_version}" = "x" ; then
       travelccm_minor_version=0
    fi

    travelccm_micro_version=`echo ${TRAVELCCM_VERSION} | \
          sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${travelccm_micro_version}" = "x" ; then
       travelccm_micro_version=0
    fi


	SAVED_CPPFLAGS="${CPPFLAGS}"
	SAVED_LDFLAGS="${LDFLAGS}"
	CPPFLAGS="${CPPFLAGS} ${GSL_CFLAGS} ${BOOST_CFLAGS} ${TRAVELCCM_CFLAGS}"
	LDFLAGS="${LDFLAGS} ${GSL_LIBS} ${TRAVELCCM_LIBS}"


   	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM([[
				#include <travelccm/TRAVELCCM_Service.hpp> 
				]],
				[[int i=0;]]
		)]
		,

    	[AC_MSG_RESULT([yes (${TRAVELCCM_VERSION})])],

		[
		AC_MSG_ERROR([We could not compile a simple TRAVELCCM example. See config.log.])
		]
	)

	CPPFLAGS="${SAVED_CPPFLAGS}"
	LDFLAGS="${SAVED_LDFLAGS}"

  fi

AC_LANG_RESTORE
])
