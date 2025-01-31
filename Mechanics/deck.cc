#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "deck.h"

int Deck::createFiggieDeck() {
    std::vector<int> suitCounts = {10, 10, 12, 8};
    std::mt19937 rng(static_cast<unsigned>(std::time(0)));
    std::shuffle(suitCounts.begin(), suitCounts.end(), rng);

    int goalSuit = -1;
    for (int i = 0; i < 4; ++i) {
        if (suitCounts[i] == 12) {
            if (i % 2 == 0) {
                goalSuit = i + 1;
            } else {
                goalSuit = i - 1;
            }
        }
    }
    cards.clear();

    for (int suit = 0; suit < 4; ++suit) {
        for (int count = 0; count < suitCounts[suit]; ++count) {
            cards.push_back({suit});
        }
    }

    std::shuffle(cards.begin(), cards.end(), rng);

    static const char* suitNames[] = {"Spade", "Club", "Heart", "Diamond"};
    for (int suit = 0; suit < 4; ++suit) {
        std::cout << suitNames[suit] << ": " << suitCounts[suit] << " cards\n";
    }
    std::cout << std::endl;
    return goalSuit;
}

void Deck::dealCards(std::vector<Player* >& players) {
    if (cards.empty()) {
        std::cerr << "Error: Deck is empty. Create and shuffle the deck first!" << std::endl;
        return;
    }

    cout << "Cards size: " << cards.size() << endl;

    int currPlayer = 0;
    for (int i = 0; i < cards.size(); i++) {
        int suit = cards[i].suit;
        players[currPlayer]->addToSuite(suit);
        players[currPlayer]->addToIntial(suit);
        currPlayer = (currPlayer + 1) % players.size();
    }
}


