#include <iostream>
#include "order.h"
#include "player.h"
#include <vector>

class orderBook {
    string suite;
    std::vector<Order *> bids;
    std::vector<Order *> asks;
    public:
        void addOrder(Order* o);
        void deleteBid(int player);
        void deleteAsk(int player);
        void resetBook();
        void updateOrder(Order* o);
        Order* getBestBid();
        Order* getBestAsk();
        void executeTrade(int suite, int tradePrice, Player bidder, Player asker);
};

