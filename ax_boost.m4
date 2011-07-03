dnl @synopsis AX_BOOST([MINIMUM-VERSION], [ACTION-IF-FOUND], [ACTION-IF-NOT-FOUND])
dnl
dnl Test for the Boost C++ libraries of a particular version (or newer)
dnl
dnl If no path to the installed boost library is given the macro
dnl searchs under /usr, /usr/local, and /opt, and evaluates the
dnl $BOOST_ROOT environment variable.
dnl
dnl This macro calls:
dnl
dnl   AC_SUBST(BOOST_CFLAGS) / AC_SUBST(BOOST_LIBS)
dnl   AC_SUBST(BOOST_FILESYSTEM_LIB)
dnl   AC_SUBST(BOOST_SYSTEM_LIB)
dnl   AC_SUBST(BOOST_PROGRAM_OPTIONS_LIB)
dnl   AC_SUBST(BOOST_THREAD_LIB)
dnl   AC_SUBST(BOOST_IOSTREAMS_LIB)
dnl   AC_SUBST(BOOST_SERIALIZATION_LIB)
dnl   AC_SUBST(BOOST_WSERIALIZATION_LIB)
dnl   AC_SUBST(BOOST_SIGNALS_LIB)
dnl   AC_SUBST(BOOST_DATE_TIME_LIB)
dnl   AC_SUBST(BOOST_REGEX_LIB)
dnl   AC_SUBST(BOOST_PYTHON_LIB)
dnl   AC_SUBST(BOOST_ASIO_LIB)
dnl   AC_SUBST(BOOST_MPI_LIB)
dnl   AC_SUBST(BOOST_MPI_PYTHON_LIB)
dnl   AC_SUBST(BOOST_UNIT_TEST_FRAMEWORK_LIB)
dnl
dnl And sets:
dnl
dnl   HAVE_BOOST
dnl   HAVE_BOOST_FILESYSTEM
dnl   HAVE_BOOST_SYSTEM
dnl   HAVE_BOOST_PROGRAM_OPTIONS
dnl   HAVE_BOOST_THREAD
dnl   HAVE_BOOST_IOSTREAMS
dnl   HAVE_BOOST_SERIALIZATION
dnl   HAVE_BOOST_SIGNALS
dnl   HAVE_BOOST_DATE_TIME
dnl   HAVE_BOOST_REGEX
dnl   HAVE_BOOST_PYTHON
dnl   HAVE_BOOST_ASIO
dnl   HAVE_BOOST_MPI
dnl   HAVE_BOOST_MPI_PYTHON
dnl   HAVE_BOOST_UNIT_TEST_FRAMEWORK
dnl
dnl @category InstalledPackages
dnl @author Thomas Porschberg <thomas@randspringer.de>
dnl @version 2006-01-02
dnl @license AllPermissive

