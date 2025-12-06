#include "../include/OrderBook.hpp"

#include <algorithm>

void OrderBook::matchOrder(Order& order) {
    if (order.type == OrderType::BUY) {
        auto it = asks.begin();
        while (order.quantity > 0 && it != asks.end() && it -> first <= order.price) {
            while (order.quantity > 0 && !it -> second.empty()) {
                Order& resting_order = it->second.front();
                uint32_t resting_id = resting_order.id;
                double price = it->first;
                long long minQty = std::min(resting_order.quantity, order.quantity);

                resting_order.quantity -= minQty;
                order.quantity -= minQty;
                if (resting_order.quantity == 0) {
                    it -> second.pop_front();
                }

                /*
                 * a struct to analyze orderBook performance
                 * records the trade and pushes it back to trade_history
                 */
                Trade executed_trade {
                    price,
                    minQty,
                    (order.type == OrderType::BUY) ? order.id : resting_id,
                    (order.type == OrderType::BUY) ? resting_id : order.id,
                    static_cast<uint64_t>(
                        std::chrono::duration_cast<std::chrono::nanoseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                        ).count() 
                    )
                };
                trade_history.push_back(executed_trade);
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
                Order& resting_order = it->second.front();
                uint32_t resting_id = resting_order.id;
                double price = it->first;
                long long minQty = std::min(resting_order.quantity, order.quantity);
                
                resting_order.quantity -= minQty;
                order.quantity -= minQty;
                if (resting_order.quantity == 0) {
                    it -> second.pop_front();
                }

                /*
                 * a struct to analyze orderBook performance
                 * records the trade and pushes it back to trade_history
                 */
                Trade executed_trade {
                    price,
                    minQty,
                    (order.type == OrderType::BUY) ? order.id : resting_id,
                    (order.type == OrderType::BUY) ? resting_id : order.id,
                    static_cast<uint64_t>(
                        std::chrono::duration_cast<std::chrono::nanoseconds>(
                            std::chrono::high_resolution_clock::now().time_since_epoch()
                        ).count() 
                    )
                };
                trade_history.push_back(executed_trade);
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
        if (type == OrderType::BUY) {
            bids[order.price].emplace_back(order);
        } else {
            asks[order.price].emplace_back(order);
        }
    }
}

BookDepth OrderBook::getDepth() const {
    BookDepth depth = {};
    
    depth.bid_price_levels = bids.size();
    for (const auto& [price, order_list] : bids) {
        for (const auto& order : order_list) {
            depth.bid_total_volume += order.quantity;
        }
    }
    
    depth.ask_price_levels = asks.size();
    for (const auto& [price, order_list] : asks) {
        for (const auto& order : order_list) {
            depth.ask_total_volume += order.quantity;
        }
    }
    return depth;
}