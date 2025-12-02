#include "../include/OrderBook.hpp"

#include <algorithm>

void OrderBook::matchOrder(Order& order) {
    if (order.type == OrderBook::OrderType::BUY) {
        auto it = asks.begin();
        while (order.quantity > 0 && it != asks.end() && it -> first <= order.price) {
            while (order.quantity > 0 && !it -> second.empty()) {
                long long qty = it -> second.front().quantity;
                long long minQty = std::min(qty, order.quantity);
                it -> second.front().quantity -= minQty;
                order.quantity -= minQty;
                if (it -> second.front().quantity == 0) {
                    it -> second.pop_front();
                }
            }
            if (it -> second.empty()) {
                it = asks.erase(it);
            } else {
                it++;
            }
        }
    } else {
        auto it = bids.begin();
        while (order.quantity > 0 && it != bids.end() && it -> first >= order.price) {
            while (order.quantity > 0 && !it -> second.empty()) {
                long long qty = it -> second.front().quantity;
                long long minQty = std::min(qty, order.quantity);
                it -> second.front().quantity -= minQty;
                order.quantity -= minQty;
                if (it -> second.front().quantity == 0) {
                    it -> second.pop_front();
                }
            }
            if (it -> second.empty()) {
                it = bids.erase(it);
            } else {
                it++;
            }
        }
    }
}

void OrderBook::addOrder(uint32_t id, double price, long long quantity, OrderType type) {
    Order order = {id, price, quantity, type};
    matchOrder(order);
    
    if (order.quantity > 0) {
        if (type == OrderBook::OrderType::BUY) {
            bids[order.price].emplace_back(order);
        } else {
            asks[order.price].emplace_back(order);
        }
    }
}