AC_DEFUN([AX_BOOST],
[
    AC_ARG_WITH([boost],
                AC_HELP_STRING([--with-boost=DIR],
                [use boost (default is NO) , specify the root directory for boost library (optional)]),
                [
                if test "$withval" = "no"; then
		            want_boost="no"
                elif test "$withval" = "yes"; then
                    want_boost="yes"
                    ac_boost_path=""
                else
			        want_boost="yes"
            		ac_boost_path="$withval"
		        fi
            	],
                [want_boost="yes"])

#    AC_CANONICAL_BUILD
BOOST_MDW_VERSION="1-33-1"
BOOSTLIB_MDW_VERSION="1_33_1"
BOOST_version_header="boost/version.hpp"

	if test "x$want_boost" = "xyes"; then
		boost_lib_version_req=ifelse([$1], ,1.20.0,$1)
		boost_lib_version_req_shorten=`expr $boost_lib_version_req : '\([[0-9]]*\.[[0-9]]*\)'`
		boost_lib_version_req_major=`expr $boost_lib_version_req : '\([[0-9]]*\)'`
		boost_lib_version_req_minor=`expr $boost_lib_version_req : '[[0-9]]*\.\([[0-9]]*\)'`
		boost_lib_version_req_sub_minor=`expr $boost_lib_version_req : '[[0-9]]*\.[[0-9]]*\.\([[0-9]]*\)'`
		if test "x$boost_lib_version_req_sub_minor" = "x" ; then
			boost_lib_version_req_sub_minor="0"
    	fi
		WANT_BOOST_VERSION=`expr $boost_lib_version_req_major \* 100000 \+  $boost_lib_version_req_minor \* 100 \+ $boost_lib_version_req_sub_minor`
		AC_MSG_CHECKING(for boostlib >= $boost_lib_version_req)
		succeeded=no

		dnl first we check the system location for boost libraries
		dnl this location is chosen if boost libraries are installed 
		dnl with the --layout=system option
		dnl or if you install boost with RPM
		if test -d /lib64
		then
			BOOST_LIBDIRTYPE="lib64"
		else
			BOOST_LIBDIRTYPE="lib"
		fi
		if test "$ac_boost_path" != ""
		then
			if test "$BOOST_LIBDIRTYPE" == "lib64"
			then
				if test -d "$ac_boost_path/$BOOST_LIBDIRTYPE" && test -r "$ac_boost_path/$BOOST_LIBDIRTYPE"
				then
	                BOOST_LIBS="-L$ac_boost_path/$BOOST_LIBDIRTYPE"
				else
                    BOOST_LIBS="-L$ac_boost_path/lib"
				fi
			else
				BOOST_LIBS="-L$ac_boost_path/lib"
			fi
			BOOST_CFLAGS="-I$ac_boost_path/include"
			BOOST_VERSION=`grep "define BOOST_LIB_VERSION" $ac_boost_path/include/${BOOST_version_header} | cut -d' ' -f3 | cut -d\" -f2`
		else
			for ac_boost_path_tmp in /usr /usr/local /opt /nastools/boost
			do
				if test -d "$ac_boost_path_tmp/include/boost" && test -r "$ac_boost_path_tmp/include/boost"
				then
					BOOST_LIBS="-L$ac_boost_path_tmp/$BOOST_LIBDIRTYPE"
					BOOST_CFLAGS="-I$ac_boost_path_tmp/include"
					BOOST_VERSION=`grep "define BOOST_LIB_VERSION" $ac_boost_path_tmp/include/${BOOST_version_header} | cut -d' ' -f3 | cut -d\" -f2`
					break;
				fi
				if test -d "$ac_boost_path_tmp/include/boost-$BOOST_MDW_VERSION/boost" && test -r "$ac_boost_path_tmp/include/boost-$BOOST_MDW_VERSION/boost"
				then
					BOOST_LIBS="-L$ac_boost_path_tmp/$BOOST_LIBDIRTYPE"
					BOOST_CFLAGS="-I$ac_boost_path_tmp/include/boost-$BOOST_MDW_VERSION"
					BOOST_VERSION=`grep "define BOOST_LIB_VERSION" $ac_boost_path_tmp/include/boost-$BOOST_MDW_VERSION/${BOOST_version_header} | cut -d' ' -f3 | cut -d\" -f2`
			
					dnl Hack for wrongly installed Boost libraries (AMD64 libraries installed in boost/lib directory)
					if test -d "$ac_boost_path_tmp/lib" \
					&& test -r "$ac_boost_path_tmp/lib" \
					&& test ! -d "$ac_boost_path_tmp/lib64"
					then
						BOOST_LIBS="-L$ac_boost_path_tmp/lib"
						echo "Hack: $BOOST_LIBS"
					fi
					break;
				fi
			done
		fi

		CPPFLAGS_SAVED="$CPPFLAGS"
		CPPFLAGS="$CPPFLAGS $BOOST_CFLAGS"
		export CPPFLAGS

		LDFLAGS_SAVED="$LDFLAGS"
		LDFLAGS="$LDFLAGS $BOOST_LIBS"
		export LDFLAGS

     	AC_TRY_COMPILE(
       	[
@%:@include <boost/version.hpp>
],
       [
#if BOOST_VERSION >= $WANT_BOOST_VERSION
// Everything is okay
#else
#  error Boost version is too old
#endif

		],
    	[
         AC_MSG_RESULT(yes)
		 succeeded=yes
		 found_system=yes
         ifelse([$2], , :, [$2])
       ],
       [
       ])

		dnl if we found no boost with system layout we search for boost libraries
		dnl built and installed without the --layout=system option or for a staged(not installed) version
		if test "x$succeeded" != "xyes"; then
			_version=0
			if test "$ac_boost_path" != ""; then
                BOOST_LIBS="-L$ac_boost_path/$BOOST_LIBDIRTYPE"
				if test -d "$ac_boost_path" && test -r "$ac_boost_path"; then
					for i in `ls -d $ac_boost_path/include/boost-* 2>/dev/null`; do
						_version_tmp=`echo $i | sed "s#$ac_boost_path##" | sed 's/\/include\/boost-//' | sed 's/_/./'`
						V_CHECK=`expr $_version_tmp \> $_version`
						if test "$V_CHECK" = "1" ; then
							_version=$_version_tmp
						fi
						VERSION_UNDERSCORE=`echo $_version | sed 's/\./_/'`
						BOOST_CFLAGS="-I$ac_boost_path/include/boost-$VERSION_UNDERSCORE"
					done
				fi
			else
				for ac_boost_path in /usr /usr/local /opt ; do
					if test -d "$ac_boost_path" && test -r "$ac_boost_path"; then
						for i in `ls -d $ac_boost_path/include/boost-* 2>/dev/null`; do
							_version_tmp=`echo $i | sed "s#$ac_boost_path##" | sed 's/\/include\/boost-//' | sed 's/_/./'`
							V_CHECK=`expr $_version_tmp \> $_version`
							if test "$V_CHECK" = "1" ; then
								_version=$_version_tmp
								best_path=$ac_boost_path
							fi
						done
					fi
				done

				VERSION_UNDERSCORE=`echo $_version | sed 's/\./_/'`
				BOOST_CFLAGS="-I$best_path/include/boost-$VERSION_UNDERSCORE"
				BOOST_LIBS="-L$best_path/$BOOST_LIBDIRTYPE"

	    		if test "x$BOOST_ROOT" != "x"; then
					if test -d "$BOOST_ROOT" && test -r "$BOOST_ROOT"; then
						version_dir=`expr //$BOOST_ROOT : '.*/\(.*\)'`
						stage_version=`echo $version_dir | sed 's/boost_//' | sed 's/_/./g'`
						stage_version_shorten=`expr $stage_version : '\([[0-9]]*\.[[0-9]]*\)'`
						V_CHECK=`expr $stage_version_shorten \>\= $_version`
						if test "$V_CHECK" = "1" ; then
							AC_MSG_NOTICE(We will use a staged boost library from $BOOST_ROOT)
							BOOST_CFLAGS="-I$BOOST_ROOT"
							BOOST_LIBS="-L$BOOST_ROOT/stage/$BOOST_LIBDIRTYPE"
						fi
					fi
	    		fi
			fi

			CPPFLAGS="$CPPFLAGS $BOOST_CFLAGS"
			export CPPFLAGS
			LDFLAGS="$LDFLAGS $BOOST_LIBS"
			export LDFLAGS

     		AC_TRY_COMPILE(
       		[
@%:@include <boost/version.hpp>
],
       [
#if BOOST_VERSION >= $WANT_BOOST_VERSION
// Everything is okay
#else
#  error Boost version is too old
#endif

		],
    	[
         AC_MSG_RESULT(yes ($_version))
		 succeeded=yes
         ifelse([$2], , :, [$2])
       ],
       [
         AC_MSG_RESULT(no ($_version))
         ifelse([$3], , :, [$3])
       ])
		fi

		if test "$succeeded" != "yes" ; then
			if test "$_version" = "0" ; then
				AC_MSG_ERROR([[We could not detect the boost libraries (version $boost_lib_version_req_shorten or higher). If you have a staged boost library (still not installed) please specify \$BOOST_ROOT in your environment and do not give a PATH to --with-boost option.  If you are sure you have boost installed, then check your version number looking in <boost/version.hpp>.]])
			else
				AC_MSG_ERROR('Your boost libraries seems to old (version $_version).  We need at least $boost_lib_version_shorten')
			fi
		else
			AC_SUBST(BOOST_CFLAGS)
			AC_SUBST(BOOST_LIBS)
			AC_DEFINE(HAVE_BOOST,,[define if the Boost library is available])

#
# Boost::Filesystem
#
			AC_CACHE_CHECK([whether the Boost::Filesystem library is available],
						   ax_cv_boost_filesystem,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/filesystem/path.hpp>]],
                                   [[using namespace boost::filesystem;
                                   path my_path( "foo/bar/data.txt" );
                                   return 0;]])],
            				       ax_cv_boost_filesystem=yes, ax_cv_boost_filesystem=no)
		 		        			AC_LANG_RESTORE
			])
			if test "$ax_cv_boost_filesystem" = "yes"; then
				AC_DEFINE(HAVE_BOOST_FILESYSTEM,,[define if the Boost::FILESYSTEM library is available])
				BN=boost_filesystem
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main,
                                 [BOOST_FILESYSTEM_LIB="-l$ax_lib" AC_SUBST(BOOST_FILESYSTEM_LIB) link_filesystem="yes" break],
                                 [link_filesystem="no"])
  				done
				if test "x$link_filesystem" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::System
