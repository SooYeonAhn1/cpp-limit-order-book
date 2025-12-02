#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include <list>
#include <utility>
#include <cstdint>
#include <functional>

class OrderBook {
public:
    enum class OrderType {
        BUY,
        SELL,
    };
    struct Order {
        uint32_t id;
        double price;
        long long quantity;
        OrderType type;
    };
    OrderBook() = default;
    ~OrderBook() = default;
    void matchOrder(Order& order);
    void addOrder(uint32_t id, double price, long long quantity, OrderType type);
private:
    std::map<double, std::list<Order>> asks;
    std::map<double, std::list<Order>, std::greater<double>> bids;
};
#endif // ORDER_BOOK_HPP