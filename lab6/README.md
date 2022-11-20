## Part 1

After modifying the code:
```shell
~/kbtu/sysprog/cs300-s22-labs/lab6/shell$ ./300sh 
300sh> /bin/ls
300sh       Makefile    builtin.cpp builtin.h   builtin.o   sh.cpp      sh.o
300sh> /bin/cat Makefile
CXX = g++
CXXFLAGS = -g3 -Wall -Wextra -Wconversion -Wcast-align -g -fsanitize=address

.PHONY: all clean format

all: 300sh

format:
        clang-format -style=Google -i *.cpp

%.o: %.cpp
        $(CXX) $(CXXFLAGS) -c $< -o $@

300sh: sh.o builtin.o
        $(CXX) $(CXXFLAGS) $^ -o $@

clean:
        rm -f 300sh *.o
```

## Part 2

After modifying the code and running the `make check`, no diff can be observed:
```shell
~/kbtu/sysprog/cs300-s22-labs/lab6/multiProcs$ make check
g++ -g -Wall -Wextra -Wpedantic -fsanitize=address -std=c++11 -o revindex_parallel revindex_procs.cpp
./revindex_sequential books < input.txt > output_sequential.txt
./revindex_parallel books < input.txt > output_parallel.txt
diff output_parallel.txt output_sequential.txt
```

Parallel implementation time:
```shell
~/kbtu/sysprog/cs300-s22-labs/lab6/multiProcs$ time ./revindex_parallel books < input.txt
...
real    0m17.921s
user    0m42.443s
sys     0m6.822s
```

Sequential implementation time:
```shell
~/kbtu/sysprog/cs300-s22-labs/lab6/multiProcs$ time ./revindex_sequential books < input.txt
...
real    0m37.625s
user    0m37.001s
sys     0m0.507s
```
