#include <iostream>
#include <cassert>
#include "Order.h"
#include "PriceLevel.h"
using namespace std;

int main() {
    cout<< "Checking PriceLevel FIFO queue\n\n";

    PriceLevel level(10050); //price level $100.50
    assert(level.is_empty());
    assert(level.get_total_quantity() == 0);

    //adding some orders
    auto order1 = level.add_order(Order(1001, Intent::Buy, OrderType::Limit, 10050, 50, 1000));
    auto order2 = level.add_order(Order(1002, Intent::Buy, OrderType::Limit, 10050, 30, 2000));
    auto order3 = level.add_order(Order(1003, Intent::Buy, OrderType::Limit, 10050, 20, 3000));

    assert(level.get_order_count() == 3);
    assert(level.get_total_quantity() == 100);
    assert(level.front().id == 1001);

    //cancel the second order
    cout<< "Canceling order #1002\n";
    level.remove_order(order2);
    assert(level.get_order_count() == 2);
    assert(level.get_total_quantity() == 70);
    assert(level.front().id == 1001);
    assert(order3->id == 1003);

    //fill first order
    cout<< "Filling order #1001 for 30 shares\n";
    order1->fill(30);
    level.reduce_quantity(30);
    assert(level.get_total_quantity() == 40);

    //fill first order completely
    level.remove_order(order1);
    assert(level.get_order_count() == 1);
    assert(level.get_total_quantity() == 20);
    assert(level.front().id == 1003);

    cout<< "All tests passed!\n";
    return 0;
}