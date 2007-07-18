# Configure path for the LATUS library.
# Denis Arnaud @ Amadeus/DEV-ORI <darnaud@amadeus.com>, March 2007


AC_DEFUN([AM_PATH_LATUS],
[
AC_ARG_WITH(latus-prefix,[  --with-latus-prefix=PFX   Prefix where LATUS is installed (optional)],
            latus_prefix="$withval", latus_prefix="")
AC_ARG_WITH(latus-exec-prefix,[  --with-latus-exec-prefix=PFX Exec prefix where LATUS is installed (optional)],
            latus_exec_prefix="$withval", latus_exec_prefix="")
AC_ARG_ENABLE(latustest, [  --disable-latustest       Do not try to compile and run a test LATUS program],
		    , enable_latustest=yes)

  if test "x${LATUS_CONFIG+set}" != xset ; then
     if test "x$latus_prefix" != x ; then
         LATUS_CONFIG="$latus_prefix/bin/latus-config"
     fi
     if test "x$latus_exec_prefix" != x ; then
        LATUS_CONFIG="$latus_exec_prefix/bin/latus-config"
     fi
  fi

  AC_PATH_PROG(LATUS_CONFIG, latus-config, no)
  min_latus_version=ifelse([$1], ,0.11.0,$1)
  AC_MSG_CHECKING(for LATUS - version >= $min_latus_version)
  no_latus=""
  if test "$LATUS_CONFIG" = "no" ; then
    no_latus=yes
  else
    LATUS_CFLAGS=`$LATUS_CONFIG --cflags`
    LATUS_LIBS=`$LATUS_CONFIG --libs`

    latus_major_version=`$LATUS_CONFIG --version | \
           sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${latus_major_version}" = "x" ; then
       latus_major_version=0
    fi

    latus_minor_version=`$LATUS_CONFIG --version | \
           sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${latus_minor_version}" = "x" ; then
       latus_minor_version=0
    fi

    latus_micro_version=`$LATUS_CONFIG --version | \
           sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${latus_micro_version}" = "x" ; then
       latus_micro_version=0
    fi

    if test "x$enable_latustest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $LATUS_CFLAGS"
      LIBS="$LIBS $LATUS_LIBS"

      rm -f conf.latustest
      AC_TRY_RUN([
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* my_strdup (const char *str);

char*
my_strdup (const char *str)
{
  char *new_str;
  
  if (str)
    {
      new_str = (char *)malloc ((strlen (str) + 1) * sizeof(char));
      strcpy (new_str, str);
    }
  else
    new_str = NULL;
  
  return new_str;
}

int main (void)
{
  int major = 0, minor = 0, micro = 0;
  int n;
  char *tmp_version;

  system ("touch conf.latustest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_latus_version");

  n = sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) ;

  if (n != 2 && n != 3) {
     printf("%s, bad version string\n", "$min_latus_version");
     exit(1);
   }

   if (($latus_major_version > major) ||
      (($latus_major_version == major) && ($latus_minor_version > minor)) ||
      (($latus_major_version == major) && ($latus_minor_version == minor) && ($latus_micro_version >= micro)))
    {
      exit(0);
    }
  else
    {
      printf("\n*** 'latus-config --version' returned %d.%d.%d, but the minimum version\n", $latus_major_version, $latus_minor_version, $latus_micro_version);
      printf("*** of LATUS required is %d.%d.%d. If latus-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If latus-config was wrong, set the environment variable LATUS_CONFIG\n");
      printf("*** to point to the correct copy of latus-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      exit(1);
    }
}

],, no_latus=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_latus" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$LATUS_CONFIG" = "no" ; then
       echo "*** The latus-config script installed by LATUS could not be found"
       echo "*** If LATUS was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the LATUS_CONFIG environment variable to the"
       echo "*** full path to latus-config."
     else
       if test -f conf.latustest ; then
        :
       else
          echo "*** Could not run LATUS test program, checking why..."
          CFLAGS="$CFLAGS $LATUS_CFLAGS"
          LIBS="$LIBS $LATUS_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding LATUS or finding the wrong"
          echo "*** version of LATUS. If it is not finding LATUS, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means LATUS was incorrectly installed"
          echo "*** or that you have moved LATUS since it was installed. In the latter case, you"
          echo "*** may want to edit the latus-config script: $LATUS_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
#     LATUS_CFLAGS=""
#     LATUS_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(LATUS_CFLAGS)
  AC_SUBST(LATUS_LIBS)
  rm -f conf.latustest
])


