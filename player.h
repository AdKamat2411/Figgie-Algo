#ifndef PLAYER_H
#define PLAYER_H

#include <string>

using namespace std;

class Player {
    string name;
    float stack;
    int suiteCount [4]; // 0: spade, 1: club, 2: heart, 3: diamond
    
    public:
        Player(string name): name{name}, stack(300.0), suiteCount{0,0,0,0} {};
        float getStack();
        float getSuiteCount(int index);
        void addToStack(float amount);
        void addToSuite(int index);
        void removeFromStack(float amount);
        void removeFromSuite(int index);
        string getName();
        void playerStatus();
};

#endif // PLAYER_H