#
            AC_CACHE_CHECK([whether the Boost::System library is available],
                           ax_cv_boost_system,
                           [AC_LANG_SAVE
            AC_LANG_CPLUSPLUS
            AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/system/error_code.hpp>]],
                                   [[using namespace boost::system;
                                   error_code myErrorCode();
                                   return 0;]])],
                                   ax_cv_boost_system=yes, ax_cv_boost_system=no)
                                    AC_LANG_RESTORE
            ])
            if test "$ax_cv_boost_system" = "yes"; then
                 AC_DEFINE(HAVE_BOOST_SYSTEM,,[define if the Boost::SYSTEM library is available])
                 BN=boost_system
                 for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
                     AC_CHECK_LIB($ax_lib, main,
                                 [BOOST_SYSTEM_LIB="-l$ax_lib" AC_SUBST(BOOST_SYSTEM_LIB) link_system="yes" break],
                                 [link_system="no"])
                 done
                 if test "x$link_system" = "xno"; then
                     AC_MSG_NOTICE(Could not link against $ax_lib !)
                 fi
            fi

#
# Boost::Program_Options
#
			AC_CACHE_CHECK([whether the Boost::Program_Options library is available],
						   ax_cv_boost_program_options,
						   [AC_LANG_SAVE
                           AC_LANG_CPLUSPLUS
	               AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/program_options.hpp>]],
                                   [[boost::program_options::options_description generic("Generic options");
                                   return 0;]])],
                           ax_cv_boost_program_options=yes, ax_cv_boost_program_options=no)
			               AC_LANG_RESTORE
			])
			if test "$ax_cv_boost_program_options" = yes; then
				AC_DEFINE(HAVE_BOOST_PROGRAM_OPTIONS,,[define if the Boost::PROGRAM_OPTIONS library is available])
				BN=boost_program_options
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main,
                                 [BOOST_PROGRAM_OPTIONS_LIB="-l$ax_lib" AC_SUBST(BOOST_PROGRAM_OPTIONS_LIB) link_program_options="yes" break],
                                 [link_program_options="no"])
  				done
				if test "x$link_program_options="no"" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::Threads
