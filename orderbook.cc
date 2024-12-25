#include "orderbook.h"

void orderBook::addOrder(Order* o) {
    float bestBid = this->getBestBid()->getPrice();
    float bestAsk = this->getBestAsk()->getPrice();
    int direction = o->getDirection();
    
    if (direction == 0) { // bid
        if (o->getPrice() > bestBid && o->getPrice() < bestAsk) {
            bids.push_back(o);
        }
    }
}

Order* orderBook::getBestBid() { return bids[0]; }

Order* orderBook::getBestAsk() { return asks[0]; }

