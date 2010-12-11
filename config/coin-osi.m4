dnl
dnl Test for OSI.
dnl
dnl author: christophe-marie.duquesne@amadeus.com
dnl
dnl This macro enables the "--with-coin-osi=" user switch.
dnl If the user does not use the switch, it tries to find osi headers in the default path.
dnl It stops the configure process if not found.
dnl

AC_DEFUN([AX_COIN_OSI],
[
    save_CFLAGS=$CFLAGS
    save_CPPFLAGS=$CFLAGS

    AC_LANG([C++])

    AC_ARG_WITH(coin-osi,
                AC_HELP_STRING([--with-coin-osi=DIR],
                               [COIN OSI home (if you installed OSI in a non-standard dir)]),
                [OSI_HOME="$withval"],
                [OSI_HOME=]
                )

    AC_MSG_CHECKING([for COIN-OR OSI])

    if test "x${OSI_HOME}" = "xno" -o "x${OSI_HOME}" = "x" ; then
        COIN_OSI_CFLAGS=
        COIN_OSI_LDFLAGS="-lOsi -lCoinUtils"
    else
        COIN_OSI_CFLAGS="-I${OSI_HOME}/include"
        COIN_OSI_LDFLAGS="-L${OSI_HOME}/lib -lOsi -lCoinUtils"
    fi

    AC_ARG_WITH(coin-osi-solvers,
                AC_HELP_STRING([--with-coin-osi-solvers=SOLVERNAMES],
                               [List of COIN-OR OSI solvers (Cpl, Glpk, Bcp, Cplex, ...) to use separated by commas. (Default = Clp)]),
                [OSI_SOLVERLIST="$withval"],
                [OSI_SOLVERLIST="Clp"]
                )

    for solver in $(echo $OSI_SOLVERLIST | tr ',' ' '); do 
        COIN_OSI_LDFLAGS+=" -lOsi${solver}"
        # Add the solver lib if delivered by COIN-OR
        test "${solver}" = "Clp" -o "${solver}" = "Dylp" -o "${solver}" = "Vol" && COIN_OSI_LDFLAGS+=" -l${solver}"
    done

    CFLAGS="$COIN_OSI_CFLAGS"
    CPPFLAGS="$COIN_OSI_CFLAGS"

    AC_CHECK_HEADER(
        [coin/OsiSolverInterface.hpp],
        [],
        [
        AC_MSG_ERROR(
           [Could not find OSI headers]
        )
        ]
    )

    HAVE_COIN_OR_OSI=1    
    
    AC_DEFINE([HAVE_COIN_OR_OSI],[],[Define this if osi is installed])
    
    AC_SUBST([COIN_OSI_CFLAGS])
    AC_SUBST([COIN_OSI_LDFLAGS])
    
    AC_MSG_RESULT([using flags $COIN_OSI_LDFLAGS])

    AM_CONDITIONAL(HAVE_COIN_OR_OSI,test "x$HAVE_COIN_OR_OSI" = "x1" )

    CFLAGS=$save_CFLAGS
    CPPFLAGS=$save_CFLAGS
])

