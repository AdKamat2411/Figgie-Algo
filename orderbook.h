#ifndef ORDERBOOK_H
#define ORDERBOOK_H

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
        void deleteBid(Player* player);
        void deleteAsk(Player* player);
        void resetBook();
        void updateOrder(Order* o);
        Order* getBestBid();
        Order* getBestAsk();
        float getBestBidPrice();
        float getBestAskPrice();
        void executeTrade(int suite, int tradePrice, Player* bidder, Player* asker);
        void printBook();
};

#endif // ORDERBOOK_H
