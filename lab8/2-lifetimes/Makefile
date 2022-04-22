
CC := gcc
RC := rustc

# Flags to be passed to the C compiler.
CFLAGS += -ggdb3 -Wall -Wextra -std=gnu11 -Wno-uninitialized

all: c rust

# -O1 is required to make the bug apparent in the c progam
c:
	$(CC) $(CFLAGS) -O1 lifetimes.c -o lifetimes_c

rust:
	${RC} lifetimes.rs -o lifetimes_rs

clean:
	rm -f lifetimes_c lifetimes_rs


.PHONY: all clean
