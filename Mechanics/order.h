#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include "player.h"

using namespace std;


class Order {
    Player* player;
    float price;
    int direction; // 0 for bid and 1 for ask
    int suite;
    public:
        Order(Player* player, float price, int direction, int suite): player(player), price(price), 
        direction(direction), suite(suite) {}
        Player* getPlayer();
        int getDirection();
        float getPrice();
        int getSuite();
};

#endif // ORDER_H
