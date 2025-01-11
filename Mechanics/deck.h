#ifndef DECK_H
#define DECK_H

#include "player.h"
#include <vector>

struct Card {
    int suit;
};

class Deck {
    private:
        std::vector<Card> cards;

    public:
        int createFiggieDeck();
        void dealCards(std::vector<Player* >& players);
};

#endif // DECK_H
