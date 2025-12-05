#include "include/OrderBook.hpp"
#include "include/Utility.hpp"

#include <iostream>
#include <chrono> // to record benchmarks
#include <iomanip>

void printTradeHistory(const std::vector<Trade>& history, long long total_submitted_quantity) {
    long long total_traded_quantity = 0;
    for (const auto& trade : history) {
        total_traded_quantity += trade.quantity;
    }

    double fill_rate = (double)total_traded_quantity / total_submitted_quantity;

    std::cout << "Total Trades Executed: " << history.size() << "\n";
    std::cout << "Total Quantity Traded: " << total_traded_quantity << "\n";
    std::cout << "Quantity Fill Rate: " << std::fixed << std::setprecision(2) << fill_rate * 100.0 << "%\n";
}

void runBenchmark(uint32_t numOrders) {
    OrderBook ob;
    uint32_t orderId = 1;

    auto start = std::chrono::high_resolution_clock::now();
    long long total_submitted_quantity = 0;
    for (uint32_t i = 0; i < numOrders; i++) {
        Order order = generateRandomOrder(orderId++, 100.0);
        total_submitted_quantity += order.quantity;
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

    // prints trade history of virtual data
    printTradeHistory(ob.getTradeHistory(), total_submitted_quantity);
}

int main() {
    runBenchmark(50000);
    return 0;
}