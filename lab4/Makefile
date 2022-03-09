# CSCI 1310 general use Makefile
#
# Notes:
# For Makefile syntax help visit https://devhints.io/makefile. For any questions please
# consult course resources, a TA or the internet.

# Targets that our compilation produces
EXEC := w01-byte matrixMultiply	# Executables

# The compiler we use (do we need a specific version?)
CC := gcc

# Compiler options
CFLAGS := -std=gnu11 -Wall -pedantic	# Flags for C compilation

# rules that are listed as .PHONY do not produce an output file
.PHONY: all clean

####################################################################
#################### RULES #########################################
####################################################################

# rules made when make is called with no rule specified
all: $(EXEC)

# Executable rule - link compiled objects into executables
%: %.o
	$(CC) $(CFLAGS) $^ -O3 -o $@

# Object rule - Compile every .c file in the source directory into an object file
%.o : %.c
	$(CC) $(strip $(CFLAGS)) $^ -c -o $@

# Clean rule - Remove all files that are produced by the compilation process
clean:
	@ rm -rf $(OBJFILES) $(EXEC) $(DBG) data