#
			AC_CACHE_CHECK(whether the Boost::Thread library is available,
						   ax_cv_boost_thread,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 CXXFLAGS_SAVE=$CXXFLAGS

			 if test "x$build_os" = "xsolaris" ; then
  				 CXXFLAGS="-pthreads $CXXFLAGS"
			 elif test "x$build_os" = "xming32" ; then
				 CXXFLAGS="-mthreads $CXXFLAGS"
			 else
				CXXFLAGS="-pthread $CXXFLAGS"
			 fi
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/thread/thread.hpp>]],
                                   [[boost::thread_group thrds;
                                   return 0;]])],
                   ax_cv_boost_thread=yes, ax_cv_boost_thread=no)
			 CXXFLAGS=$CXXFLAGS_SAVE
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_thread" = "xyes"; then
               if test "x$build_os" = "xsolaris" ; then
 				  BOOST_CFLAGS="-pthreads $BOOST_CFLAGS"
			   elif test "x$build_os" = "xming32" ; then
 				  BOOST_CFLAGS="-mthreads $BOOST_CFLAGS"
			   else
				  BOOST_CFLAGS="-pthread $BOOST_CFLAGS"
			   fi

				AC_SUBST(BOOST_CFLAGS)
				AC_DEFINE(HAVE_BOOST_THREAD,,[define if the Boost::THREAD library is available])
				BN=boost_thread
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main, [BOOST_THREAD_LIB="-l$ax_lib" AC_SUBST(BOOST_THREAD_LIB) link_thread="yes" break],
                                 [link_thread="no"])
  				done
				if test "x$link_thread" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::IOStreams
