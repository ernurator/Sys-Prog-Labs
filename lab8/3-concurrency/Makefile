CPP := g++
RC := rustc
SHELL=/bin/bash

RED=\033[0;31m
GREEN=\033[0;32m
BLACK=\033[0m

# Flags to be passed to the C++ compiler.
CPPFLAGS	 += -std=c++17 -Wall -Wextra -g
THREADFLAGS	 += -O3 -pthread 

all: cpp rust

cpp: concurrency.cpp
	$(CPP) $(CPPFLAGS) $(THREADFLAGS) concurrency.cpp -o concurrency_cpp

rust: concurrency.rs
	${RC} concurrency.rs -o concurrency_rs

clean:
	rm -f concurrency_cpp concurrency_rs 

check: cpp rust
	@echo Checking C++ correctness
	@out=`for i in $$(seq 1 500); do ./concurrency_cpp; done | uniq | wc -l`; \
	if (( out == 1 )) ; then \
		printf '$(GREEN)No race conditions detected in C++ code$(BLACK)\n'; \
	else \
		printf '$(RED)Race conditions detecteded in C++ code (final balance varies between runs)$(BLACK)\n'; \
	fi
	@echo Checking Rust correctness
	@out=`for i in $$(seq 1 500); do ./concurrency_rs; done | uniq | wc -l`; \
	if (( out == 1 )) ; then \
		printf '$(GREEN)No race conditions detected in Rust code$(BLACK)\n'; \
	else \
		printf '$(RED)Race conditions detecteded in Rust code (final balance varies between runs)$(BLACK)\n'; \
	fi
	


.PHONY: all clean check
