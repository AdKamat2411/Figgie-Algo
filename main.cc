#include "deck.h"
#include "orderbook.h"
#include "noisy.h"
#include "EVtrader.h"
#include <iostream>
#include <random>

using namespace std;

int main() {
    int eventCount = 0;
    const int maxEvents = 10000;
    const float lambda = 0.25;

    Noisy* p1 = new Noisy("p1");
    Noisy* p2 = new Noisy("p2");
    EVtrader* p3 = new EVtrader("p3");
    EVtrader* p4 = new EVtrader("p4");

    Deck newDeck = Deck();

    int goalSuit = newDeck.createFiggieDeck();

    std::vector<Player* > players = {p1, p2, p3, p4};

    newDeck.dealCards(players);

    std::vector<orderBook*> books = {new orderBook(), new orderBook(), new orderBook(), new orderBook()};

    std::random_device rd;
    std::mt19937 gen(rd());
    std::exponential_distribution<> expDist(lambda);

    float p1look = expDist(gen);
    float p2look = expDist(gen);
    float p3look = expDist(gen);
    float p4look = expDist(gen);
    float currentTime = 0.0;

    p1->playerStatus();
    p2->playerStatus();
    p3->playerStatus();
    p4->playerStatus();

    float pot = 0.0;
    for (int i = 0; i < 4; i++) {
        players[i]->removeFromStack(50.0);
    }
    pot += 200.0;
    cout << "Pot is " << pot << endl;

    while (eventCount < maxEvents) {
        if (currentTime >= p1look) {
            // Player 1 looks at the market
            eventCount++;
            p1look += expDist(gen);
            p1->strategy(books);
        }
        if (currentTime >= p2look) {
            // Player 2 looks at the market
            eventCount++;
            p2look += expDist(gen);
            // Order* o2 = new Order(p2, 2, 1, 2);
            // books[2]->addOrder(o2);
            p2->strategy(books);
        }
        if (currentTime >= p3look) {
            // Player 2 looks at the market
            eventCount++;
            p3look += expDist(gen);
            // Order* o2 = new Order(p2, 2, 1, 2);
            // heart.addOrder(o2);
            p3->strategy(books, players);
        }
        if (currentTime >= p4look) {
            // Player 2 looks at the market
            eventCount++;
            p4look += expDist(gen);
            // Order* o2 = new Order(p2, 2, 1, 2);
            // heart.addOrder(o2);
            p4->strategy(books, players);
            // for (int i = 0; i < 4; i++) {
            //     cout << "Book is " << i << endl;
            //     books[i]->printBook();
            // }
        }
        currentTime += 0.01;
        
    }
    std::cout << "Goal suit is " << goalSuit << std::endl;
    int majorityOwnerVal = 0;
    for (int i = 0; i < 4; i++) {
        int goalSuiteCount = players[i]->getSuiteCount(goalSuit);
        if (goalSuiteCount > majorityOwnerVal) {
            majorityOwnerVal = goalSuiteCount;
        }
        players[i]->addToStack(10*players[i]->getSuiteCount(goalSuit));
        pot -= 10*players[i]->getSuiteCount(goalSuit);
    }
    std::vector<int> majorityOwners;
    for (int i = 0; i < 4; i++) {
        if (players[i]->getSuiteCount(goalSuit) == majorityOwnerVal) {
            majorityOwners.push_back(i);
        }
    }
    for (int i = 0; i < majorityOwners.size(); i++) {
        players[majorityOwners[i]]->addToStack(pot/majorityOwners.size());
    }
    p1->playerStatus();
    p2->playerStatus();
    p3->playerStatus();
    p4->playerStatus();
    return 0;
}


