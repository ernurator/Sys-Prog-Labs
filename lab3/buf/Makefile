# CSCI 1310 Lab 3 Makefile

# Standard C compiler
CC := gcc

# Regular compilation flags
CFLAGS := -O0 -g -std=c99 -Wall -Werror -Wno-deprecated-declarations # Flags for C compilation

# Compilation flags that ensure that the stack is static and with no security measures
STACKFLAGS := -Wno-implicit -fno-stack-protector -no-pie -fno-pic -z execstack -z norelro

# rules that are listed as .PHONY do not produce an output file
.PHONY: all do_hack clean

all: buffer exploit

# Compile the hackable buffer program
buffer: buffer.c
	$(CC) $(CFLAGS) $(STACKFLAGS) -o $@ $^
	@ objdump -d $@ > buffer_asm.txt

# Compile the exploit printing program
exploit: exploit.c
	$(CC) $(CFLAGS) -o $@ $^

#dump contents of exploit to file
exploit_text1: exploit
	@ ./exploit > exploit1.txt

exploit_text2: exploit
	@ ./exploit > exploit2.txt

#pipe output of exploit printing program into buffer program
do_hack: buffer
	@ echo "Testing Buffer ... "
	./exploit | ./buffer


clean:
	@ rm -rf buffer exploit exploit1.txt  exploit2.txt buffer_asm.txt
