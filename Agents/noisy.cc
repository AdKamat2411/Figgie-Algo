#include "noisy.h"
#include <random>
#include <iostream>

void Noisy::strategy(std::vector<orderBook*> books) {
    for (int bookNum = 0; bookNum < 4; bookNum++) {
        float maxBid = books[bookNum]->getBestBidPrice();
        if (maxBid <= 0) {
            continue;
        }
        // cout << "Max Bid is " << maxBid << endl; 
        float minSell = books[bookNum]->getBestAskPrice();
        // cout << "Reached here!" << endl;
        bool direction = makeDecision();
        
        float Z = generateNormal(0.0, 1.0);
        float pb = maxBid * exp(Z);
        if (direction == 0 && maxBid > 0) {
            float p = generateUniform(0.0, pb);
            float limitBuyPrice = std::min(p, minSell);
            Order* o1 = new Order(this, limitBuyPrice, 0, bookNum);
            books[bookNum]->addOrder(o1);
        } else if (direction == 1) {
            float p = generateUniform(pb, 2 * pb);
            float limitSellPrice = std::max(p, maxBid);
            Order* o2 = new Order(this, limitSellPrice, 1, bookNum);
            books[bookNum]->addOrder(o2);
        }
    }
}

bool Noisy::makeDecision() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    double randomValue = dis(gen);

    if (randomValue < 0.5) {
        return true;
    } else {
        return false;
    }
}

float Noisy::generateNormal(double mean, double variance) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(mean, sqrt(variance));
    return d(gen);
}

float Noisy::generateUniform(double lower, double upper) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lower, upper);
    return dis(gen);
}

