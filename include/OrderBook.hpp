#ifndef ORDER_BOOK_HPP
#define ORDER_BOOK_HPP

#include <map>
#include <cstdlib>
#include <cstdint>

class OrderBook {
public:
    struct Order {
        uint32_t id;
        double price;
        int quantity;
    };
    enum class OrderType {
        BUY,
        SELL,
    };
    OrderBook();
    ~OrderBook();
    void matchOrder(Order order, OrderType type);
    void addOrder(uint32_t id, double price, int quantity, OrderType type);
private:
    std::map<int, std::pair<double, int>> bidBook;
    std::map<int, std::pair<double, int>> askBook;
};
#endif // ORDER_BOOK_HPP