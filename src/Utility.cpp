#include "../include/Utility.hpp"

#include <random>
#include <cmath>

// static initialization to generate random numbers
static std::random_device rd;
static std::mt19937 gen(rd());
static std::normal_distribution<> price_dist(100.00, 0.1);
static std::uniform_int_distribution<long long> qty_dist(1, 1000);

Order generate_random_order(uint32_t id_counter, double mid_price) {
    // decide price
    double price = price_dist(gen);
    price = std::round(price * 100.0) / 100.0;

    // decide quantity
    long long quantity = qty_dist(gen);

    // decide type of order
    OrderType type = (std::rand() % 2 == 0) ? OrderType::BUY : OrderType::SELL;

    if (std::rand() % 10 == 0) {
        if (type == OrderType::BUY) {
            price += 1.00;
        } else {
            price -= 1.00;
        }
    }

    return {id_counter, price, quantity, type};
}