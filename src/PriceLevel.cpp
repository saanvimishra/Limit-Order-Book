#include "PriceLevel.h"

//returns iterator to the inserted order
std::list<Order>::iterator PriceLevel::add_order(const Order& order) {
    total_quantity += order.open_quantity;
    return orders.insert(orders.end(), order);
}

//removes an order from anywhere in the list using its iterator
void PriceLevel::remove_order(std::list<Order>::iterator order_iter) {
    total_quantity -= order_iter->open_quantity;
    orders.erase(order_iter); 
}

//reduces total quantity at this price level when an order is filled (or partially filled)
void PriceLevel::reduce_quantity(uint32_t filled_quantity) {
    if (filled_quantity > total_quantity) { //bug check, should never happen
        total_quantity = 0;
    } else {
        total_quantity -= filled_quantity;
    }
}

