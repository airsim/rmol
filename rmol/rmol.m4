# Configure path for the RMOL library.
# Denis Arnaud <denis_arnaud@users.sourceforge.net>, February 2007


AC_DEFUN([AM_PATH_RMOL],
[
AC_ARG_WITH(rmol-prefix,[  --with-rmol-prefix=PFX   Prefix where RMOL is installed (optional)],
            rmol_prefix="$withval", rmol_prefix="")
AC_ARG_WITH(rmol-exec-prefix,[  --with-rmol-exec-prefix=PFX Exec prefix where RMOL is installed (optional)],
            rmol_exec_prefix="$withval", rmol_exec_prefix="")
AC_ARG_ENABLE(rmoltest, [  --disable-rmoltest       Do not try to compile and run a test RMOL program],
		    , enable_rmoltest=yes)

  if test "x${RMOL_CONFIG+set}" != xset ; then
     if test "x$rmol_prefix" != x ; then
         RMOL_CONFIG="$rmol_prefix/bin/rmol-config"
     fi
     if test "x$rmol_exec_prefix" != x ; then
        RMOL_CONFIG="$rmol_exec_prefix/bin/rmol-config"
     fi
  fi

  AC_PATH_PROG(RMOL_CONFIG, rmol-config, no)
  min_rmol_version=ifelse([$1], ,0.11.0,$1)
  AC_MSG_CHECKING(for RMOL - version >= $min_rmol_version)
  no_rmol=""
  if test "$RMOL_CONFIG" = "no" ; then
    no_rmol=yes
  else
    RMOL_CFLAGS=`$RMOL_CONFIG --cflags`
    RMOL_LIBS=`$RMOL_CONFIG --libs`

    rmol_major_version=`$RMOL_CONFIG --version | \
           sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${rmol_major_version}" = "x" ; then
       rmol_major_version=0
    fi

    rmol_minor_version=`$RMOL_CONFIG --version | \
           sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${rmol_minor_version}" = "x" ; then
       rmol_minor_version=0
    fi

    rmol_micro_version=`$RMOL_CONFIG --version | \
           sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${rmol_micro_version}" = "x" ; then
       rmol_micro_version=0
    fi

    if test "x$enable_rmoltest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $RMOL_CFLAGS"
      LIBS="$LIBS $RMOL_LIBS"

      rm -f conf.rmoltest
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

  system ("touch conf.rmoltest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_rmol_version");

  n = sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) ;

  if (n != 2 && n != 3) {
     printf("%s, bad version string\n", "$min_rmol_version");
     exit(1);
   }

   if (($rmol_major_version > major) ||
      (($rmol_major_version == major) && ($rmol_minor_version > minor)) ||
      (($rmol_major_version == major) && ($rmol_minor_version == minor) && ($rmol_micro_version >= micro)))
    {
      exit(0);
    }
  else
    {
      printf("\n*** 'rmol-config --version' returned %d.%d.%d, but the minimum version\n", $rmol_major_version, $rmol_minor_version, $rmol_micro_version);
      printf("*** of RMOL required is %d.%d.%d. If rmol-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If rmol-config was wrong, set the environment variable RMOL_CONFIG\n");
      printf("*** to point to the correct copy of rmol-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      exit(1);
    }
}

],, no_rmol=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_rmol" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$RMOL_CONFIG" = "no" ; then
       echo "*** The rmol-config script installed by RMOL could not be found"
       echo "*** If RMOL was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the RMOL_CONFIG environment variable to the"
       echo "*** full path to rmol-config."
     else
       if test -f conf.rmoltest ; then
        :
       else
          echo "*** Could not run RMOL test program, checking why..."
          CFLAGS="$CFLAGS $RMOL_CFLAGS"
          LIBS="$LIBS $RMOL_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding RMOL or finding the wrong"
          echo "*** version of RMOL. If it is not finding RMOL, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means RMOL was incorrectly installed"
          echo "*** or that you have moved RMOL since it was installed. In the latter case, you"
          echo "*** may want to edit the rmol-config script: $RMOL_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
#     RMOL_CFLAGS=""
#     RMOL_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(RMOL_CFLAGS)
  AC_SUBST(RMOL_LIBS)
  rm -f conf.rmoltest
])


