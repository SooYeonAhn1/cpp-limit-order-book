#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include "Order.hpp"
#include "Trade.hpp"

#include <map>
#include <list>
#include <vector>
#include <utility>
#include <functional>

class OrderBook {
public:
    struct BookDepth {
        size_t bid_price_levels;
        long long bid_total_volume;
        size_t ask_price_levels;
        long long ask_total_volume;
    };
    OrderBook() = default;
    ~OrderBook() = default;
    void matchOrder(Order& order);
    void addOrder(uint32_t id, double price, long long quantity, OrderType type);
    const std::vector<Trade> getTradeHistory() const { return trade_history; }
private:
    std::map<double, std::list<Order>> asks;
    std::map<double, std::list<Order>, std::greater<double>> bids;
    std::vector<Trade> trade_history; // a vector to analyze orderBook the performace
};
#endif // ORDER_BOOK_HPP