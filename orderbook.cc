#include "orderbook.h"

void orderBook::addOrder(Order* o) {
    float bestBid = getBestBidPrice();
    float bestAsk = getBestAskPrice();
    int direction = o->getDirection();
    float orderPrice = o->getPrice();
    
    
    if (direction == 0) { // bid
        if (orderPrice > bestBid && orderPrice < bestAsk) {
            bids.emplace_back(o);
        } else if (orderPrice > bestBid && orderPrice >= bestAsk) {
            
            if (o->getPlayer()->getStack() > orderPrice && asks.back()->getPlayer()->getSuiteCount(o->getSuite()) > 0 && 
                (asks.back()->getPlayer()->getName() != o->getPlayer()->getName())) {
                // check if bidder has enough money to make trade and seller has inventory
                executeTrade(o->getSuite(), orderPrice, o->getPlayer(), asks.back()->getPlayer());
                // asks[0]->getPlayer()->playerStatus();
                if (asks.back()->getPlayer()->getName() != o->getPlayer()->getName()) {
                    cout << asks.back()->getPlayer()->getName() << " sold 1 " << o->getSuite() << " to " << o->getPlayer()->getName() << " at " << orderPrice << endl;
                }
                
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
                if (bids.back()->getPlayer()->getStack() > orderPrice && o->getPlayer()->getSuiteCount(o->getSuite()) > 0 && 
                    (bids.back()->getPlayer()->getName() != o->getPlayer()->getName())) {
                    // execute trade, reset orderbook
                    executeTrade(o->getSuite(), bestBid, bids.back()->getPlayer(), o->getPlayer());
                    // o->getPlayer()->playerStatus();
                    if (bids.back()->getPlayer()->getName() != o->getPlayer()->getName()) {
                        cout << o->getPlayer()->getName() << " sold 1 " << o->getSuite() << " to " << bids.back()->getPlayer()->getName() << " at " << bestBid << endl;
                    }
                    resetBook();
                }
            }
        }
    }
}

void orderBook::deleteBid(Player* player) {
    for (auto it = bids.begin(); it != bids.end(); ++it) {
        if ((*it)->getPlayer()->getName() == player->getName()) {
            Order *deletingOrder = (*it);
            bids.erase(it);
            delete deletingOrder;
        }
    }
}


void orderBook::deleteAsk(Player* player) {
    for (auto it = asks.begin(); it != asks.end(); ++it) {
        if ((*it)->getPlayer()->getName() == player->getName()) {
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
    Player* player = o->getPlayer();
    if (direction == 0) {
        deleteBid(player);
        addOrder(o);
    } else {
        deleteAsk(player);
        addOrder(o);
    }
}



Order* orderBook::getBestBid() { return bids.back(); }

Order* orderBook::getBestAsk() { return asks.back(); }

float orderBook::getBestBidPrice() {
    if (!bids.empty()) {
        return bids.back()->getPrice();
    } else {
        return -1;  // Or some default value indicating no bids
    }
}

float orderBook::getBestAskPrice() {
    if (!asks.empty()) {
        return asks.back()->getPrice();
    } else {
        return 100000000;  // Or some default value indicating no asks
    }
}


void orderBook::executeTrade(int suite, int tradePrice, Player* bidder, Player* asker) {
    bidder->addToSuite(suite);
    asker->removeFromSuite(suite); 
    bidder->removeFromStack(tradePrice);
    asker->addToStack(tradePrice);
    tradeLog.emplace_back(bidder, asker, suite, tradePrice);
}

void orderBook::printBook() {
    cout << "Bids: " << endl;
    for (auto it: bids) {
        cout << it->getPlayer()->getName() << " " << it->getPrice() << endl;
    }
    cout << "Asks: " << endl;
    for (auto it: asks) {
        cout << it->getPlayer()->getName() << " " << it->getPrice() << endl;
    }
}

std::vector<Trade> orderBook::getTrades() { return tradeLog; }

