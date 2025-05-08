AC_INIT([smolmath],[0.1],[LowByteFox])
AC_CONFIG_AUX_DIR([build])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_PROG_CC

AC_SUBST([CONFIGURE_PATH],["$0"])
AC_SUBST([CONFIG_ARGS],["$(echo $ac_configure_args | tr -d \"\'\")"])

AH_TOP([#pragma once])
AH_BOTTOM([#include "compile_args.h"])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([Makefile])

AC_OUTPUT
