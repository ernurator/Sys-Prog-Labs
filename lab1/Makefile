.PHONY: all clean format
CFLAGS = -Wall -Werror -Wextra -O3

all: reverse_test

clean:
	rm -f reverse_test test_reverse.o reverse.o

format:
	clang-format -style=Google -i test_reverse.c reverse.c reverse.h

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

reverse_test: test_reverse.o reverse.o
	gcc $^ -o $@
