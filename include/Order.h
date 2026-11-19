#ifndef ORDER_H
#define ORDER_H

#include <cstdint>
#include <iostream>
#include <string>
#include <iomanip>

enum class Intent : uint8_t {
    Buy,
    Sell
};

enum class OrderType : uint8_t {
    Limit,
    Market
};

struct Order {
    uint64_t id;    //unique order identifier
    Intent intent;      //buy or sell
    OrderType type;     //limit or market
    uint32_t price_cents;
    uint32_t open_quantity;  //quantity currently open
    uint32_t total_quantity;    //total quantity for the order
    uint64_t timestamp;     //arrival time in nanoseconds
    
    // Constructor for the Order struct
    Order(uint64_t order_id, Intent order_intent, OrderType order_type, uint32_t price, uint32_t quantity, uint64_t arrival_time=0)
        : id(order_id), 
        intent(order_intent), 
        type(order_type), 
        price_cents(price), 
        open_quantity(quantity), 
        total_quantity(quantity), 
        timestamp(arrival_time) {}

    //checks if order is filled
    bool is_filled() const {
        return open_quantity == 0;
    }

    //partially or fully fills order
    void fill(uint32_t quantity){
        if (quantity > open_quantity) open_quantity = 0;
        else open_quantity -= quantity;
    }

    void display() const{
        std::cout<< "[Order #" << id << "] "
            << (intent == Intent::Buy ? "Buy " : "Sell ")
            << open_quantity << " out of " << total_quantity << " shares @ $"
            << std::fixed << std::setprecision(2) << price_cents / 100.0
            << (is_filled() ? " (FILLED)" : " (OPEN)")
            << "\n";
    }

};

#endif