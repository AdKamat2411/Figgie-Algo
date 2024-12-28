#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include "deck.h"

void Deck::createFiggieDeck() {
    std::vector<int> suitCounts = {10, 10, 12, 8};
    std::mt19937 rng(static_cast<unsigned>(std::time(0)));
    std::shuffle(suitCounts.begin(), suitCounts.end(), rng);

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
}

void Deck::dealCards(std::vector<Player>& players) {
    if (cards.empty()) {
        std::cerr << "Error: Deck is empty. Create and shuffle the deck first!" << std::endl;
        return;
    }

    const int cardsPerPlayer = cards.size() / players.size();

    for (size_t i = 0; i < players.size(); ++i) {
        for (int j = 0; j < cardsPerPlayer; ++j) {
            const Card& card = cards[i * cardsPerPlayer + j];
            players[i].addToSuite(card.suit);
        }
    }
}


