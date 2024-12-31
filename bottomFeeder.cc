#include "bottomFeeder.h"
#include <map>
#include <algorithm>
#include <numeric>
#include <random>

void bottomFeeder::strategy(std::vector<orderBook*> books, std::vector<Player* > players) {
    for (int bookNum = 0; bookNum < 4; bookNum++) {
        float sum = 0;
        for (int x: playerIdx) {
            sum += getAvgPrice(players, x, books[bookNum]);
        }
        float eXprice = sum / playerIdx.size();

        bool direction = makeDecision();
        if (direction == 0) {
            float limitBuyPrice = std::min(eXprice, books[bookNum]->getBestAskPrice());
            Order* buyOrder = new Order(this, limitBuyPrice, 0, bookNum);
            books[bookNum]->addOrder(buyOrder);
        } else {
            float limitSellPrice = std::max(eXprice, books[bookNum]->getBestBidPrice());
            Order* buyOrder = new Order(this, limitSellPrice, 1, bookNum);
            books[bookNum]->addOrder(buyOrder);
        }
    }
    
}

float bottomFeeder::getAvgPrice(std::vector<Player* > players, int Idx, orderBook* book) {
    Player* currP = players[Idx];
    std::vector<Trade> trades = book->getTrades();
    std::vector<float> buyPrices;
    std::vector<float> sellPrices;

    for (auto trade: trades) {
        if (trade.buyer == currP) {
            buyPrices.push_back(trade.price);
        } else if (trade.seller == currP) {
            sellPrices.push_back(trade.price);
        }
    }

    if (buyPrices.size() < pastTrades || sellPrices.size() < pastTrades) {
        return 0;
    }

    std::vector<float> recentBuyPrices(buyPrices.end() - pastTrades, buyPrices.end());
    std::vector<float> recentSellPrices(sellPrices.end() - pastTrades, sellPrices.end());

    float buyMean = std::accumulate(recentBuyPrices.begin(), recentBuyPrices.end(), 0.0f) / pastTrades;
    float sellMean = std::accumulate(recentSellPrices.begin(), recentSellPrices.end(), 0.0f) / pastTrades;

    return (buyMean + sellMean) / 2.0f;
}   



bool bottomFeeder::makeDecision() {
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

float generateUniform(double lower, double upper) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(lower, upper);
    return dis(gen);
}



