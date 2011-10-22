dnl @synopsis AX_MYSQL
dnl 
dnl This macro tries to find Xerces C++ API header and library locations.
dnl
dnl We define the following configure script flags:
dnl
dnl		--with-xerces: Give prefix for both library and headers, and try
dnl			to guess subdirectory names for each.  (e.g. Tack /lib and
dnl			/include onto given dir name, and other common schemes.)
dnl		--with-xerces-lib: Similar to --with-xerces, but for library only.
dnl		--with-xerces-include: Similar to --with-xerces, but for headers
dnl			only.
dnl
dnl @version 1.0, 2008/07/13
dnl @author Denis Arnaud <denis_arnaud@users.sourceforge.net>

AC_DEFUN([AX_XERCES_C],
[
	#
	# Set up configure script macros
	#
    AC_ARG_WITH(xerces,
      [ --with-xerces=PATH to Xerces C++ installation directory],
      [xerces_inc_check="$withval/include"
       xerces_lib_check="$withval/lib64 $withval/lib"
      ],
      [xerces_inc_check="/usr/include /usr/local/include /usr/local/xercesc/include /usr/xercesc/include /usr/pkg/include /nastools/xerces-c/include"
       xerces_lib_check="/usr/local/lib64 /usr/local/lib /usr/lib64 /usr/lib /usr/local/xercesc/lib64 /usr/local/xercesc/lib /usr/lib64/xercesc /usr/lib/xercesc /usr/xercesc/lib64 /usr/xercesc/lib /usr/pkg/lib64 /usr/pkg/lib /nastools/xerces-c/lib64 /nastools/xerces-c/lib"
      ]
    )

    AC_ARG_WITH(xerces-lib,
      [  --with-xerces-lib=PATH to Xerces C++ library installation],
      [xerces_lib_check="$with_xerces_lib"]
    )

    AC_ARG_WITH(xerces-include,
      [  --with-xerces-include=PATH to Xerces C++ header installation],
      [xerces_inc_check="$with_xerces_include"]
    )

	#
	# Look for Xerces C++ API library
	#
    XERCES_C_LIB="xerces-c"
	AC_MSG_CHECKING([for Xerces C++ library directory ])
	xerces_libdir=
    for m in $xerces_lib_check
    do
		if test -d "$m" && \
          (test -f "$m/lib$XERCES_C_LIB.so" || test -f "$m/lib$XERCES_C_LIB.a")
		then
          xerces_libdir=$m
          break
		fi
    done

    if test -z "$xerces_libdir"
    then
      AC_MSG_ERROR([Didn't find $XERCES_C_LIB library in '$xerces_lib_check'])
    fi

	case "$xerces_libdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Xerces C++ library directory ($xerces_libdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([yes ($xerces_libdir)])

	case "$xerces_libdir" in
	  /usr/lib) ;;
	  *) LDFLAGS="$LDFLAGS -L${xerces_libdir}" ;;
	esac

	#
	# Look for Xerces C++ API headers
	#
    AC_MSG_CHECKING([for Xerces C++ include directory: ])
    xerces_incdir=
	xerces_version_header=
    for m in $xerces_inc_check
    do
      if test -d "$m" && (test -f "$m/xercesc/sax/Parser.hpp" \
	  	 || test -f "$m/xercesc/util/XercesVersion.hpp")
        then
          xerces_incdir=$m
		  xerces_version_header=$m/xercesc/util/XercesVersion.hpp
          break
      fi
    done

	if test -z "$xerces_incdir"
	then
		AC_MSG_ERROR([Didn't find the Xerces C++ include dir in '$xerces_inc_check'])
	fi

	case "$xerces_incdir" in
		/* ) ;;
		* )  AC_MSG_ERROR([The Xerces C++ include directory ($xerces_incdir) must be an absolute path.]) ;;
	esac

	AC_MSG_RESULT([yes ($xerces_incdir)])

    no_xerces=""
    if test "x$xerces_incdir" = "x" -o "x$xerces_libdir" = "x"; then
      no_xerces=yes
    else
		xerces_version_major=`grep "^#define XERCES_VERSION_MAJOR" $xerces_version_header | cut -d" " -f3`
		xerces_version_minor=`grep "^#define XERCES_VERSION_MINOR" $xerces_version_header | cut -d" " -f3`
		xerces_version_revision=`grep "^#define XERCES_VERSION_REVISION" $xerces_version_header | cut -d" " -f3`
		XERCES_VERSION="$xerces_version_major.$xerces_version_minor.$xerces_version_revision"

		XERCES_CFLAGS="-I${xerces_incdir}"
		XERCES_LIBS="-L${xerces_libdir} -l${XERCES_C_LIB}"
    	AC_SUBST(XERCES_VERSION)
    	AC_SUBST(XERCES_CFLAGS)
    	AC_SUBST(XERCES_LIBS)


    	SAVED_CPPFLAGS="$CPPFLAGS"
    	SAVED_LDFLAGS="$LDFLAGS"
    	CPPFLAGS="$CPPFLAGS $XERCES_CFLAGS"
    	LDFLAGS="$LDFLAGS $XERCES_LIBS"

    	AC_MSG_CHECKING([that Xerces C++ programs can be built])
    	AC_COMPILE_IFELSE(
			[AC_LANG_PROGRAM(
				[[#include <xercesc/sax2/SAX2XMLReader.hpp>
              	#include <xercesc/sax2/XMLReaderFactory.hpp>
				]],
          		[[xercesc::SAX2XMLReader* aXMLReader_ptr = xercesc::XMLReaderFactory::createXMLReader();
				]]
        	)]
        	,
    		[AC_MSG_RESULT([yes])],
			[
			AC_MSG_ERROR([We could not compile a simple Xerces C++ example. See config.log.])
			]
      	)

		CPPFLAGS="$SAVED_CPPFLAGS"
		LDFLAGS="$SAVED_LDFLAGS"

    fi dnl no_xerces
  ]) dnl AX_XERCES_C
