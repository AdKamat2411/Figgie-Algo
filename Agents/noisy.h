#ifndef NOISY_H
#define NOISY_H

#include "../Mechanics/player.h"
#include "../Mechanics/orderbook.h"
#include <vector>

class Noisy: public Player {
    bool makeDecision();
    float generateNormal(double mean, double variance);
    float generateUniform(double lower, double upper);
    public:
        Noisy(string name): Player(name) {}
        void strategy(std::vector<orderBook*> books);
};

#endif // NOISY_H
