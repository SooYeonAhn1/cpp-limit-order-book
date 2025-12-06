#include "include/OrderBook.hpp"
#include "include/Utility.hpp"

#include <iostream>
#include <chrono> // to record benchmarks
#include <iomanip>

void printDepth(const BookDepth& depth) {
    std::cout << "\n--- FINAL BOOK STATE ---\n";
    std::cout << "Bid Levels (Prices): " << depth.bid_price_levels << std::endl;
    std::cout << "Ask Levels (Prices): " << depth.ask_price_levels << std::endl;
    std::cout << "Total Resting Volume: " << depth.bid_total_volume + depth.ask_total_volume << std::endl;
}

void printTradeHistory(const std::vector<Trade>& history, long long total_submitted_quantity) {
    long long total_traded_quantity = 0;
    for (const auto& trade : history) {
        total_traded_quantity += trade.quantity;
    }

    double fill_rate = (double)total_traded_quantity / total_submitted_quantity;
    std::cout << "\n--- TOTAL TRADE HISTORY ---" << std::endl;
    std::cout << "Total Trades Executed: " << history.size() << std::endl;
    std::cout << "Total Quantity Traded: " << total_traded_quantity << std::endl;
    std::cout << "Quantity Fill Rate: " << std::fixed << std::setprecision(2) << fill_rate * 100.0 << "%" << std::endl;
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
    
    std::cout << "\n--- BENCHMARK RESULTS ---" << std::endl;
    std::cout << "Total Operations: " << numOrders << std::endl;
    std::cout << "Total Time: " << std::fixed << std::setprecision(6) 
              << total_seconds * 1000.0 << " ms" << std::endl;

    std::cout << "THROUGHPUT: " << std::fixed << std::setprecision(2)
              << ops_per_second / 1000000.0 << " Million Ops/s" << std::endl;

    // prints trade history of virtual data
    printTradeHistory(ob.getTradeHistory(), total_submitted_quantity);

    // prints the final book state
    printDepth(ob.getDepth());
}

int main() {
    uint64_t operations = 0;
    std::string input_buffer;
    while (true) {
        std::cout << "Input the number of operations that you want to run. The number should be a non-negative integer as the input." << std::endl;
        std::cout << "To exit the program, press ctrl-c (command-c for mac)." << std::endl;
        std::getline(std::cin, input_buffer);

        if (input_buffer.empty() || 
            !std::all_of(input_buffer.begin(), input_buffer.end(), ::isdigit)) {
            
            std::cout << "\n[Invalid Input] Please insert a positive integer (no decimals or negatives).\n";
            continue; // Restart the loop
        }

        try {
            operations = std::stoull(input_buffer);
            break;
        } catch (...) {
            std::cout << "\n[Invalid Input] Number is too large.\n";
        }
    }

    runBenchmark(operations);
    return 0;
}