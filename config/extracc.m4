#
# Configure path for the EXTRACC library.
# Denis Arnaud <denis_arnaud@users.sourceforge.net>, July 2008
#
# Note: as the EXTRACC library depends upon BOOST to build,
# your configure.ac must define appropriately the BOOST_CFLAGS
# variable.
#


AC_DEFUN([AM_PATH_EXTRACC],
[
	AC_LANG_SAVE
	AC_LANG([C++])

	AC_ARG_WITH(extracc,
		[ --with-extracc=PFX   Prefix where EXTRACC is installed (optional, default /usr/local)],
		extracc_dir_check="$withval",
		extracc_dir_check="/usr/local /usr")

        AC_MSG_CHECKING([for Extracc configuration script])
        extracc_dir=
        for m in $extracc_dir_check
                do
			echo "test $m"
                        if test -x "$m/bin/extracc-config"
                        then
                                extracc_dir=$m
                        break
                fi
        done


	EXTRACC_CONFIG="$extracc_dir/bin/extracc-config"

	AS_IF([test -x "$EXTRACC_CONFIG"],
		[],
		[AC_MSG_FAILURE([--with-extracc must be a valid directory where EXTRACC is installed (default /usr/local /usr)])])

	EXTRACC_VERSION=`$EXTRACC_CONFIG --version`
	EXTRACC_CFLAGS=`$EXTRACC_CONFIG --cflags`
	EXTRACC_LIBS=`$EXTRACC_CONFIG --libs`

	AC_SUBST([EXTRACC_VERSION])
	AC_SUBST([EXTRACC_CFLAGS])
	AC_SUBST([EXTRACC_LIBS])
	
	EXTRACC_EXTRACPPUNIT_INCLUDE=`$EXTRACC_CONFIG --extracppunit-makefile-include`
	AC_SUBST([EXTRACC_EXTRACPPUNIT_INCLUDE])

	extracc_major_version=`echo $EXTRACC_VERSION | sed 's/^\([[0-9]]*\).*/\1/'`
	if test "x${extracc_major_version}" = "x" ; then
		extracc_major_version=0
	fi

	extracc_minor_version=`echo $EXTRACC_VERSION | \
						sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
	if test "x${extracc_minor_version}" = "x" ; then
		extracc_minor_version=0
	fi

	extracc_micro_version=`echo $EXTRACC_VERSION | \
	sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
	if test "x${extracc_micro_version}" = "x" ; then
		extracc_micro_version=0
	fi

AC_LANG_RESTORE
])
