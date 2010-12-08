dnl @synopsis AX_ICU
dnl 
dnl This macro tries to find Icu C API header and library locations.
dnl
dnl We define the following configure script flags:
dnl
dnl		--with-icu: Give prefix for both library and headers, and try
dnl			to guess subdirectory names for each.  (e.g. Tack /lib and
dnl			/include onto given dir name, and other common schemes.)
dnl		--with-icu-lib: Similar to --with-icu, but for library only.
dnl		--with-icu-include: Similar to --with-icu, but for headers
dnl			only.
dnl
dnl @version 1.2, 2007/02/20
dnl @author Warren Young <icupp@etr-usa.com>

AC_DEFUN([AX_ICU],
[
	#
	# Set up configure script macros
	#
	AC_ARG_WITH(icu,
		[  --with-icu=<path>     root directory path of Icu installation],
		[ICU_lib_check="$with_icu/lib64/icu $with_icu/lib/icu $with_icu/lib64 $with_icu/lib"
		ICU_inc_check="$with_icu/include $with_icu/include/icu"
		ICU_bin_check="$with_icu/bin"],
		[ICU_lib_check="/usr/lib64 /usr/lib /usr/lib64/icu /usr/lib/icu /usr/local/lib64 /usr/local/lib /usr/local/lib/icu /usr/local/icu/lib /usr/local/icu/lib/icu /opt/icu/lib /opt/icu/lib/icu"
		ICU_inc_check="/usr/include /usr/local/include /usr/local/icu/include /opt/icu/include"
		ICU_bin_check="/usr/bin /usr/local/bin /usr/local/icu/bin"])

	AC_ARG_WITH(icu-lib,
		[  --with-icu-lib=<path> directory path of Icu library installation],
		[ICU_lib_check="$with_icu_lib $with_icu_lib/lib64 $with_icu_lib/lib $with_icu_lib/lib64/icu $with_icu_lib/lib/icu"])

	AC_ARG_WITH(icu-include,
		[  --with-icu-include=<path> directory path of Icu header installation],
		[ICU_inc_check="$with_icu_include $with_icu_include/include $with_icu_include/include/icu"])


    #
	# Look for Icu Configuration Script
	#
	AC_MSG_CHECKING([for Icu configuration script])
	ICU_CONFIG=
	ICU_bindir=
	for m in $ICU_bin_check
		do
			if test -d "$m" && test -f "$m/icu-config"
			then
				ICU_CONFIG=$m/icu-config
				ICU_bindir=$m
			break
		fi
	done

	if test -z "$ICU_bindir"
	then
		AC_MSG_ERROR([Didn't find $ICU_CONFIG binary in '$ICU_bin_check'])
	fi

	case "$ICU_bindir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Icu binary directory ($ICU_bindir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([$ICU_bindir])

	AC_PATH_PROG(ICU_CONFIG, icu-config, $ICU_bindir)

	if test "x${ICU_CONFIG+set}" != xset
	then
		ICU_VERSION=`${ICU_CONFIG} --version`
		ICU_CFLAGS=`${ICU_CONFIG} --cppflags`
		ICU_LIBS=`${ICU_CONFIG} --ldflags`
	else
		#
		# Look for Icu C API library
		#
		AC_MSG_CHECKING([for Icu library directory])
		ICU_libdir=
		ICU_IO_LIB=icuio
		for m in $ICU_lib_check
		do
			if test -d "$m" && \
				(test -f "$m/lib$ICU_IO_LIB.so" \
				|| test -f "$m/lib$ICU_IO_LIB.a")
			then
				ICU_libdir=$m
				break
			fi
		done

		if test -z "$ICU_libdir"
		then
			AC_MSG_ERROR([Didn't find $ICU_IO_LIB library in '$ICU_lib_check'])
		fi

		case "$ICU_libdir" in
			/* ) ;;
			* )  AC_MSG_ERROR([The Icu library directory ($ICU_libdir) must be an absolute path.]) ;;
		esac

		AC_MSG_RESULT([$ICU_libdir])

		case "$ICU_libdir" in
		  /usr/lib64) ;;
		  /usr/lib) ;;
		  *) LDFLAGS="$LDFLAGS -L${ICU_libdir}" ;;
		esac

		#
		# Look for Icu C API headers
		#
		AC_MSG_CHECKING([for Icu include directory])
		ICU_incdir=
		for m in $ICU_inc_check
		do
			if test -d "$m" && test -f "$m/unicode/utf8.h"
			then
				ICU_incdir=$m
				break
			fi
		done

		if test -z "$ICU_incdir"
		then
			AC_MSG_ERROR([Didn't find the Icu include dir in '$ICU_inc_check'])
		fi

		case "$ICU_incdir" in
			 /* ) ;;
			 * )  AC_MSG_ERROR([The Icu include directory ($ICU_incdir) must be an absolute path.]) ;;
		esac

		AC_MSG_RESULT([$ICU_incdir])

		ICU_CFLAGS="-D_REENTRANT -I${ICU_incdir}"
		ICU_LIBS="-licui18n -licuuc -licudata -lpthread -lm"

		case "$ICU_libdir" in
		  /usr/lib64) ;;
		  /usr/lib) ;;
		  *) ICU_LIBS="-L${ICU_libdir} $ICU_LIBS" ;;
		esac
	fi

	AC_SUBST(ICU_VERSION)
	AC_SUBST(ICU_CFLAGS)
	AC_SUBST(ICU_LIBS)

	save_LIBS="$LIBS"
	LIBS="$LIBS $ICU_LIBS"
#	AC_CHECK_LIB($ICU_IO_LIB, utext_isWritable,
#       			[], 
#               	[AC_MSG_ERROR([Could not find working Icu client library!])]
#               	)
	ICU_IO_LIB="-l${ICU_IO_LIB}"
	AC_SUBST(ICU_IO_LIB)
	LIBS="$save_LIBS"
]) dnl AX_ICU
