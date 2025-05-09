AC_INIT([smolmath],[0.1],[LowByteFox])
AC_CONFIG_AUX_DIR([build])
AM_INIT_AUTOMAKE([foreign subdir-objects -Wall -Werror])
AC_PROG_CC
AC_PROG_LEX([yywrap])
AC_PROG_YACC
AC_CHECK_LIB([m], [pow])

AC_ARG_WITH([backend],
  [AS_HELP_STRING([--with-backend=BACKEND], [Choose numeric backend: float32, float64, float128])],
  [backend=$withval],
  [backend=float64])


case "$backend" in
    float32)
        AC_DEFINE([BACKEND_FLOAT32], [1], [32 bit floating point number])
        ;;
    float64)
        AC_DEFINE([BACKEND_FLOAT64], [1], [64 bit floating point number])
        ;;
    float128)
        AC_DEFINE([BACKEND_FLOAT128], [1], [128 bit floating point number])
        ;;
    *)
        AC_MSG_ERROR([Invalid backend: $backend. Choose one of: float32, float64, float128])
        ;;
esac

AC_SUBST([CONFIGURE_PATH],["$0"])
AC_SUBST([CONFIG_ARGS],["$(echo $ac_configure_args | tr -d \"\'\")"])

AH_TOP([#pragma once])
AH_BOTTOM([#include "compile_args.h"])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
