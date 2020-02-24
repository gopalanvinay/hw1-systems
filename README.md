# HW1: Benchmarking the memory hierarchy

This project deals with empirically determining the sizes of the different cache layers in a processor by building a micro-benchmark that measures memory performance for different request sizes.

## Part 1
In order to read random bytes of data over many iterations without adding any overhead to the measurement, I decided to first initialize a `buffer` of size i and fill it with random values, then create a vector `idxs` of indices from 0 to i-1 and shuffle their ordering at random.

Inside my second loop of many iterations, I first pick a 'random index' by using `idx = idxs[j]`, and then time a single byte read from the position `buffer[idx]`. This introduces some randomness in the byte read without employing any arithmetic or random generators which add significant overhead. I chose 2^8 as the number of iterations because that gave me the most useful and readable graph as opposed to other higher powers of 2.

## Part 2
A graph of latency (ns) per memory read is given in the following image:

![Latency per memory read](/plots/cache_latencies2.png)

## Part 3
    1. In the graph, the spikes represent the sudden increase in fetching/reading time from a location in memory, which means the spikes represent where the hardware was forced to use a larger cache to store the buffer.
    From the graph, we can speculate due to the spike in fetching/reading time at 64KB that the L1 cache is of size 64KB. Similarly, the spikes at 256KB and ~2.2MB tell us that the L2 and L3 caches are of size 256KB and 2-3MB respectively. 

    2. My numbers for fetches from L2 (with mutex assuming both cores are under use) and main memory seem to line up (taking into account slight overheads), however I didn't get an order of 10^0 nanoseconds for any measurement from the L1 cache, probably due to the overhead of all processes such as Chrome, VSCode and the Linux VM running on my machine at the same time.

    3. From the System Report on my Mac (Early 2011), I learn that my machine uses a Core i5 processor (2 cores) which has an L1 cache of 64KB per core, L2 cache of size 256KB and  L3 cache of size 3MB. These measurements line up with my guesses in part 1.