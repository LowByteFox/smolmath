compile_args.h:
	echo '#pragma once' > compile_args.h
	echo '#define CONFIGURE_ARGS "$(CONFIGURE_PATH) $(CONFIG_ARGS)"' >> compile_args.h

bin_PROGRAMS = smolmath
smolmath_SOURCES = main.c ast.c lexer.l parser.y

AM_YFLAGS = -d -Wcounterexamples
AM_LFLAGS =

BUILT_SOURCES = compile_args.h parser.h
CLEANFILES = compile_args.h parser.h
