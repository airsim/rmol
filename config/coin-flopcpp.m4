dnl
dnl Test for Flopc++
dnl
dnl author: Christophe-marie Duquesne <chm.duquesne@gmail.com>
dnl
dnl This macro enables the "--with-coin-flopcpp=" user switch. If the
dnl user does not use the switch, it tries to find flopcpp headers in the
dnl default path. It stops the configure process if not found.
dnl
dnl It assumes you're checking by yourself that coin osi is installed.
dnl
dnl Usage: just put in your configure.ac:
dnl
dnl AX_COIN_FLOPCPP
dnl
dnl You can then use COIN_FLOPCPP_CFLAGS and COIN_FLOPCPP_LDFLAGS in your
dnl Makefile.am, and the flag HAVE_COIN_FLOPCPP is defined in your
dnl config.h
dnl

AC_DEFUN([AX_COIN_FLOPCPP],
[
    save_CFLAGS=$CFLAGS
    save_CPPFLAGS=$CPPFLAGS

    AC_LANG([C++])

    AC_ARG_WITH(coin-flopcpp,
        AC_HELP_STRING([--with-coin-flopcpp=DIR],
            [COIN FLOPC++ home (if installed in a non-standard dir)]),
            [FLOPCPP_HOME="$withval"],
            [FLOPCPP_HOME=]
    )

    AC_MSG_CHECKING([for COIN FLOPC++])

    if test "x${FLOPCPP_HOME}" = "xno" -o "x${FLOPCPP_HOME}" = "x" ; then
        COIN_FLOPCPP_CFLAGS=""
        COIN_FLOPCPP_LDFLAGS=""
    else
        COIN_FLOPCPP_CFLAGS="-I${FLOPCPP_HOME}/include"
        COIN_FLOPCPP_LDFLAGS="-L${FLOPCPP_HOME}/lib"
    fi

    CFLAGS="$COIN_FLOPCPP_CFLAGS"
    CPPFLAGS="$COIN_FLOPCPP_CFLAGS"

    AC_CHECK_HEADER(
        [coin/flopc.hpp],
        [],
        [
        AC_MSG_ERROR(
           [Could not find COIN FLOPC++ headers]
        )
        ]
    )

    HAVE_COIN_FLOPCPP=1
    
    AC_DEFINE([HAVE_COIN_FLOPCPP],[],[Define this if COIN FLOPCPP is installed])
    
    AC_SUBST([COIN_FLOPCPP_CFLAGS])
    AC_SUBST([COIN_FLOPCPP_LDFLAGS])
    
    AC_MSG_RESULT([using flags $COIN_FLOPCPP_LDFLAGS])

    AM_CONDITIONAL(HAVE_COIN_FLOPCPP,test "x$HAVE_COIN_FLOPCPP" = "x1" )

    CFLAGS=$save_CFLAGS
    CPPFLAGS=$save_CPPFLAGS
])

