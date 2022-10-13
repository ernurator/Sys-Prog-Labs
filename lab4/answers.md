# Exercise 1
* `w01-byte` bytes/second: 44148
* `w02-byte` bytes/second: 631220
* `w03-byte` bytes/second: 1.61031e+07

# Exercise 2
### Scenario 1:
* How many array elements can fit into a cache block?
2
* What combination of parameters is producing the hit rate you observe? Think about the sizes of each of the parameters.
We get a miss on every second cache access, so current and next elements are pushed into the cache. On the next element, we get a hit.
* What is our hit rate if we increase Rep Count arbitrarily? Why?
0.5, because we get hit & miss cyclically (with cycle size equal to 2 elements). So hit rate doesn't depend on rep count in this scenario.

### Scenario 2:
* What combination of parameters is producing the hit rate you observe? Think about the sizes of each of the parameters.
For each cache access we get a miss, and write current and next elements into the cache. But since step size is 27, on the following iteration we get a miss again.
* What happens to our hit rate if we increase the number of blocks and why?
When number of blocks is larger than 1, we start to get non-zero hit rate. It is because there are only 2 values of an array accessed on each repetition, so we get hits on every repetition after the first one.

### Scenario 3:
* Choose a `number of blocks` greater than `1` and determine the smallest `block size` that uses every block *and* maximizes the hit rate given the parameters above. Explain why.
Number of blocks: 2
Block Size: 128
Hit rate: 126/128
Explanation: We are pushing the first half of an array to first block on the very first read & write, and the second half of the array is pushed to the second block after we iterate through half of the array.

# Exercise 3
* Order the functions from fastest to slowest, and explain why each function's ranking makes sense using your understanding of how the cache works. Some functions might have similar runtimes. If this is the case, explain why.
<!-- Fill this in -->
