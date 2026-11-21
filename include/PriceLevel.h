#ifndef PRICE_LEVEL_H
#define PRICE_LEVEL_H

#include <list>
#include <cstdint>
#include <cstdlib>
#include "Order.h"

class PriceLevel{
private:
    uint32_t price_cents; //price level in cents
    uint32_t total_quantity; //total quantity at this price level
    std::list<Order> orders; //list of orders at this price level

public:
    PriceLevel() : price_cents(0), total_quantity(0) {}

    explicit PriceLevel(uint32_t price) : price_cents(price), total_quantity(0) {}

    //append order to the back of the list and return iterator
    std::list<Order>::iterator add_order(const Order& order);

    //removes any order in the list in O(1) using its iterator
    void remove_order(std::list<Order>::iterator order_iter);

    //reduce total quantity when an order is filled (or partially filled)
    void reduce_quantity(uint32_t filled_quantity);

    //getters
    uint32_t get_price() const { return price_cents; }
    uint32_t get_total_quantity() const { return total_quantity; }
    bool is_empty() const { return orders.empty(); }
    size_t get_order_count() const { return orders.size(); }

    //access to the head of the order list for matching
    Order& front() { return orders.front(); }
};
#endif