#
			AC_CACHE_CHECK(whether the Boost::IOStreams library is available,
						   ax_cv_boost_iostreams,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE(
			   [AC_LANG_PROGRAM(
	   [[@%:@include <boost/iostreams/filtering_stream.hpp>
	   @%:@include <boost/range/iterator_range.hpp>]],
	   [[std::string  input = "Hello World!";
	   namespace io = boost::iostreams;
	   io::filtering_istream in (boost::make_iterator_range(input));
	   return 0;
           ]])],
                   ax_cv_boost_iostreams=yes, ax_cv_boost_iostreams=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_iostreams" = "xyes"; then
				AC_DEFINE(HAVE_BOOST_IOSTREAMS,,[define if the Boost::IOStreams library is available])
				BN=boost_iostreams
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main, [BOOST_IOSTREAMS_LIB="-l$ax_lib" AC_SUBST(BOOST_IOSTREAMS_LIB) link_thread="yes" break],
                                 [link_thread="no"])
  				done
				if test "x$link_thread" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::Serialization
#
			AC_CACHE_CHECK(whether the Boost::Serialization library is available,
						   ax_cv_boost_serialization,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM(
	[[@%:@include <fstream>
	@%:@include <boost/archive/text_oarchive.hpp>
        @%:@include <boost/archive/text_iarchive.hpp>
	]],
        [[std::ofstream ofs("filename");
	boost::archive::text_oarchive oa(ofs);
	return 0;
        ]])],
                   ax_cv_boost_serialization=yes, ax_cv_boost_serialization=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_serialization" = "xyes"; then
				AC_DEFINE(HAVE_BOOST_SERIALIZATION,,[define if the Boost::Serialization library is available])
				BN=boost_serialization
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main,
                                 [BOOST_SERIALIZATION_LIB="-l$ax_lib" AC_SUBST(BOOST_SERIALIZATION_LIB) link_thread="yes" break],
                                 [link_thread="no"])
  				done
				BN=boost_wserialization
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main,
                                 [BOOST_WSERIALIZATION_LIB="-l$ax_lib" AC_SUBST(BOOST_WSERIALIZATION_LIB) link_thread="yes" break],
                                 [link_thread="no"])
  				done
				if test "x$link_thread" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::Signals
#
			AC_CACHE_CHECK(whether the Boost::Signals library is available,
						   ax_cv_boost_signals,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/signal.hpp>
												]],
                                   [[boost::signal<void ()> sig;
                                     return 0;
                                   ]])],
                   ax_cv_boost_signals=yes, ax_cv_boost_signals=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_signals" = "xyes"; then
				AC_DEFINE(HAVE_BOOST_SIGNALS,,[define if the Boost::Signals library is available])
				BN=boost_signals
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main, [BOOST_SIGNALS_LIB="-l$ax_lib" AC_SUBST(BOOST_SIGNALS_LIB) link_signals="yes" break],
                                 [link_signals="no"])
  				done
				if test "x$link_signals" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::Date_Time
#
			AC_CACHE_CHECK(whether the Boost::Date_Time library is available,
						   ax_cv_boost_date_time,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/date_time/gregorian/gregorian_types.hpp>
												]],
                                   [[using namespace boost::gregorian; date d(2002,Jan,10);
                                     return 0;
                                   ]])],
                   ax_cv_boost_date_time=yes, ax_cv_boost_date_time=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_date_time" = "xyes"; then
				AC_DEFINE(HAVE_BOOST_DATE_TIME,,[define if the Boost::Date_Time library is available])
				BN=boost_date_time
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main, [BOOST_DATE_TIME_LIB="-l$ax_lib" AC_SUBST(BOOST_DATE_TIME_LIB) link_date_time="yes" break],
                                 [link_date_time="no"])
  				done
				if test "x$link_date_time"="no" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::Regex
#
			AC_CACHE_CHECK(whether the Boost::Regex library is available,
						   ax_cv_boost_regex,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/regex.hpp>
												]],
                                   [[boost::regex r(); return 0;]])],
                   ax_cv_boost_regex=yes, ax_cv_boost_regex=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_regex" = "xyes"; then
				AC_DEFINE(HAVE_BOOST_REGEX,,[define if the Boost::Regex library is available])
				BN=boost_regex
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main, [BOOST_REGEX_LIB="-l$ax_lib" AC_SUBST(BOOST_REGEX_LIB) link_thread="yes" break],
                                 [link_thread="no"])
  				done
				if test "x$link_thread" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi

