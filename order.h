#include <iostream>
#include <string>
#include "player.h"

using namespace std;

class Order {
    Player player;
    float price;
    int direction; // 0 for bid and 1 for ask
    int suite;
    public:
        Player getPlayer();
        int getDirection();
        float getPrice();
        int getSuite();
};
