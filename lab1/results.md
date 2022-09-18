## Assignment part 1

### Reverse strings

```bash
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ gcc test_reverse.c reverse.c -o reverse_test && ./reverse_test 2 hello world
world hello 
Testing for correctness...
=================== Running Reverse Tests. ===================
Reverse: Passed 5 tests, Failed 0 tests | 100.000000%
```

## Assignmnet part 2

### Warning flags

```bash
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ gcc -Wall -Werror -Wextra test_reverse.c reverse.c -o reverse_test
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ ./reverse_test 2 csci 300
300 csci 
Testing for correctness...
=================== Running Reverse Tests. ===================
Reverse: Passed 5 tests, Failed 0 tests | 100.000000%
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ ./reverse_test 2 csci  # ended with error
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ ./reverse_test 2 csci 300 500  # ended with error
```

### Optimizations

```bash
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ gcc -Wall -Werror -Wextra -O3 test_reverse.c reverse.c -o reverse_test && ./reverse_test 
Testing for correctness...
=================== Running Reverse Tests. ===================
Reverse: Passed 5 tests, Failed 0 tests | 100.000000%
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ time ./reverse_test
Testing for correctness...
=================== Running Reverse Tests. ===================
Reverse: Passed 5 tests, Failed 0 tests | 100.000000%

real    0m0.037s
user    0m0.008s
sys     0m0.025s
```

## Assignment part 3

### Makefiles

```makefile
reverse_test: test_reverse.c reverse.c reverse.h
	gcc test_reverse.c reverse.c -o reverse_test
```

```bash
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ make reverse_test
gcc test_reverse.c reverse.c -o reverse_test
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ ls reverse_test
reverse_test
```

### Variables

```makefile
CFLAGS = -Wall -Werror -Wextra -O3

reverse_test: test_reverse.c reverse.c reverse.h
	gcc $(CFLAGS) test_reverse.c reverse.c -o $@
```

```bash
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ make reverse_test
gcc -Wall -Werror -Wextra -O3 test_reverse.c reverse.c -o reverse_test
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ ./reverse_test 
Testing for correctness...
=================== Running Reverse Tests. ===================
Reverse: Passed 5 tests, Failed 0 tests | 100.000000%
```

### Phony Targets

```makefile
.PHONY: all clean format
CFLAGS = -Wall -Werror -Wextra -O3

all: reverse_test

clean:
	rm -f reverse_test

format:
	clang-format -style=Google -i test_reverse.c reverse.c reverse.h

reverse_test: test_reverse.c reverse.c reverse.h
	gcc $(CFLAGS) test_reverse.c reverse.c -o $@
```

### Simplifying Linking

```makefile
.PHONY: all clean format
CFLAGS = -Wall -Werror -Wextra -O3

all: reverse_test

clean:
	rm -f reverse_test test_reverse.o reverse.o

format:
	clang-format -style=Google -i test_reverse.c reverse.c reverse.h

reverse.o: reverse.c
	gcc $(CFLAGS) -c $< -o $@

test_reverse.o: test_reverse.c reverse.h
	gcc $(CFLAGS) -c $< -o $@

reverse_test: test_reverse.o reverse.o
	gcc $^ -o $@
```

```bash
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ make
gcc -Wall -Werror -Wextra -O3 -c test_reverse.c -o test_reverse.o
gcc -Wall -Werror -Wextra -O3 -c reverse.c -o reverse.o
gcc test_reverse.o reverse.o -o reverse_test
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ ./reverse_test 
Testing for correctness...
=================== Running Reverse Tests. ===================
Reverse: Passed 5 tests, Failed 0 tests | 100.000000%
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ make clean
rm -f reverse_test test_reverse.o reverse.o
```

### Pattern Rules

```makefile
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
```

```bash
ernurator@ernurator-osx:~/kbtu/sysprog/cs300-s22-labs/lab1$ make
gcc -Wall -Werror -Wextra -O3 -c test_reverse.c -o test_reverse.o
gcc -Wall -Werror -Wextra -O3 -c reverse.c -o reverse.o
gcc test_reverse.o reverse.o -o reverse_test
```
