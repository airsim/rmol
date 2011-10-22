#
# Configure paths and flags for the ZeroMQ library.
# Denis Arnaud <denis_arnaud at users dot sourceforge dot net>, May 2011
#
# Variables set by this macro:
#  * AM_PATH_ZEROMQ
#  * ZEROMQ_VERSION
#  * ZEROMQ_CFLAGS
#  * ZEROMQ_LIBS
#

AC_DEFUN([AM_PATH_ZEROMQ],
[
AC_LANG_SAVE
AC_LANG([C++])

##
AC_ARG_WITH(zeromq,
	[[  --with-zeromq[=PFX] Prefix where ZeroMQ is installed (optional) ]],
	    zeromq_dir="$withval",
	    zeromq_dir="")

	ac_zeromq_path=""
    if test "x${zeromq_dir}" = "xno"
	then
      without_zeromq=yes
    elif test "x${zeromq_dir}" != "xyes"
	then
      with_arg="${zeromq_dir}/include:-L${zeromq_dir}/lib ${zeromq_dir}/include/zeromq:-L${zeromq_dir}/lib"
    fi

  ##
  AC_MSG_CHECKING(for zmq.hpp)

  if test "x$without_zeromq" != "xyes"
  then
    for i in $with_arg /usr/include: /usr/local/include:-L/usr/local/lib \
	    /usr/pkg/include:-L/usr/pkg/lib
    do
      ac_zeromq_path=`echo "$i" | sed 's/:.*//'`
      lib=`echo "$i" | sed 's/.*://'`

      if test -f ${ac_zeromq_path}/zmq.hpp
      then
        AC_MSG_RESULT(${ac_zeromq_path}/zmq.hpp)
	ZEROMQ_LIBS="$lib -lzmq"

	AC_DEFINE(HAVE_ZEROMQ, 1, [define if you have ZeroMQ])
	have_zeromq=yes
	break
      fi
    done
  fi

  if test "x$have_zeromq" != "xyes"; then
	AC_MSG_ERROR([The ZeroMQ library cannot be found. You may want to install zeromq-devel (RPM-based)/zeromq-dev (Debian-based) package.])
  fi

  ## ZeroMQ version
  zeromq_lib_version_req=ifelse([$1], ,2.0,$1)
  AC_MSG_CHECKING(for zeromq lib version >= $zeromq_lib_version_req)
  succeeded=no
  zeromq_lib_version_req_shorten=`expr $zeromq_lib_version_req : '\([[0-9]]*\.[[0-9]]*\)'`
  zeromq_lib_version_req_major=`expr $zeromq_lib_version_req : '\([[0-9]]*\)'`
  zeromq_lib_version_req_minor=`expr $zeromq_lib_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
  WANT_ZEROMQ_VERSION=`expr $zeromq_lib_version_req_major \* 100 \+  $zeromq_lib_version_req_minor`

  # The lines specifying the ZeroMQ version are like the following:
  #define ZMQ_VERSION_MAJOR 2
  #define ZMQ_VERSION_MINOR 1
  #define ZMQ_VERSION_PATCH 4
  zeromq_version_major=`grep "define ZMQ_VERSION_MAJOR" ${ac_zeromq_path}/zmq.h | cut -d' ' -f3`
  zeromq_version_minor=`grep "define ZMQ_VERSION_MINOR" ${ac_zeromq_path}/zmq.h | cut -d' ' -f3`
  zeromq_version_computed=`expr $zeromq_version_major \* 100 \+  $zeromq_version_minor`
  ZEROMQ_VERSION="${zeromq_version_major}.${zeromq_version_minor}"

  if test ${zeromq_version_computed} -ge ${WANT_ZEROMQ_VERSION}
  then
	AC_MSG_RESULT([yes (${ZEROMQ_VERSION}.)])
  else
	AC_MSG_ERROR([The version (${ZEROMQ_VERSION}) of the ZeroMQ library is too old. You may want to upgrade your zeromq package.])
  fi

  ##
  AC_SUBST([ZEROMQ_VERSION])
  AC_SUBST([ZEROMQ_CFLAGS])
  AC_SUBST([ZEROMQ_LIBS])

AC_LANG_RESTORE
])
