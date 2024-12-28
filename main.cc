#include "deck.h"
#include "orderbook.h"
#include <iostream>
#include <random>

using namespace std;

int main() {
    int eventCount = 0;
    const int maxEvents = 100;
    const float lambda = 0.25;

    Player* p1 = new Player("p1");
    Player* p2 = new Player("p2");

    Deck newDeck = Deck();

    newDeck.createFiggieDeck();

    std::vector<Player* > players = {p1, p2};

    newDeck.dealCards(players);

    orderBook heart;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> expDist(lambda);

    float p1look = expDist(gen);
    float p2look = expDist(gen);
    float currentTime = 0.0;

    p1->playerStatus();
    p2->playerStatus();

    while (eventCount < maxEvents) {
        if (currentTime >= p1look) {
            // Player 1 looks at the market
            eventCount++;
            p1look += expDist(gen);
            Order* o1 = new Order(p1, 2, 0, 2); 
            heart.addOrder(o1);
            // p1.strategy();
        }
        if (currentTime >= p2look) {
            // Player 1 looks at the market
            eventCount++;
            p2look += expDist(gen);
            Order* o2 = new Order(p2, 2, 1, 2);
            heart.addOrder(o2);
            // p1.strategy();
        }
        currentTime += 0.01;
        
    }
    p1->playerStatus();
    p2->playerStatus();
    return 0;
}


