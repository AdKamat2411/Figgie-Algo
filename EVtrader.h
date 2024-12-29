#ifndef EVTRADER_H
#define EVTRADER_H

#include "player.h"
#include "orderbook.h"
#include "probability.h"
#include <vector>


class EVtrader: public Player {
    public:
        EVtrader(string name): Player(name) {}
        void strategy(std::vector<orderBook*> books, std::vector<Player* > players);
};


#endif // EVTRADER_H