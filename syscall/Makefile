## [M1]
#  
#   MAKEFILE_LIST variable has the make files  names in the order pasrsed by 'make'.
#  $(lastword $(MAKEFILE_LIST)) is Makefile (name of the current makefile).
#  'realpath' command prints the resolved absolute path of current makefile.
#  'dirname' elimates non-directory suffixes.
#  Hence CUR_DIR variable holds the absolute path of the code-socket directory. 
CUR_DIR := $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))

## [M2]
#   gcc  is used to compile the C language code and create executables.
# The CFLAGS command expands the contents when the compiler is invoked.-g option generates the debug information to be used by the gdb debugger.-O2 is used to turn on all optimization flag mentioned by -O.-Werror makes all the warnings into errors.-Wall enables all compilers warning messages.
#LDFLAGS is used for linker flags.
#  ...
CC = gcc
CFLAGS += -g -O2 -Werror -Wall
LDFLAGS +=

## [M3]
#  DEPS_DIR includes all  the dependent directories from the current directory.
#  ...
DEPS_DIR  := $(CUR_DIR)/.deps$(LIB_SUFFIX)
DEPCFLAGS = -MD -MF $(DEPS_DIR)/$*.d -MP

## [M5]
#  A list of all the .c files irrespective of file name is obtained using the wildcard function and stored in SRC_FILES.
#  ...
SRC_FILES = $(wildcard *.c)

## [M6]
# All the .c files that were extracted,their executables are  stored  in EXE_FILES.
#  ...
EXE_FILES = $(SRC_FILES:.c=)

## [M7]
# 'all' is the target here.
#all the names of the files in EXE_FILES are echoed.
all: $(EXE_FILES)
	echo $(EXE_FILES)

## [M8]
#  # This compiles each C file in the ./deps directory(folder containing dependencies).
# The rule is
#       gcc -g -O2 -Werror -Wall -MD -MF /.deps$*.d -MP -c $@ @<
# where $* will hold the pattern % which is ultimately the name of the C file.
#       $@ holds the target %/%.c 
#       $< evaluates to the name of the c file (%.c)
#  ...
%/%.c:%.c $(DEPS_DIR)
	$(CC) $(CFLAGS) $(DEPCFLAGS) -c $@ $<

## [M9]
#  All the executables in EXE_FILES are forcefully removed.
#  ...
clean:
	rm -f $(EXE_FILES)

## [M10]
#  Phony target is used to specify targets with no prerequistes. Phony targets are not real files names but names for the recipes.
#  Here targets 'all'and 'clean' are phony targets and they will  not be  executed by make until specified while running make.
#  ...
.PHONY: all clean
