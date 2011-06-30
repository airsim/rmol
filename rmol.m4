# Configure path for the RMOL library.
# Denis Arnaud <denis_arnaud@users.sourceforge.net>, May 2007


AC_DEFUN([AM_PATH_RMOL],
[

AC_ARG_WITH(rmol,
	[ --with-rmol=PFX   Prefix where RMOL is installed (optional)],
    rmol_dir="$withval",
	rmol_dir="")

  if test "x${RMOL_CONFIG+set}" != xset ; then
     if test "x$rmol_dir" != x ; then
         RMOL_CONFIG="$rmol_dir/bin/rmol-config"
     fi
  fi

  AC_PATH_PROG(RMOL_CONFIG, rmol-config, no)

  min_rmol_version=ifelse([$1], ,0.11.0,$1)
  AC_MSG_CHECKING(for RMOL - version >= $min_rmol_version)
  no_rmol=""
  if test "$RMOL_CONFIG" = "no" ; then
    no_rmol=yes
	AC_MSG_RESULT([no])
  else
	RMOL_VERSION=`$RMOL_CONFIG --version`
    RMOL_CFLAGS=`$RMOL_CONFIG --cflags`
    RMOL_LIBS=`$RMOL_CONFIG --libs`

	AC_SUBST([RMOL_VERSION])
	AC_SUBST([RMOL_CFLAGS])
	AC_SUBST([RMOL_LIBS])

    rmol_major_version=`echo $RMOL_VERSION | sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${rmol_major_version}" = "x" ; then
       rmol_major_version=0
    fi

    rmol_minor_version=`echo $RMOL_VERSION | \
						sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${rmol_minor_version}" = "x" ; then
       rmol_minor_version=0
    fi

    rmol_micro_version=`echo $RMOL_VERSION | \
          sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${rmol_micro_version}" = "x" ; then
       rmol_micro_version=0
    fi


	SAVED_CPPFLAGS="$CPPFLAGS"
	SAVED_LDFLAGS="$LDFLAGS"
	CPPFLAGS="$CPPFLAGS $RMOL_CFLAGS"
	LDFLAGS="$LDFLAGS $RMOL_LIBS"


   	AC_COMPILE_IFELSE(
		[AC_LANG_PROGRAM([[
				#include <rmol/RMOL_Service.hpp> 
				]],
				[[int i=0;]]
		)]
		,

    	[AC_MSG_RESULT([yes ($RMOL_VERSION)])],

		[
		AC_MSG_ERROR([We could not compile a simple RMOL example. See config.log.])
		]
	)

	CPPFLAGS="$SAVED_CPPFLAGS"
	LDFLAGS="$SAVED_LDFLAGS"

  fi
])
