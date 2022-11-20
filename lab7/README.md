# Lab 7

After modifying the code and running the `make check`, no diff can be observed:
```shell
~/kbtu/sysprog/cs300-s22-labs/lab7$ make check
g++ -g -Wall -Wextra -Wpedantic -fsanitize=address -std=c++11 -o revindex_threads revindex_threads.cpp
./revindex_sequential books < input.txt > output_sequential.txt
./revindex_threads books < input.txt > output_parallel.txt
diff output_parallel.txt output_sequential.txt
```

Threads implementation time:
```shell
~/kbtu/sysprog/cs300-s22-labs/lab7$ time ./revindex_threads books < input.txt
...
real    0m16.161s
user    0m43.589s
sys     0m0.742s
```

Sequential implementation time:
```shell
~/kbtu/sysprog/cs300-s22-labs/lab7$ time ./revindex_sequential books < input.txt
...
real    0m38.246s
user    0m37.317s
sys     0m0.686s
```
