#include "player.h"

export struct Card {
    int suit;
    int rank;
};

class Deck {
    private:
        std::vector<Card> cards;

    public:
        void createFiggieDeck();
        void dealCards(std::vector<Player>& players);
};


