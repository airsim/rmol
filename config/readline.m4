#
# Configure paths and flags for the GNU Readline library.
# Denis Arnaud <denis_arnaud at users dot sourceforge dot net>, April 2011
# Based on http://code.google.com/p/libnfc/source/browse/trunk/m4/readline.m4
# itself based on Wojtekka's m4 from
# http://wloc.wsinf.edu.pl/~kklos/ekg-20080219/m4/readline.m4
#
# Note: the GNU Readline library has a GPL license. Any program using
# it must therefore be GPL.
#
# Variables set by this macro:
#  * AM_PATH_READLINE
#  * READLINE_VERSION
#  * READLINE_CFLAGS
#  * READLINE_LIBS
#

AC_DEFUN([AM_PATH_READLINE],
[
AC_LANG_SAVE
AC_LANG([C])

##
AC_ARG_WITH(readline,
	[[  --with-readline[=PFX] Prefix where Readline is installed (optional) ]],
	    readline_dir="$withval",
	    readline_dir="")

	ac_readline_path=""
    if test "x${readline_dir}" = "xno"
	then
      without_readline=yes
    elif test "x${readline_dir}" != "xyes"
	then
      with_arg="${readline_dir}/include:-L${readline_dir}/lib ${readline_dir}/include/readline:-L${readline_dir}/lib"
    fi

  ##
  AC_MSG_CHECKING(for readline.h)

  if test "x$without_readline" != "xyes"; then
  	 for i in $with_arg \
	 	 /usr/include: /usr/local/include:-L/usr/local/lib \
		 /usr/pkg/include:-L/usr/pkg/lib
	 do
    
      ac_readline_path=`echo "$i" | sed 's/:.*//'`
      lib=`echo "$i" | sed 's/.*://'`

      if test -f ${ac_readline_path}/readline/readline.h
	  then
        AC_MSG_RESULT(${ac_readline_path}/readline/readline.h)
        READLINE_LIBS="$lib -lreadline"

		if test "${ac_readline_path}" != "/usr/include"; then
		   READLINE_CFLAGS="-I${ac_readline_path}/readline -I${ac_readline_path}"
		else
		   READLINE_CFLAGS="-I${ac_readline_path}/readline"
		fi
        
		AC_DEFINE(HAVE_READLINE, 1, [define if you have readline])
		ac_readline_path="${ac_readline_path}/readline"
        have_readline=yes
        break
      
	  elif test -f ${ac_readline_path}/readline.h -a "x${ac_readline_path}" != "x/usr/include"
	  then
        AC_MSG_RESULT(${ac_readline_path}/readline.h)
        READLINE_CFLAGS="-I${ac_readline_path}"
        READLINE_LIBS="$lib -lreadline"
        AC_DEFINE(HAVE_READLINE, 1, [define if you have readline])
        have_readline=yes
        break
      fi

    done

  fi

  if test "x$have_readline" != "xyes"; then
	AC_MSG_ERROR([The GNU Readline library cannot be found. You may want to install readline-devel (RPM-based)/readline-dev (Debian-based) package.])
  fi

  ## Readline version
  readline_lib_version_req=ifelse([$1], ,6.0,$1)
  AC_MSG_CHECKING(for readline lib version >= $readline_lib_version_req)
  succeeded=no
  readline_lib_version_req_shorten=`expr $readline_lib_version_req : '\([[0-9]]*\.[[0-9]]*\)'`
  readline_lib_version_req_major=`expr $readline_lib_version_req : '\([[0-9]]*\)'`
  readline_lib_version_req_minor=`expr $readline_lib_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
  WANT_READLINE_VERSION=`expr $readline_lib_version_req_major \* 100 \+  $readline_lib_version_req_minor`

  # The lines specifying the Readline version are like the following:
  #define RL_READLINE_VERSION [TAB] 0x0601      /* Readline 6.0 */
  #define RL_VERSION_MAJOR [TAB] 6
  #define RL_VERSION_MINOR [TAB] 1
  readline_version_coded=`grep "define RL_READLINE_VERSION" ${ac_readline_path}/readline.h | cut -f2 | cut -dx -f2`
  readline_version_major=`grep "define RL_VERSION_MAJOR" ${ac_readline_path}/readline.h | cut -f2`
  readline_version_minor=`grep "define RL_VERSION_MINOR" ${ac_readline_path}/readline.h | cut -f2`
  readline_version_computed=`expr $readline_version_major \* 100 \+  $readline_version_minor`
  READLINE_VERSION="${readline_version_major}.${readline_version_minor}"

  if test ${readline_version_computed} -ge ${WANT_READLINE_VERSION}
  then
	AC_MSG_RESULT([yes (${READLINE_VERSION}.)])
  else
	AC_MSG_ERROR([The version (${READLINE_VERSION}) of the GNU Readline library is too old. You may want to upgrade your readline package.])
  fi

  ##
  AC_SUBST([READLINE_VERSION])
  AC_SUBST([READLINE_CFLAGS])
  AC_SUBST([READLINE_LIBS])

AC_LANG_RESTORE
])
