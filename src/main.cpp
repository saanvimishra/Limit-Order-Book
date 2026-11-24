#include <iostream>
#include <cassert>
#include "Order.h"
#include "PriceLevel.h"
#include "OrderBook.h"
using namespace std;

int main() {
    cout<< "Order Book Test" << endl;

    OrderBook book;
    uint32_t best_bid=0, best_ask=0;

    assert(book.is_empty());
    assert(!book.get_best_bid(best_bid));
    assert(!book.get_best_ask(best_ask));

    //add resting buy orders
    book.add_resting_order(Order(1, Intent::Buy, OrderType::Limit, 10000, 50, 1000));
    book.add_resting_order(Order(2, Intent::Buy, OrderType::Limit, 10050, 30, 2000)); //best bid
    book.add_resting_order(Order(3, Intent::Buy, OrderType::Limit, 10050, 20, 3000));

    //add resting sell orders
    book.add_resting_order(Order(4, Intent::Sell, OrderType::Limit, 10150, 40, 4000));
    book.add_resting_order(Order(5, Intent::Sell, OrderType::Limit, 10100, 25, 5000)); //best ask

    book.print_order_book();

    assert(book.active_order_count() == 5);
    assert(book.get_best_bid(best_bid) && best_bid == 10050);
    assert(book.get_best_ask(best_ask) && best_ask == 10100);

    //cancel order 5
    assert(book.cancel_order(5)== true);
    assert(book.cancel_order(5) == false);

    //best ask must shift to 10150
    assert(book.get_best_ask(best_ask) && best_ask == 10150);
    assert(book.active_order_count() == 4);

    book.print_order_book();

    cout<< "All tests passed!" << endl;    
    return 0;
}