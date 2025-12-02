#include "include/OrderBook.hpp"
#include "include/Utility.hpp"

#include <iostream>
#include <chrono> // to record benchmarks
#include <iomanip>

void runBenchmark(uint32_t numOrders) {
    OrderBook ob;
    uint32_t orderId = 1;

    auto start = std::chrono::high_resolution_clock::now();

    for (uint32_t i = 0; i < numOrders; i++) {
        Order order = generateRandomOrder(orderId++, 100.0);
        ob.addOrder(order.id, order.price, order.quantity, order.type);
    }

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    double total_seconds = duration.count();
    
    double ops_per_second = static_cast<double>(numOrders) / total_seconds;
    
    std::cout << "\n--- BENCHMARK RESULTS ---\n";
    std::cout << "Total Operations: " << numOrders << "\n";
    std::cout << "Total Time: " << std::fixed << std::setprecision(6) 
              << total_seconds * 1000.0 << " ms\n";

    std::cout << "THROUGHPUT: " << std::fixed << std::setprecision(2)
              << ops_per_second / 1000000.0 << " Million Ops/s\n";
    std::cout << "--- END ---\n";
}

int main() {
    runBenchmark(50000);
    return 0;
}