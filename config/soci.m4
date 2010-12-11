dnl @synopsis AX_SOCI
dnl 
dnl This macro tries to find Soci C API header and library locations.
dnl
dnl We define the following configure script flags:
dnl
dnl		--with-soci: Give prefix for both library and headers, and try
dnl			to guess subdirectory names for each.  (e.g. Tack /lib and
dnl			/include onto given dir name, and other common schemes.)
dnl		--with-soci-lib: Similar to --with-soci, but for library only.
dnl		--with-soci-include: Similar to --with-soci, but for headers
dnl			only.
dnl
dnl @version 1.2, 2007/02/20
dnl @author Warren Young <socipp@etr-usa.com>

AC_DEFUN([AX_SOCI],
[
	#
	# Set up configure script macros
	#
	AC_ARG_WITH(soci,
		[  --with-soci=<path>     root directory path of Soci installation],
		[SOCI_lib_check="$with_soci/lib64/soci $with_soci/lib/soci $with_soci/lib64 $with_soci/lib"
		SOCI_inc_check="$with_soci/include $with_soci/include/soci"
		SOCI_bin_check="$with_soci/bin"],
		[SOCI_lib_check="/usr/lib64 /usr/lib /usr/lib64/soci /usr/lib/soci /usr/local/lib64 /usr/local/lib /usr/local/lib/soci /usr/local/soci/lib /usr/local/soci/lib/soci /opt/soci/lib /opt/soci/lib/soci"
		SOCI_inc_check="/usr/include /usr/include/soci /usr/local/include/soci /usr/local/soci/include /usr/local/soci/include/soci /opt/soci/include /opt/soci/include/soci"
		SOCI_bin_check="/usr/bin /usr/local/bin /usr/local/soci/bin /opt/bin /opt/soci/bin /opt/bin/soci"])

	AC_ARG_WITH(soci-lib,
		[  --with-soci-lib=<path> directory path of Soci library installation],
		[SOCI_lib_check="$with_soci_lib $with_soci_lib/lib64 $with_soci_lib/lib $with_soci_lib/lib64/soci $with_soci_lib/lib/soci"])

	AC_ARG_WITH(soci-include,
		[  --with-soci-include=<path> directory path of Soci header installation],
		[SOCI_inc_check="$with_soci_include $with_soci_include/include $with_soci_include/include/soci"])

    #
	# Look for Soci Configuration Script
	#
	AC_MSG_CHECKING([for Soci configuration script])
	SOCI_CONFIG=
	SOCI_bindir=
	for m in $SOCI_bin_check
		do
			if test -d "$m" && test -f "$m/soci-config"
			then
				SOCI_CONFIG=$m/soci-config
				SOCI_bindir=$m
			break
		fi
	done

#	if test -z "$SOCI_bindir"
#	then
#		AC_MSG_ERROR([Didn't find $SOCI_CONFIG binary in '$SOCI_bin_check'])
#	fi

#	case "$SOCI_bindir" in
#		/* ) ;;
#		* )  AC_MSG_ERROR([The Soci binary directory ($SOCI_bindir) must be an absolute path.]) ;;
#	esac

	AC_MSG_RESULT([$SOCI_CONFIG])

#	AC_PATH_PROG(SOCI_CONFIG, soci-config, $SOCI_bindir)

	if test "x${SOCI_CONFIG}1" != "x1"
	then
		SOCI_VERSION=`${SOCI_CONFIG} --version`
	fi

	# SOCI library
	SOCI_CORE_LIB=soci_core
	SOCI_MYSQL_LIB=soci_mysql
	SOCI_LIB_SUFFIX=gcc-3_0

	#
	# Look for Soci Core API library
	#
	AC_MSG_CHECKING([for Soci library directory])
	SOCI_libdir=
	for m in $SOCI_lib_check
	do
		if test -d "$m"
		then
			for socilib in "$SOCI_CORE_LIB $SOCI_CORE_LIB-${SOCI_LIB_SUFFIX}"
			do
				if (test -f "$m/lib$SOCI_CORE_LIB.so" || test -f "$m/lib$SOCI_CORE_LIB.a")
				then
					SOCI_libdir=$m
					break
				fi
				if (test -f "$m/lib${SOCI_CORE_LIB}-${SOCI_LIB_SUFFIX}.so" \
				|| test -f "$m/lib${SOCI_CORE_LIB}-${SOCI_LIB_SUFFIX}.a")
				then
					SOCI_CORE_LIB=${SOCI_CORE_LIB}-${SOCI_LIB_SUFFIX}
					SOCI_MYSQL_LIB=${SOCI_MYSQL_LIB}-${SOCI_LIB_SUFFIX}
					SOCI_libdir=$m
					break
				fi
			done
		fi
	done

	if test -z "$SOCI_libdir"
	then
		AC_MSG_ERROR([Didn't find $SOCI_CORE_LIB library in '$SOCI_lib_check'])
	fi

	case "$SOCI_libdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Soci library directory ($SOCI_libdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([$SOCI_libdir])

#	case "$SOCI_libdir" in
#	  /usr/lib) ;;
#	  *) LDFLAGS="$LDFLAGS -L${SOCI_libdir}" ;;
#	esac


	SOCI_areHeadersBuried=

	#
	# Look for Soci Core API headers (case of buried headers)
	#
	AC_MSG_CHECKING([for Soci include directory])
	SOCI_incdir=
	for m in $SOCI_inc_check
	do
		if test -d "$m" && test -f "$m/soci/core/soci.h"
		then
			SOCI_incdir=$m
			SOCI_areHeadersBuried=true
			break
		fi
	done

	#
	# if Soci Code API headers not found, look for non-buried headers
	#

	if test -z "$SOCI_incdir"
	then
		for m in $SOCI_inc_check
		do
			if test -d "$m" && test -f "$m/soci.h"
			then
				SOCI_incdir=$m
				break
			fi
		done
	fi	

	if test -z "$SOCI_incdir"
	then
		AC_MSG_ERROR([Didn't find the Soci include dir in '$SOCI_inc_check'])
	fi

	case "$SOCI_incdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Soci include directory ($SOCI_incdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([$SOCI_incdir])

	if test "$SOCI_incdir" != "/usr/include"
	then
		SOCI_CFLAGS="-I${SOCI_incdir}"
	fi
	if test "$SOCI_libdir" != "/usr/lib" -a "$SOCI_libdir" != "/usr/lib64"
	then
		SOCI_LIBS="-L${SOCI_libdir}"
	fi
	
	if test "$SOCI_areHeadersBuried" = true
	then
		AC_MSG_RESULT(Soci headers are buried.)
		SOCI_CFLAGS="-DSOCI_HEADERS_BURIED -DSOCI_MYSQL_HEADERS_BURIED ${SOCI_CFLAGS}"
	fi

        SOCI_CFLAGS="${MYSQL_CFLAGS} ${SOCI_CFLAGS}"

	SOCI_LIBS="${MYSQL_LIBS} ${SOCI_LIBS} -l${SOCI_CORE_LIB} -l${SOCI_MYSQL_LIB} -ldl"
	AC_SUBST(SOCI_CFLAGS)
	AC_SUBST(SOCI_LIBS)

# Test linking with soci (note that it needs MySQL client to have been defined
# before)
	save_LIBS="$LIBS"
	if test -z "$MYSQL_LIBS"
	then
		MYSQL_LIBS="-L/usr/lib64/mysql -L/usr/lib/mysql -lmysqlclient"
	fi
	LIBS="$LIBS $MYSQL_LIBS $SOCI_LIBS"
	AC_CHECK_LIB($SOCI_CORE_LIB, soci_begin,
                 [], 
                 [AC_MSG_ERROR([Could not find working Soci client library!])]
                )
	LIBS="$save_LIBS"
	AC_SUBST(SOCI_CORE_LIB)
]) dnl AX_SOCI
