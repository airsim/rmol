dnl @synopsis AX_OPENMPI
dnl 
dnl This macro tries to find Openmpi C API header and library locations.
dnl
dnl We define the following configure script flags:
dnl
dnl		--with-openmpi: Give prefix for both library and headers, and try
dnl			to guess subdirectory names for each.  (e.g. Tack /lib and
dnl			/include onto given dir name, and other common schemes.)
dnl		--with-openmpi-lib: Similar to --with-openmpi, but for library only.
dnl		--with-openmpi-include: Similar to --with-openmpi, but for headers
dnl			only.
dnl
dnl @version 1.0, 2009/10/08
dnl @author Denis Arnaud <denis.arnaud_fedora@m4x.org>

AC_DEFUN([AX_OPENMPI],
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

OPENMPI_DEF_VERSION="1.3.3"
OPENMPI_DEF_CC="gcc"
MPIDIR="${OPENMPI_DEF_VERSION}-${OPENMPI_DEF_CC}"

	#
	# Set up configure script macros
	#
	AC_ARG_WITH(openmpi,
		[  --with-openmpi=<path>    root directory path of Openmpi installation],
		[OPENMPI_lib_check="$with_openmpi/lib${MODE}/openmpi $with_openmpi/lib/openmpi $with_openmpi/lib${MODE} $with_openmpi/lib"
		OPENMPI_inc_check="$with_openmpi/include $with_openmpi/include/openmpi $with_openmpi/include/openmpi/${MPIDIR}"],
		[OPENMPI_lib_check="/usr/lib${MODE} /usr/lib /usr/lib${MODE}/openmpi /usr/lib/openmpi /usr/lib${MODE}/openmpi/lib /usr/lib/openmpi/lib /usr/lib${MODE}/openmpi/${MPIDIR} /usr/lib/openmpi/${MPIDIR} /usr/local/lib${MODE} /usr/local/lib /usr/local/lib${MODE}/openmpi /usr/local/lib/openmpi /usr/local/lib${MODE}/openmpi/${MPIDIR} /usr/local/lib/openmpi/${MPIDIR} /usr/local/openmpi/lib${MODE} /usr/local/openmpi/lib /usr/local/openmpi/${MPIDIR}/lib${MODE} /usr/local/openmpi/${MPIDIR}/lib$ /opt/openmpi/lib /opt/openmpi/${MPIDIR}/lib /opt/openmpi/lib/openmpi"
		OPENMPI_inc_check="/usr/include /usr/include/openmpi /usr/include/openmpi-${ARCH} /usr/include/openmpi-${GENARCH} /usr/include/openmpi/${MPIDIR} /usr/local/include /usr/local/include/openmpi /usr/local/include/openmpi/${MPIDIR} /opt/openmpi/include /opt/openmpi/${MPIDIR}/include"])

	AC_ARG_WITH(openmpi-lib,
		[  --with-openmpi-lib=<path> directory path of Openmpi library installation],
		[OPENMPI_lib_check="$with_openmpi_lib $with_openmpi_lib/lib${MODE} $with_openmpi_lib/lib $with_openmpi_lib/lib${MODE}/openmpi $with_openmpi_lib/lib/openmpi $with_openmpi_lib/lib${MODE}/openmpi/${MPIDIR} $with_openmpi_lib/lib/openmpi/${MPIDIR}"])

	AC_ARG_WITH(openmpi-include,
		[  --with-openmpi-include=<path> directory path of Openmpi header installation],
		[OPENMPI_inc_check="$with_openmpi_include $with_openmpi_include/include $with_openmpi_include/include/openmpi $with_openmpi_include/include/openmpi/${MPIDIR}"])

	# OpenMPI library
	OPENMPI_LIB=mpi

	#
	# Look for OpenMPI library
	#
	AC_MSG_CHECKING([for OpenMPI library directory])
	OPENMPI_libdir=
	for m in ${OPENMPI_lib_check}
	do
		if test -d "$m"
		then
			if (test -f "$m/lib$OPENMPI_LIB.so" || test -f "$m/lib$OPENMPI_LIB.a")
			then
				OPENMPI_libdir=$m
				break
			fi
		fi
	done

	if test -z "$OPENMPI_libdir"
	then
		AC_MSG_ERROR([Didn't find $OPENMPI_LIB library in '$OPENMPI_lib_check'])
	fi

	case "$OPENMPI_libdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Openmpi library directory ($OPENMPI_libdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([$OPENMPI_libdir])

	#
	# Look for OpenMPI headers
	#
	AC_MSG_CHECKING([for OpenMPI include directory])
	OPENMPI_incdir=
	for m in $OPENMPI_inc_check
	do
		if test -d "$m" && test -f "$m/mpi.h"
		then
			OPENMPI_incdir=$m
			break
		fi
	done

	if test -z "$OPENMPI_incdir"
	then
		AC_MSG_ERROR([Didn't find the Openmpi include dir in '$OPENMPI_inc_check'])
	fi

	case "$OPENMPI_incdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Openmpi include directory ($OPENMPI_incdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([$OPENMPI_incdir])

	#
	# Look for OpenMPI version
	#
	min_openmpi_version=ifelse([$1], , 1.0.0, $1)
	AC_MSG_CHECKING([for OpenMPI version >= $min_openmpi_version])

	# Derive the full version, e.g., 1.3.3
	OPENMPI_VERSION=`echo ${OPENMPI_incdir} | sed 's/.*\/\([[0-9]]*\)\.\([[0-9]]*\)\.\([[0-9]]*\).*/\1.\2.\3/g'`
	if test -z "${OPENMPI_VERSION}" ; then
	   OPENMPI_VERSION=${OPENMPI_DEF_VERSION}
	fi

	# Calculation of major, minor, micro
    openmpi_major_version=`echo $OPENMPI_VERSION | sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${openmpi_major_version}" = "x" ; then
       openmpi_major_version=0
    fi

    openmpi_minor_version=`echo $OPENMPI_VERSION | \
						sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${openmpi_minor_version}" = "x" ; then
       openmpi_minor_version=0
    fi

    openmpi_micro_version=`echo $OPENMPI_VERSION | \
          sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${openmpi_micro_version}" = "x" ; then
       openmpi_micro_version=0
    fi
	
	AC_MSG_RESULT([$OPENMPI_VERSION])

	#
	# Derive the flags for compilation and linking
	#
	OPENMPI_CFLAGS="-I${OPENMPI_incdir} -I${OPENMPI_incdir}/openmpi -I${OPENMPI_incdir}/${MODE} ${MODEFLAG}"
	OPENMPI_LIBS="-L${OPENMPI_libdir} -lmpi_cxx"

	#
	# Make the changes permanent
	#
	AC_SUBST(OPENMPI_VERSION)
	AC_SUBST(OPENMPI_CFLAGS)
	AC_SUBST(OPENMPI_LIBS)

	# Test linking with openmpi
	save_LIBS="$LIBS"
	if test -z "$OPENMPI_LIBS"
	then
		OPENMPI_LIBS="-L/usr/lib${MODE}/openmpi/${MPIDIR} -lmpi_cxx"
	fi
	LIBS="$LIBS $OPENMPI_LIBS"
	AC_CHECK_LIB($OPENMPI_LIB, ompi_mpi_char,
                 [], 
                 [AC_MSG_ERROR([Could not find working Openmpi library!])]
                )
	LIBS="$save_LIBS"
]) dnl AX_OPENMPI
