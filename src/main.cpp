#include <iostream>
#include <cassert>
#include "Order.h"
using namespace std;

int main() {
    cout<<"LOB Day-1 Check"<<endl;

    //sample buy order
    Order samplebuy(101, Intent::Buy, OrderType::Limit, 10050, 50, 1000);
    samplebuy.display();

    //validate initial state of samplebuy order
    assert(!samplebuy.is_filled());
    assert(samplebuy.open_quantity == 50);

    //partial fill
    samplebuy.fill(20);
    cout<<"filled 20 shared"<<endl;
    samplebuy.display();
    assert(!samplebuy.is_filled());
    assert(samplebuy.open_quantity == 30);

    //remaining fill
    samplebuy.fill(30);
    cout<<"filled remaining 30 shared"<<endl;
    samplebuy.display();
    assert(samplebuy.is_filled());
    assert(samplebuy.open_quantity == 0);   

    cout<<"Day-1 [PASSED]"<<endl;
    return 0;
}