#include "bottomFeeder.h"

void bottomFeeder::strategy(std::vector<orderBook*> books, std::vector<Player* > players) {
    std::vector<int> counts;
    for (int numBook = 0; numBook < 4; numBook++) {
        std::map<Player*, int> knownCount;
        for (int i = 0; i < 4; i++) {
            knownCount[players[i]] = 0;
        }
        knownCount[this] = this->getIntialCount(numBook);
        
        for (auto trade: books[numBook]->getTrades()) {
            if (knownCount[trade.seller] > 0) {
                knownCount[trade.seller] -= 1;
                knownCount[trade.buyer] += 1;
            } else {
                knownCount[trade.seller] = 0;
                knownCount[trade.buyer] += 1;
            }
        }

        int sum = 0;
        for (int i = 0; i < 4; i++) {
            sum += knownCount[players[i]];
        }
        counts.push_back(sum);
        // cout << "Current suit is " << numBook << endl;
        // for (int i = 0; i < 4; i++) {
        //     cout << players[i]->getName() << "'s count is " << knownCount[players[i]] << endl;
        // }
    }
    Probability prob;
    std::vector<float> likelihoods = prob.multinomial(counts);
    
}
