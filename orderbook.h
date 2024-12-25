#include <iostream>
#include "order.h"
#include <vector>

class orderBook {
    string suite;
    std::vector<Order *> bids;
    std::vector<Order *> asks;
    public:
        void addOrder(Order* o);
        void deleteOrder(string player);
        void resetBook();
        void updateOrder(Order* o);
        Order* getBestBid();
        Order* getBestAsk();
};

