#ifndef BOTTOMFEEDER_H
#define BOTTOMFEEDER_H

#include <iostream>
#include "../Mechanics/player.h"
#include "../Mechanics/orderbook.h"
#include "probability.h"


class bottomFeeder: public Player {
    std::vector<int> playerIdx;
    int pastTrades;
    bool makeDecision();
    public:
        bottomFeeder(string name, std::vector<int> playerIdx, int k): Player(name), playerIdx(playerIdx), pastTrades(k) {}
        void strategy(std::vector<orderBook*> books, std::vector<Player* > players);
        float getAvgPrice(std::vector<Player* > players, int Idx, orderBook* book);
};


#endif // BOTTOMFEEDER_H