#
# Boost::ASIO: it needs Boost.System, Boost.Regex, Boost.Thread and 
# Boost.DateTime, but does not produce any (other) library.
#
			AC_CACHE_CHECK(whether the Boost::Asio library is available,
						   ax_cv_boost_asio,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/asio.hpp>]],
                                   [[boost::asio::io_service io;
	                                 boost::system::error_code timer_result;
	                                 boost::asio::deadline_timer t(io);
	                                 t.cancel();
	                                 io.run_one();
	                                 return 0;
                                   ]])],
                   ax_cv_boost_asio=yes, ax_cv_boost_asio=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_asio" = "xyes"; then
			   AC_DEFINE(HAVE_BOOST_ASIO,,[define if the Boost::Asio library is available])
			   BOOST_ASIO_LIB="${BOOST_SYSTEM_LIB} ${BOOST_THREAD_LIB}"
			   BOOST_ASIO_LIB="${BOOST_ASIO_LIB} ${BOOST_DATE_TIME_LIB}"
			   BOOST_ASIO_LIB="${BOOST_ASIO_LIB} ${BOOST_REGEX_LIB}"
			   BOOST_ASIO_LIB="${BOOST_ASIO_LIB} ${BOOST_SERIALIZATION_LIB}"
			   AC_SUBST(BOOST_ASIO_LIB)
			fi

#
# Support for Python and MPI (MPICH2, Boost::MPI, Boost::Python, 
# Boost::Serialization, Boost::MPI_Python)
# Note: on some distributions (e.g., Debian), Boost.MPI uses OpenMPI rather 
#       than MPICH2
#
			CPPFLAGS_ORIG="${CPPFLAGS}"
			CPPFLAGS="${CPPFLAGS} ${PYTHON_CFLAGS} ${MPIGEN_CFLAGS}"
#			CPPFLAGS="${CPPFLAGS} ${PYTHON_CFLAGS} ${MPICH2_CFLAGS}"
#			CPPFLAGS="${CPPFLAGS} ${PYTHON_CFLAGS} ${OPENMPI_CFLAGS}"
			LDFLAGS_ORIG="${LDFLAGS}"
			LDFLAGS="${LDFLAGS} ${PYTHON_LIBS} ${PYTHON_ADD_LIBS} ${MPIGEN_LIBS}"
#			LDFLAGS="${LDFLAGS} ${PYTHON_LIBS} ${PYTHON_ADD_LIBS} ${MPICH2_LIBS}"
#			LDFLAGS="${LDFLAGS} ${PYTHON_LIBS} ${PYTHON_ADD_LIBS} ${OPENMPI_LIBS}"

#
# Boost::Python
#
			AC_CACHE_CHECK(whether the Boost::Python library is available,
						   ax_cv_boost_python,
			[AC_LANG_SAVE
			AC_LANG_CPLUSPLUS

		    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/python.hpp>
			char const* greet() { return "hello"; } 
			BOOST_PYTHON_MODULE(hello_ext) { boost::python::def("greet", greet);}
										   ]])],
                   ax_cv_boost_python=yes, ax_cv_boost_python=no)
			 AC_LANG_RESTORE
			])

			BOOST_PYTHON_LIB="-lboost_python ${PYTHON_LIBS} ${PYTHON_ADD_LIBS}"
			AC_SUBST(BOOST_PYTHON_LIB)

#
# Boost::MPI
#
			AC_CACHE_CHECK(whether the Boost::Mpi library is available,
						   ax_cv_boost_mpi,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/mpi.hpp>]],
                                   [[
	                                 return 0;
                                   ]])],
                   ax_cv_boost_mpi=yes, ax_cv_boost_mpi=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_mpi" = "xyes"; then
				AC_DEFINE(HAVE_BOOST_MPI,,[define if the Boost::Mpi library is available])
				BN=boost_mpi
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main, [BOOST_MPI_LIB="-l$ax_lib" AC_SUBST(BOOST_MPI_LIB) link_mpi="yes" break],
                                 [link_mpi="no"])
  				done
				if test "x$link_mpi" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				else
					BOOST_MPI_LIB="${BOOST_MPI_LIB} ${BOOST_SERIALIZATION_LIB} ${MPIGEN_LIBS}"
				fi
			fi

