#include "OrderBook.h"
#include <iostream>
#include <iomanip>

using namespace std;

bool OrderBook::add_resting_order(const Order& order) {
    if (order.is_filled() || order_map.find(order.id) != order_map.end()) {
        return false; // order is already filled or already exists
    }

    if(order.intent == Intent::Buy) {
        auto level_iter = bids.find(order.price_cents);
        if (level_iter == bids.end()) {
            //create and insert new price level if it doesn't exist
            level_iter = bids.insert(make_pair(order.price_cents, PriceLevel(order.price_cents))).first;
        }
        auto list_iter = level_iter->second.add_order(order);
        order_map[order.id] = OrderLocation{Intent::Buy, order.price_cents, list_iter};
    }
    else {
        auto level_iter = asks.find(order.price_cents);
        if (level_iter == asks.end()) {
            //create and insert new price level if it doesn't exist
            level_iter = asks.insert(make_pair(order.price_cents, PriceLevel(order.price_cents))).first;
        }
        auto list_iter = level_iter->second.add_order(order);
        order_map[order.id] = OrderLocation{Intent::Sell, order.price_cents, list_iter};
    }

    return true;
}

bool OrderBook::cancel_order(uint64_t order_id) {
    auto map_iter = order_map.find(order_id);
    if (map_iter == order_map.end()) {
        return false; // order not found
    }

    OrderLocation loc = map_iter->second;

    if (loc.intent == Intent::Buy) {
        auto level_iter = bids.find(loc.price_cents);
        if (level_iter != bids.end()) {
            level_iter->second.remove_order(loc.order_iter);
            if (level_iter->second.is_empty()) {
                bids.erase(level_iter); // remove empty price level
            }
        }
    } else {
        auto level_iter = asks.find(loc.price_cents);
        if (level_iter != asks.end()) {
            level_iter->second.remove_order(loc.order_iter);
            if (level_iter->second.is_empty()) {
                asks.erase(level_iter); // remove empty price level
            }
        }
    }
    order_map.erase(map_iter); // remove order from map
    return true;
}

bool OrderBook::get_best_bid(uint32_t& out_price) const {
    if (bids.empty()) {
        return false; // no bids available
    }
    out_price = bids.begin()->first;
    return true;
}

bool OrderBook::get_best_ask(uint32_t& out_price) const {
    if (asks.empty()) {
        return false; // no asks available
    }
    out_price = asks.begin()->first;
    return true;
}

void OrderBook::print_order_book() const {
    cout<< "\n------------------------------------------\n";
    cout<< "            LIMIT ORDER BOOK\n";
    cout<< "------------------------------------------\n";

    cout<< " ASKS (Lowest sell first)\n";
    for (const auto& ask_pair : asks) {
        const PriceLevel& level = ask_pair.second;
        cout<< "Price: $" << fixed << setprecision(2) << level.get_price() / 100.0
            << ", Total Quantity: " << level.get_total_quantity()
            << ", Orders: " << level.get_order_count() << "\n";
    }

    cout<< " BIDS (Highest buy first)\n";
    for (const auto& bid_pair : bids) {
        const PriceLevel& level = bid_pair.second;
        cout<< "Price: $" << fixed << setprecision(2) << level.get_price() / 100.0
            << ", Total Quantity: " << level.get_total_quantity()
            << ", Orders: " << level.get_order_count() << "\n";
    }
}