# Configure path for the GNU Scientific Library
# Christopher R. Gabriel <cgabriel@linux.it>, April 2000


AC_DEFUN([AM_PATH_GLPK],
[
AC_ARG_WITH(glpk,[  --with-glpk=PFX   Prefix where GLPK is installed (optional)],
            glpk_prefix="$withval", glpk_prefix="/usr")
AC_ARG_ENABLE(glpktest, [  --disable-glpktest       Do not try to compile and run a test GLPK program],
		    , enable_glpktest=yes)

  if test "x${GLPK_CONFIG+set}" != xset ; then
     if test "x$glpk_prefix" != x ; then
         GLPK_CONFIG="$glpk_prefix/bin/glpsol"
     fi
  fi

  AC_PATH_PROG(GLPK_CONFIG, glpsol, no)
  min_glpk_version=ifelse([$1], ,0.2.5,$1)
  AC_MSG_CHECKING(for GLPK - version >= $min_glpk_version)
  no_glpk=""
  if test "$GLPK_CONFIG" = "no" ; then
    no_glpk=yes
  else
    GLPK_CFLAGS="-I$glpk_prefix/include"
    GLPK_LIBS="-L$glpk_prefix/lib -lglpk"

    glpk_major_version=`$GLPK_CONFIG --version | \
           cut -d\  -f 5 | grep 4 | \
           sed 's/^\([[0-9]]*\).*/\1/'`
    if test "x${glpk_major_version}" = "x" ; then
       glpk_major_version=0
    fi

    glpk_minor_version=`$GLPK_CONFIG --version | \
           cut -d\  -f 5 | grep 4 | \
           sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\2/'`
    if test "x${glpk_minor_version}" = "x" ; then
       glpk_minor_version=0
    fi

    glpk_micro_version=`$GLPK_CONFIG --version | \
           cut -d\  -f 5 | grep 4 | \
           sed 's/^\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\)\.\{0,1\}\([[0-9]]*\).*/\3/'`
    if test "x${glpk_micro_version}" = "x" ; then
       glpk_micro_version=0
    fi

    if test "x$enable_glpktest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $GLPK_CFLAGS"
      LIBS="$LIBS $GLPK_LIBS"

      rm -f conf.glpktest
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

  system ("touch conf.glpktest");

  /* HP/UX 9 (%@#!) writes to sscanf strings */
  tmp_version = my_strdup("$min_glpk_version");

  n = sscanf(tmp_version, "%d.%d.%d", &major, &minor, &micro) ;

  if (n != 2 && n != 3) {
     printf("%s, bad version string\n", "$min_glpk_version");
     exit(1);
   }

   if (($glpk_major_version > major) ||
      (($glpk_major_version == major) && ($glpk_minor_version > minor)) ||
      (($glpk_major_version == major) && ($glpk_minor_version == minor) && ($glpk_micro_version >= micro)))
    {
      exit(0);
    }
  else
    {
      printf("\n*** 'glpk-config --version' returned %d.%d.%d, but the minimum version\n", $glpk_major_version, $glpk_minor_version, $glpk_micro_version);
      printf("*** of GLPK required is %d.%d.%d. If glpk-config is correct, then it is\n", major, minor, micro);
      printf("*** best to upgrade to the required version.\n");
      printf("*** If glpk-config was wrong, set the environment variable GLPK_CONFIG\n");
      printf("*** to point to the correct copy of glpk-config, and remove the file\n");
      printf("*** config.cache before re-running configure\n");
      exit(1);
    }
}

],, no_glpk=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
       CFLAGS="$ac_save_CFLAGS"
       LIBS="$ac_save_LIBS"
     fi
  fi
  if test "x$no_glpk" = x ; then
     AC_MSG_RESULT(yes)
     ifelse([$2], , :, [$2])     
  else
     AC_MSG_RESULT(no)
     if test "$GLPK_CONFIG" = "no" ; then
       echo "*** The glpk-config script installed by GLPK could not be found"
       echo "*** If GLPK was installed in PREFIX, make sure PREFIX/bin is in"
       echo "*** your path, or set the GLPK_CONFIG environment variable to the"
       echo "*** full path to glpk-config."
     else
       if test -f conf.glpktest ; then
        :
       else
          echo "*** Could not run GLPK test program, checking why..."
          CFLAGS="$CFLAGS $GLPK_CFLAGS"
          LIBS="$LIBS $GLPK_LIBS"
          AC_TRY_LINK([
#include <stdio.h>
],      [ return 0; ],
        [ echo "*** The test program compiled, but did not run. This usually means"
          echo "*** that the run-time linker is not finding GLPK or finding the wrong"
          echo "*** version of GLPK. If it is not finding GLPK, you'll need to set your"
          echo "*** LD_LIBRARY_PATH environment variable, or edit /etc/ld.so.conf to point"
          echo "*** to the installed location  Also, make sure you have run ldconfig if that"
          echo "*** is required on your system"
	  echo "***"
          echo "*** If you have an old version installed, it is best to remove it, although"
          echo "*** you may also be able to get things to work by modifying LD_LIBRARY_PATH"],
        [ echo "*** The test program failed to compile or link. See the file config.log for the"
          echo "*** exact error that occured. This usually means GLPK was incorrectly installed"
          echo "*** or that you have moved GLPK since it was installed. In the latter case, you"
          echo "*** may want to edit the glpk-config script: $GLPK_CONFIG" ])
          CFLAGS="$ac_save_CFLAGS"
          LIBS="$ac_save_LIBS"
       fi
     fi
#     GLPK_CFLAGS=""
#     GLPK_LIBS=""
     ifelse([$3], , :, [$3])
  fi
  AC_SUBST(GLPK_CFLAGS)
  AC_SUBST(GLPK_LIBS)
  rm -f conf.glpktest
])


