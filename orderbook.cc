#include "orderbook.h"

void orderBook::addOrder(Order* o) {
    float bestBid = getBestBid()->getPrice();
    float bestAsk = getBestAsk()->getPrice();
    int direction = o->getDirection();
    int orderPrice = o->getPrice();
    
    if (direction == 0) { // bid
        if (orderPrice > bestBid && orderPrice < bestAsk) {
            bids.emplace_back(o);
        } else if (orderPrice > bestBid && orderPrice >= bestAsk) {
            
            if (o->getPlayer().getStack() > orderPrice && asks[0]->getPlayer().getSuiteCount(o->getSuite()) > 0) {
                // check if bidder has enough money to make trade and seller has inventory
                executeTrade(o->getSuite(), orderPrice, o->getPlayer(), asks[0]->getPlayer());
                // reset book
                resetBook();
            }
        } 
    }
    else { // asks
        if (orderPrice < bestAsk) {
            if (orderPrice > bestBid) {
                asks.emplace_back(o);
            }
            else{
                // check if bidder has enough money and seller has inventory
                if (o->getPlayer().getStack() > orderPrice && asks[0]->getPlayer().getSuiteCount(o->getSuite()) > 0) {
                    // execute trade, reset orderbook
                    executeTrade(o->getSuite(), bestBid, bids[0]->getPlayer(), o->getPlayer());
                    resetBook();
                }
            }
        }
    }
}

void orderBook::deleteBid(int player) {
    for (auto it = bids.begin(); it != bids.end(); ++it) {
        if ((*it)->getPlayer() == player) {
            Order *deletingOrder = (*it);
            bids.erase(it);
            delete deletingOrder;
        }
    }
}


void orderBook::deleteAsk(int player) {
    for (auto it = asks.begin(); it != asks.end(); ++it) {
        if ((*it)->getPlayer() == player) {
            Order *deletingOrder = (*it);
            asks.erase(it);
            delete deletingOrder;
        }
    }
}

void orderBook::resetBook() {
    for (auto it: bids) {
        delete it;
    }
    bids.clear();
    for (auto it: asks) {
        delete it;
    }
    asks.clear();
}

void orderBook::updateOrder(Order* o) {
    int direction = o->getDirection();
    int player = o->getPrice();
    if (direction == 0) {
        deleteBid(player);
        addOrder(o);
    } else {
        deleteAsk(player);
        addOrder(o);
    }
}



Order* orderBook::getBestBid() { return bids[0]; }

Order* orderBook::getBestAsk() { return asks[0]; }

void orderBook::executeTrade(int suite, int tradePrice, Player bidder, Player asker) {
    bidder.addToSuite(suite);
    asker.removeFromSuite(suite); 
    bidder.removeFromStack(tradePrice);
    asker.addToStack(tradePrice);
}

