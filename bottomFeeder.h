#ifndef BOTTOMFEEDER_H
#define BOTTOMFEEDER_H

#include <iostream>
#include "player.h"
#include "orderbook.h"
#include "probability.h"

class bottomFeeder: public Player {
    public:
        void strategy(std::vector<orderBook*> books, std::vector<Player* > players);
};


#endif // BOTTOMFEEDER_H