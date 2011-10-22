dnl
dnl Real-Time library (librt)
dnl

AC_DEFUN([AC_CHECK_LIBRT],
[
   AC_MSG_CHECKING([for librt])

   rt_found="no"
   for dir in /lib /usr/lib /usr/local/lib; do
      if test -f "$dir/librt.so.1"; then
        rt_found="yes"
        break;
      fi
   done
   if test x_$rt_found = x_yes; then
        AC_SUBST(RT_LIBS,"-lrt")
	AC_MSG_RESULT([-lrt])
   else
        AC_SUBST(RT_LIBS,"")
        AC_MSG_RESULT([not needed])
   fi
])