#
# Boost::MPI_Python
#
			AC_CACHE_CHECK(whether the Boost::Mpi_Python library is available,
						   ax_cv_boost_mpi_python,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/mpi/python/serialize.hpp>
			 								   ]],
                                   [[
	                                 return 0;
                                   ]])],
                   ax_cv_boost_mpi_python=yes, ax_cv_boost_mpi_python=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_mpi_python" = "xyes"; then
				AC_DEFINE(HAVE_BOOST_MPI_PYTHON,,[define if the Boost::Mpi_Python library is available])
				BN=boost_mpi_python
#				BN=boost_mpi_python-py25
				for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
				    AC_CHECK_LIB($ax_lib, main, [BOOST_MPI_PYTHON_LIB="-l$ax_lib" AC_SUBST(BOOST_MPI_PYTHON_LIB) link_mpi_python="yes" break],
                                 [link_mpi_python="no"])
  				done
				if test "x$link_mpi_python" = "xno"; then
					AC_MSG_NOTICE(Could not link against $ax_lib !)
				else
					BOOST_MPI_PYTHON_LIB="${BOOST_MPI_PYTHON_LIB} ${BOOST_SERIALIZATION_LIB}"
					BOOST_MPI_PYTHON_LIB="${BOOST_MPI_PYTHON_LIB} ${BOOST_PYTHON_LIB}"
					BOOST_MPI_PYTHON_LIB="${BOOST_MPI_PYTHON_LIB} ${BOOST_MPI_LIB}"
					BOOST_MPI_PYTHON_LIB="${BOOST_MPI_PYTHON_LIB} ${MPIGEN_LIBS}"
				fi
			fi

#
# End of section on support for MPI
#
			CPPFLAGS="${CPPFLAGS_ORIG}"
			LDFLAGS="${LDFLAGS_ORIG}"

#
# Boost::UnitTestFramework
#
			AC_CACHE_CHECK(whether the Boost::UnitTestFramework library is available,
						   ax_cv_boost_unit_test_framework,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
			 AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/test/unit_test.hpp>]],
                                    [[using boost::unit_test::test_suite;
					                 test_suite* test= BOOST_TEST_SUITE( "Unit test example 1" ); return 0;]])],
                   ax_cv_boost_unit_test_framework=yes, ax_cv_boost_unit_test_framework=no)
			 AC_LANG_RESTORE
			])
			if test "x$ax_cv_boost_unit_test_framework" = "xyes"; then
    		AC_DEFINE(HAVE_BOOST_UNIT_TEST_FRAMEWORK,,[define if the Boost::Unit_test_framework library is available])
			BN=boost_unit_test_framework
    		saved_ldflags="${LDFLAGS}"
			for ax_lib in \
					$BN-mt $BN $BN-$CC-mt $BN-$CC \
					$BN-$CC-mt-s $BN-$CC-s lib$BN-mt lib$BN \
					lib$BN-$CC-mt lib$BN-$CC lib$BN-$CC-mt-s lib$BN-$CC-s \
					$BN-mgw-mt $BN-mgw $BN-mgw-mt-s $BN-mgw-s \
					$BN-$CC-mt-$BOOSTLIB_MDW_VERSION ; do
                LDFLAGS="${LDFLAGS} -l$ax_lib"
    			AC_CACHE_CHECK(the name of the Boost::UnitTestFramework library,
	      					   ax_cv_boost_unit_test_framework,
						[AC_LANG_SAVE
			 AC_LANG_CPLUSPLUS
               AC_LINK_IFELSE([AC_LANG_PROGRAM([[@%:@include <boost/test/unit_test.hpp>]],
                               [[using boost::unit_test::test_suite;
                               test_suite* test= BOOST_TEST_SUITE( "Unit test example 1" ); return 0;]])],
                               [link_thread="yes"],[link_thread="no"])

			 AC_LANG_RESTORE
               ])
                LDFLAGS="${saved_ldflags}"
			    if test "x$link_thread" = "xyes"; then
                    BOOST_UNIT_TEST_FRAMEWORK_LIB="-l$ax_lib"
                    AC_SUBST(BOOST_UNIT_TEST_FRAMEWORK_LIB)
					break
				fi
              done
			    if test "x$link_thread" = "xno"; then
				   AC_MSG_NOTICE(Could not link against $ax_lib !)
				fi
			fi


		fi dnl endif test "$succeeded"

        CPPFLAGS="$CPPFLAGS_SAVED"
        LDFLAGS="$LDFLAGS_SAVED"

	fi dnl endif test "x$want_boost"
])
