#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include <map>
#include <unordered_map>
#include <list>
#include <cstdint>
#include "Order.h"
#include "PriceLevel.h"

// location data of data stored in hashmap for order lookup
struct OrderLocation {
    Intent intent;
    uint32_t price_cents;
    std::list<Order>::iterator order_iter;
};

class OrderBook {
private:
    // buy ladder: highest bid at begin()
    std::map<uint32_t, PriceLevel, std::greater<uint32_t>> bids;
    //key: price, value: PriceLevel queue

    // sell ladder: lowest ask at begin()
    std::map<uint32_t, PriceLevel> asks;
    //key: price, value: PriceLevel queue

    // hashmap for order lookup by order id
    std::unordered_map<uint64_t, OrderLocation> order_map;
    //maps order id to order location

public:
    OrderBook() = default;

    // insert a resting limit order into the order book
    bool add_resting_order(const Order& order);

    // cancel an existing order by its order id
    bool cancel_order(uint64_t order_id);

    bool get_best_bid(uint32_t& out_price) const;
    bool get_best_ask(uint32_t& out_price) const;
    size_t active_order_count() const { return order_map.size(); }
    bool is_empty() const { return bids.empty() && asks.empty(); }

    void print_order_book() const;
};

#endif