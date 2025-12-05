#ifndef TRADE_HPP
#define TRADE_HPP

#include <chrono>
#include <cstdint>

struct Trade {
    double price;
    long long quantity;
    uint32_t buyer_order_id;
    uint32_t seller_order_id;
    uint64_t timestamp;
};

#endif // TRADE_HPP