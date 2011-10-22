dnl @synopsis AX_MPICH2
dnl 
dnl This macro tries to find Mpich2 C API header and library locations.
dnl
dnl We define the following configure script flags:
dnl
dnl		--with-mpich2: Give prefix for both library and headers, and try
dnl			to guess subdirectory names for each.  (e.g. Tack /lib and
dnl			/include onto given dir name, and other common schemes.)
dnl		--with-mpich2-lib: Similar to --with-mpich2, but for library only.
dnl		--with-mpich2-include: Similar to --with-mpich2, but for headers
dnl			only.
dnl
dnl @version 1.0, 2009/10/08
dnl @author Denis Arnaud <denis.arnaud_fedora@m4x.org>

AC_DEFUN([AX_MPICH2],
[

dnl
dnl Check the CPU (and OS) architecture: 32 or 64 bits
dnl
ARCH=`arch`
if test "${ARCH}" = "i386" -o "${ARCH}" = "i686" -o "${ARCH}" = "ppc" -o "${ARCH}" = "sparcv9"
then
   MODE=32
   MODEFLAG="-m32"
elif test "${ARCH}" = "ia64"
then
   MODE=64
elif test "${ARCH}" = "s390"
then
   MODE=31
elif test "${ARCH}" = "s390x"
then
   MODE=64
elif test "${ARCH}" = "x86_64" -o "${ARCH}" = "ppc64" -o "${ARCH}" = "sparc64"
then
   MODE=64
   MODEFLAG="-m64"
fi

GENARCH="${ARCH}"
if test "${ARCH}" = "i686"
then
  GENARCH="i386" 
fi

MPICH2_DEF_VERSION="1.3.3"
MPICH2_DEF_CC="gcc"
MPIDIR="${MPICH2_DEF_VERSION}-${MPICH2_DEF_CC}"

	#
	# Set up configure script macros
	#
	AC_ARG_WITH(mpich2,
		[  --with-mpich2=<path>    root directory path of Mpich2 installation],
		[MPICH2_lib_check="$with_mpich2/lib${MODE}/mpich2 $with_mpich2/lib/mpich2 $with_mpich2/lib${MODE} $with_mpich2/lib"
		MPICH2_inc_check="$with_mpich2/include $with_mpich2/include/mpich2 $with_mpich2/include/mpich2/${MPIDIR}"
		MPICH2_bin_check="$with_mpich2/bin $with_mpich2/lib${MODE}/mpich2/bin $with_mpich2/lib/mpich2/bin $with_mpich2/lib${MODE}/bin $with_mpich2/lib/bin"],
		[MPICH2_lib_check="/usr/lib${MODE} /usr/lib /usr/lib${MODE}/mpich2 /usr/lib/mpich2 /usr/lib${MODE}/mpich2/lib /usr/lib/mpich2/lib /usr/lib${MODE}/mpich2/${MPIDIR} /usr/lib/mpich2/${MPIDIR} /usr/local/lib${MODE} /usr/local/lib /usr/local/lib${MODE}/mpich2 /usr/local/lib/mpich2 /usr/local/lib${MODE}/mpich2/${MPIDIR} /usr/local/lib/mpich2/${MPIDIR} /usr/local/mpich2/lib${MODE} /usr/local/mpich2/lib /usr/local/mpich2/${MPIDIR}/lib${MODE} /usr/local/mpich2/${MPIDIR}/lib /opt/mpich2/lib /opt/mpich2/${MPIDIR}/lib /opt/mpich2/lib/mpich2"
		MPICH2_inc_check="/usr/include /usr/include/mpich2 /usr/include/mpich2-${ARCH} /usr/include/mpich2-${GENARCH} /usr/include/mpich2/${MPIDIR} /usr/local/include /usr/local/include/mpich2 /usr/local/include/mpich2/${MPIDIR} /opt/mpich2/include /opt/mpich2/${MPIDIR}/include"
		MPICH2_bin_check="/usr/lib${MODE}/bin /usr/lib/bin /usr/lib${MODE}/mpich2/bin /usr/lib/mpich2/bin /usr/lib${MODE}/mpich2/lib/bin /usr/lib/mpich2/lib/bin /usr/lib${MODE}/mpich2/${MPIDIR}/bin /usr/lib/mpich2/${MPIDIR}/bin /usr/local/lib${MODE}/bin /usr/local/lib/bin /usr/local/lib${MODE}/mpich2/bin /usr/local/lib/mpich2/bin /usr/local/lib${MODE}/mpich2/${MPIDIR}/bin /usr/local/lib/mpich2/${MPIDIR}/bin /usr/local/mpich2/lib${MODE}/bin /usr/local/mpich2/lib/bin /usr/local/mpich2/${MPIDIR}/lib${MODE}/bin /usr/local/mpich2/${MPIDIR}/lib/bin /opt/mpich2/lib/bin /opt/mpich2/${MPIDIR}/lib/bin /opt/mpich2/lib/mpich2/bin"])

	AC_ARG_WITH(mpich2-lib,
		[  --with-mpich2-lib=<path> directory path of Mpich2 library installation],
		[MPICH2_lib_check="$with_mpich2_lib $with_mpich2_lib/lib${MODE} $with_mpich2_lib/lib $with_mpich2_lib/lib${MODE}/mpich2 $with_mpich2_lib/lib/mpich2 $with_mpich2_lib/lib${MODE}/mpich2/${MPIDIR} $with_mpich2_lib/lib/mpich2/${MPIDIR}"])

	AC_ARG_WITH(mpich2-include,
		[  --with-mpich2-include=<path> directory path of Mpich2 header installation],
		[MPICH2_inc_check="$with_mpich2_include $with_mpich2_include/include $with_mpich2_include/include/mpich2 $with_mpich2_include/include/mpich2/${MPIDIR}"])

	# Mpich2 library
	MPICH2_LIB=mpichcxx
	MPICH2_LIBC=mpich

	#
	# Look for Mpich2 library
	#
	AC_MSG_CHECKING([for Mpich2 library directory])
	MPICH2_libdir=
	for m in ${MPICH2_lib_check}
	do
		if test -d "$m"
		then
			if (test -f "$m/lib$MPICH2_LIB.so" || test -f "$m/lib$MPICH2_LIB.a")
			then
				MPICH2_libdir=$m
				break
			fi
		fi
	done

	if test -z "$MPICH2_libdir"
	then
		AC_MSG_ERROR([Did not find $MPICH2_LIB library in '$MPICH2_lib_check'])
	fi

	case "$MPICH2_libdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Mpich2 library directory ($MPICH2_libdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([$MPICH2_libdir])

	#
	# Look for Mpich2 headers
	#
	AC_MSG_CHECKING([for Mpich2 include directory])
	MPICH2_incdir=
	for m in ${MPICH2_inc_check}
	do
		if test -d "$m" && test -f "$m/mpi.h"
		then
			MPICH2_incdir=$m
			break
		fi
	done

	if test -z "$MPICH2_incdir"
	then
		AC_MSG_ERROR([Did not find the Mpich2 include dir in '$MPICH2_inc_check'])
	fi

	case "$MPICH2_incdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Mpich2 include directory ($MPICH2_incdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([$MPICH2_incdir])

	#
	# Look for Mpich2 configuration
	#
	# Mpich2 configuration binary
	MPICH2_VERBIN=mpich2version

	AC_MSG_CHECKING([for Mpich2 configuration])
	MPICH2_verdir=
	for m in ${MPICH2_bin_check}
	do
		if test -d "$m"
		then
			if (test -x "$m/$MPICH2_VERBIN")
			then
				MPICH2_verdir=$m
				break
			fi
		fi
	done

	if test -z "$MPICH2_verdir"
	then
		AC_MSG_RESULT([Did not find $MPICH2_VERBIN tool, but will try to determine the version with other tricks])
	else
		case "$MPICH2_verdir" in
			/* ) ;;
			* )  AC_MSG_ERROR([The Mpich2 tool directory ($MPICH2_verdir) must be an absolute path.]) ;;
		esac
	fi

	AC_MSG_RESULT([$MPICH2_verdir])

	#
	# Look for Mpich2 version
	#
	min_mpich2_version=ifelse([$1], , 1.0.0, $1)
	AC_MSG_CHECKING([for Mpich2 version >= $min_mpich2_version])

	# Derive the full version, e.g., 1.2.1
	if test ! -z "$MPICH2_verdir"
	then
		MPICH2_VERSION=`${MPICH2_verdir}/${MPICH2_VERBIN} --version | cut -f2`
	fi
	if test -z "${MPICH2_VERSION}" ; then
	   MPICH2_VERSION=${MPICH2_DEF_VERSION}
	fi

	# Calculation of major, minor, micro
    mpich2_major_version=`echo $MPICH2_VERSION | sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${mpich2_major_version}" = "x" ; then
       mpich2_major_version=0
    fi

    mpich2_minor_version=`echo $MPICH2_VERSION | \
						sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${mpich2_minor_version}" = "x" ; then
       mpich2_minor_version=0
    fi

    mpich2_micro_version=`echo $MPICH2_VERSION | \
          sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${mpich2_micro_version}" = "x" ; then
       mpich2_micro_version=0
    fi
	
	AC_MSG_RESULT([$MPICH2_VERSION])

	#
	# Derive the flags for compilation and linking
	#
	MPICH2_CFLAGS="-I${MPICH2_incdir} ${MODEFLAG}"
	MPICH2_LIBS="-L${MPICH2_libdir} -lmpichcxx -lmpich"

	#
	# Make the changes permanent
	#
	HAVE_MPICH2=1
	MPIGEN_VERSION=${MPICH2_VERSION}
	MPIGEN_CFLAGS=${MPICH2_CFLAGS}
	MPIGEN_LIBS=${MPICH2_LIBS}
	AC_SUBST(MPICH2_VERSION)
	AC_SUBST(MPICH2_CFLAGS)
	AC_SUBST(MPICH2_LIBS)

	# Test linking with mpich2
	save_LIBS="$LIBS"
	if test -z "$MPICH2_LIBS"
	then
		MPICH2_LIBS="-L/usr/lib${MODE}/mpich2 -lmpichcxx -lmpich"
	fi
	LIBS="$LIBS $MPICH2_LIBS"
	AC_CHECK_LIB($MPICH2_LIBC, MPID_Comm_direct,
                 [], 
                 [AC_MSG_ERROR([Could not find working Mpich2 library!])]
                )
	LIBS="$save_LIBS"
]) dnl AX_MPICH2
