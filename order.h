#include <iostream>
#include <string>

using namespace std;

class Order {
    int player; // index of player in array of 4 players
    float price;
    int direction; // 0 for bid and 1 for ask
    string card;
    public:
        int getPlayer();
        int getDirection();
        float getPrice();
        string getCard();
};
