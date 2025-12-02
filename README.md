# cpp-limit-order-book

A high-performance Limit Order Book (LOB) implementation in C++, designed to simulate low-latency matching engines used in High-Frequency Trading (HFT).

## Overview
This project implements a standard **Price-Time Priority** matching algorithm. It focuses on computational efficiency and memory safety, utilizing **modern C++ (C++17/20)** features to handle order lifecycles.

## Key Features
* **Order Matching:** Real-time matching of Bids and Asks using standard FIFO logic.
* **Data Structures:** Utilizes `std::map` (Red-Black Tree) for O(log n) price level management and `std::list` for order time priority.
* **Modern C++:** Implements strict type safety with `enum class` and memory management via smart pointers.

## References
* Logic based on standard limit order book architecture (e.g., QuantStart, market microstructure literature).