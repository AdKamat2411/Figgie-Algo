#ifndef ORDERBOOK_H
#define ORDERBOOK_H

#include <iostream>
#include "order.h"
#include "player.h"
#include <vector>


struct Trade {
    Player* buyer;
    Player* seller;
    int suit;
    int price;
    Trade(Player* b, Player* s, int sType, int p): buyer(b), seller(s), suit(sType), price(p) {}
};

class orderBook {
    std::vector<Order *> bids;
    std::vector<Order *> asks;
    std::vector<Trade> tradeLog;
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
        std::vector<Trade> getTrades();
};

#endif // ORDERBOOK_H
