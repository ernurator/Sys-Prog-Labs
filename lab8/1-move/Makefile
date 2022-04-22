
CC := gcc
RC := rustc

# Flags to be passed to the C compiler.
CFLAGS += -ggdb3 -Wall -Wextra -std=gnu11

all: c rust

c:
	$(CC) $(CFLAGS) -O3 move.c -o move_c

rust:
	${RC} move.rs -o move_rs

clean:
	rm -f move_c move_rs 


.PHONY: all clean
