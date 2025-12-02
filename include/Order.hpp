#ifndef ORDER_HPP
#define ORDER_HPP

#include <cstdint>

enum class OrderType : uint8_t {
    BUY,
    SELL,
};

struct Order {
    uint32_t id;
    double price;
    long long quantity;
    OrderType type;
};

#endif // ORDER_HPP