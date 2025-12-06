# cpp-limit-order-book

A high-performance Limit Order Book (LOB) implementation in C++, designed to simulate low-latency matching engines used in High-Frequency Trading (HFT). The engine processes randomized, high-volume order streams and reports real-time execution metrics and a trade audit trail.

## Overview
This project implements a standard **Price-Time Priority** matching algorithm. It focuses on computational efficiency and memory safety, utilizing **modern C++ (C++17/20)** features to handle order lifecycles.

## Key Features
* **Order Matching:** Real-time matching of Bids and Asks using standard FIFO logic.
* **Data Structures:** Utilizes `std::map` (Red-Black Tree) for O(log n) price level management and `std::list` for order time priority.
* **Modern C++:** Implements strict type safety with `enum class`.

## Quantitative Benchmark

The matching engine's performance was measured by processing 50,000 randomly generated, high-volume orders (with 33% aggression chance) on a single thread. The results confirm a high-throughput, accurate implementation.

* **Throughput (Speed):** Achieved a stable **0.93 Million Order Operations/Second**.
* **Fill Rate (Accuracy):** Maintained a near-perfect **49.84% Quantity Fill Rate**, validating the symmetric Price-Time Priority matching logic against balanced synthetic market data.

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

## Usage
Upon running the executable, the program will prompt for the simulation size:
```
Input the number of operations that you want to run. The number should be a non-negative integer as the input.
To exit the program, press ctrl-c (command-c for mac).
```

## Sample Output (copy and pasted from terminal)
This is how the output looks when `./obExec` is run on the terminal with 50000 as the input.

```
--- BENCHMARK RESULTS ---
Total Operations: 50000
Total Time: 53.689445 ms
THROUGHPUT: 0.93 Million Ops/s

--- TOTAL TRADE HISTORY ---
Total Trades Executed: 49844
Total Quantity Traded: 311614075
Quantity Fill Rate: 49.84%

--- FINAL BOOK STATE ---
Bid Levels (Prices): 27
Ask Levels (Prices): 3
Total Resting Volume: 1963878
```

## References
* Logic based on standard limit order book architecture (e.g., QuantStart, market microstructure literature).