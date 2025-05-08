compile_args.h:
	echo '#pragma once' > compile_args.h
	echo '#define CONFIGURE_ARGS "$(CONFIGURE_PATH) $(CONFIG_ARGS)"' >> compile_args.h

bin_PROGRAMS = smolmath
smolmath_SOURCES = main.c

BUILT_SOURCES = compile_args.h
CLEANFILES = compile_args.h
