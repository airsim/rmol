# Configure path for the GSL library.
# Denis Arnaud <denis_arnaud@users.sourceforge.net>, May 2007


AC_DEFUN([AM_PATH_GSL],
[

AC_ARG_WITH(gsl,
	[ --with-gsl=PFX   Prefix where GSL is installed (optional)],
    gsl_dir="$withval",
	gsl_dir="")

  if test "x${GSL_CONFIG+set}" != xset ; then
     if test "x$gsl_dir" != x ; then
         GSL_CONFIG="$gsl_dir/bin/gsl-config"
     fi
  fi

  AC_PATH_PROG(GSL_CONFIG, gsl-config, no)

  min_gsl_version=ifelse([$1], ,0.11.0,$1)
  AC_MSG_CHECKING(for GSL - version >= $min_gsl_version)
  no_gsl=""
  if test "$GSL_CONFIG" = "no" ; then
    no_gsl=yes
	AC_MSG_RESULT([no])
  else
	GSL_VERSION=`$GSL_CONFIG --version`
    GSL_CFLAGS=`$GSL_CONFIG --cflags`
    GSL_LIBS=`$GSL_CONFIG --libs`

	AC_SUBST([GSL_VERSION])
	AC_SUBST([GSL_CFLAGS])
	AC_SUBST([GSL_LIBS])

    gsl_major_version=`echo $GSL_VERSION | sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${gsl_major_version}" = "x" ; then
       gsl_major_version=0
    fi

    gsl_minor_version=`echo $GSL_VERSION | \
						sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${gsl_minor_version}" = "x" ; then
       gsl_minor_version=0
    fi

    gsl_micro_version=`echo $GSL_VERSION | \
          sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${gsl_micro_version}" = "x" ; then
       gsl_micro_version=0
    fi


	SAVED_CPPFLAGS="$CPPFLAGS"
	SAVED_LDFLAGS="$LDFLAGS"
	CPPFLAGS="$CPPFLAGS $GSL_CFLAGS"
	LDFLAGS="$LDFLAGS $GSL_LIBS"


   	AC_COMPILE_IFELSE(
		AC_LANG_PROGRAM([[
				#include <gsl/gsl_types.h> 
				]],
				[[int i=0;]]
		)
		,

    	[AC_MSG_RESULT([yes ($GSL_VERSION)])],

		[
		AC_MSG_ERROR([We could not compile a simple GSL example. See config.log.])
		]
	)

	CPPFLAGS="$SAVED_CPPFLAGS"
	LDFLAGS="$SAVED_LDFLAGS"

  fi
])
