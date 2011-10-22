dnl
dnl brief  : sets gsoap library
dnl author : daniel.perez
dnl todo   : make library checks work
dnl todo   : make static/dynamic library an option 
dnl
AC_DEFUN([AX_GSOAP],
[


  dnl ###############################################
  dnl
  dnl 0) --with-gsoap-prefix 
  dnl
  AC_MSG_CHECKING([where is gsoap++'s]) 
  AC_ARG_WITH(
              [gsoap-prefix],
              AC_HELP_STRING([--with-gsoap-prefix=DIR],
              ["gsoap++ home or prefix (e.g. /usr/, /usr/local,...)"]),
              [
                GSOAP_PREFIX=$withval
                AC_MSG_RESULT([using $GSOAP_PREFIX folder])
              ],
              [
                AC_MSG_RESULT([no prefix provided, using default location.])
                foo="foo"
              ]
  )

	if test "x$GSOAP_PREFIX" != "x"; then
    GSOAP_LIBRARY_PATH_FLAG="-L$GSOAP_PREFIX/lib"
  else
    GSOAP_LIBRARY_PATH_FLAG=
  fi

  GSOAP_SHARED_LIBS="-lgsoap++ $GSOAP_LIBRARY_PATH_FLAG"
  GSOAP_STATIC_LIBS="-lgsoap++ $GSOAP_LIBRARY_PATH_FLAG"
  GSOAP_INCLUDES="$GSOAP_PREFIX/include"
  GSOAP_LD_LIBRARY_PATH="$GSOAP_PREFIX/lib"

  AC_SUBST([GSOAP_SHARED_LIBS])
  AC_SUBST([GSOAP_STATIC_LIBS])
  AC_SUBST([GSOAP_INCLUDES])
  AC_SUBST([GSOAP_LD_LIBRARY_PATH])

  dnl ###############################################
  dnl
  dnl 1) Checking if wsdl2h exists
  dnl
  AC_CHECK_PROG(WSDL2H, wsdl2h, true, false,[$PATH$PATH_SEPARATOR$GSOAP_PREFIX/bin$PATH_SEPARATOR]) 

  if test "$WSDL2H" = false ; then 
    AC_MSG_ERROR(cannot find wsdl2h.) 
  fi 
    
  dnl ###############################################
  dnl
  dnl 2) Checking if soapcpp2 exists
  dnl
  dnl AC_MSG_CHECKING([if soapcpp2 is installed]) 
  dnl AC_CHECK_PROG(SOAPCPP2, soapcpp2, true, false) 
  dnl
  dnl if test "$SOAPCPP2" = false ; then 
  dnl  AC_MSG_ERROR(cannot find soapcpp2.) 
  dnl fi

  dnl ###############################################
  dnl
  dnl 3) Checking if it compiles
  dnl
  AC_MSG_CHECKING([if gsoap++ compiles]) 
  AC_TRY_COMPILE([ #include <stdsoap2.h> ], [soap_new();],AC_MSG_RESULT([yes]), [AC_MSG_RESULT([no, see config.log.]) ; exit ] ) 


  dnl ###############################################
  dnl
  dnl 4) Checking if it links
  dnl

  dnl Setting library environment.
dnl  GSOAP_LINKS_DYNAMICALLY="false"
dnl  OLD_LDFLAGS="$LDFLAGS"
dnl  LDFLAGS="$LIBS $GSOAP_SHARED_LIBS" 
dnl 
dnl
dnl  dnl AC_MSG_CHECKING([if gsoap++ links dynamically]) 
dnl  dnl AC_TRY_LINK([ #include <stdsoap2.h> ], [soap_new();],[GSOAP_LINKS_DYNAMICALLY="true";AC_MSG_RESULT([yes])],[AC_MSG_RESULT([no.])]) 
dnl  AC_CHECK_LIB([gsoap++],[soap_new],[GSOAP_LINKS_DYNAMICALLY="true"],[]) 
dnl
dnl  dnl Setting library environment.
dnl  GSOAP_LINKS_STATICALLY="false"
dnl  LDFLAGS="$OLD_LDFLAGS"
dnl  LDFLAGS="$LIBS $GSOAP_STATIC_LIBS" 
dnl
dnl  dnl AC_MSG_CHECKING([if gsoap++ links statically]) 
dnl  dnl AC_TRY_LINK([ #include <stdsoap2.h> ], [soap_new();],[GSOAP_LINKS_STATICALLY="true";AC_MSG_RESULT([yes])],[AC_MSG_RESULT([no.])]) 
dnl  AC_CHECK_LIB([gsoap++],[soap_new],[GSOAP_LINKS_STATICALLY="true"],[]) 
dnl
dnl  LIBS="$OLD_LIBS" 
dnl
dnl  if [test "$GSOAP_LINKS_DINAMICALLY" == "true"] ; then
dnl    GSOAP_LIBS="$GSOAP_SHARED_LIBS";
dnl    AC_SUBST([GSOAP_LIBS])
dnl  elif [test "$GSOAP_LINKS_STATICALLY" == "true"] ; then
dnl    GSOAP_LIBS="$GSOAP_STATIC_LIBS"
dnl    AC_SUBST([GSOAP_LIBS])
dnl  else
dnl    AC_MSG_ERROR(gsoap does not link. See config.log.)
dnl  fi
])
