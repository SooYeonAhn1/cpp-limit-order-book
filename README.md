# cpp-limit-order-book

A high-performance Limit Order Book (LOB) implementation in C++, designed to simulate low-latency matching engines used in High-Frequency Trading (HFT). The engine processes randomized, high-volume order streams and reports real-time execution metrics and a trade audit trail.

## Overview
This project implements a standard **Price-Time Priority** matching algorithm. It focuses on computational efficiency and memory safety, utilizing **modern C++ (C++17/20)** features to handle order lifecycles.

## Key Features
* **Order Matching:** Real-time matching of Bids and Asks using standard FIFO logic.
* **Data Structures:** Utilizes `std::map` (Red-Black Tree) for O(log n) price level management and `std::list` for order time priority.
* **Modern C++:** Implements strict type safety with `enum class`.
Design note: std::map was chosen over a hash map because price levels must stay ordered for best-bid/ask lookup; the ordering requirement outweighs the O(1) average lookup a hash map would give.

## Quantitative Benchmark

The matching engine's performance was measured by processing 5000000 randomly generated, high-volume orders (with 33% aggression chance) on a single thread. The results confirm a high-throughput, accurate implementation.

* **Throughput (Speed):** Achieved a stable **3.64 Million Order Operations/Second**.
* **Fill Rate (Sanity Check):** The **50.00% quantity fill rate** matches the expected value for symmetric synthetic order flow, confirming the matching logic has no directional bias.

## Running the program
First clone the repository and change directory to the cloned repository
```
$ git clone https://github.com/SooYeonAhn1/cpp-limit-order-book
$ cd cpp-limit-order-book
```

Enter the build directory
```
$ mkdir build # only needs to be done at initial build
$ cd build
```

Run the following commands
```
$ cmake ..
$ make
$ ./obExec
```

Upon running the executable, the program will prompt for the simulation size:
```
Input the number of operations that you want to run. The number should be a non-negative integer as the input.
To exit the program, press ctrl-c (command-c for mac).
```

## Sample Output (copy and pasted from terminal)
This is how the output looks when `./obExec` is run on the terminal with 5000000 as the input.

```
--- BENCHMARK RESULTS ---
Total Operations: 5000000
Total Time: 1373.532569 ms
THROUGHPUT: 3.64 Million Ops/s

--- TOTAL TRADE HISTORY ---
Total Trades Executed: 4999614
Total Quantity Traded: 31244701243
Quantity Fill Rate: 50.00%

--- FINAL BOOK STATE ---
Bid Levels (Prices): 28
Ask Levels (Prices): 1
Total Resting Volume: 1725325
```

## References
* Logic based on standard limit order book architecture (e.g., QuantStart, market microstructure literature).