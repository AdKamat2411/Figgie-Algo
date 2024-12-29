#include <iostream>
#include <vector>
#include "probability.h"
#include <cmath>

using namespace std;

float Probability::factorial(int n) {
    float result = 1;
    for (int i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

float Probability::nCr(int n, int r) {
    if (r >= 0 && r <= n) {
        return factorial(n) / (factorial(n - r) * factorial(r));
    } else {
        return 0;
    }
}

std::vector<float> Probability::multinomial(std::vector<int> counts) {
    std::vector<int> combos;
    for (int i = 0; i < 11; i++) {
        int commonSuit = i / 3;
        int eightSuit = (i % 3 < i / 3) ? i % 3 : (i % 3) + 1;
        std::vector<int> suits = {0, 1, 2, 3};
        
        // Remove elements matching commonSuit or eightSuit
        suits.erase(
            std::remove_if(suits.begin(), suits.end(),
                           [commonSuit, eightSuit](int suit) {
                               return suit == commonSuit || suit == eightSuit;
                           }),
            suits.end());

        int p = nCr(12, counts[commonSuit]) * nCr(8, counts[eightSuit]) *
                nCr(10, counts[suits[0]]) * nCr(10, counts[suits[1]]);
        combos.push_back(p);
    }

    std::vector<float> likelihoods;

    float sum = 0;
    for (int i = 0; i < combos.size(); i++) {
        sum += combos[i];
    }
    for (int i = 0; i < combos.size(); i++) {
        likelihoods.push_back(static_cast<float>(combos[i]) / sum);
    }
    return likelihoods;
}




float cardVal(int deckNum, int suiteIdx, int numCards, float r) {
    if (deckNum == 3*suiteIdx || deckNum == ((3*suiteIdx) + 1) || deckNum == ((3*suiteIdx) + 2)) {
        int payout;
        int majority;
        if (deckNum % 3 == 0) {
            payout = 120;
            majority = 5;
        } else {
            payout = 100;
            majority = 6;
        }
        float payoutVal;
        if (numCards >= majority) {
            payoutVal = 0;
        } else {
            payoutVal = (payout * (1 - r) * std::pow(r, numCards)) / (1 - std::pow(r, majority));
        }
        return 10 + payoutVal;
    } else {
        return 0;
    }
}

float Probability::buyVal(int suiteIdx, int numCards, std::vector<float> likelihoods, float r) {
    float val = 0;
    for (int i = 0; i < 12; i++) {
        val += likelihoods[i] * cardVal(i, suiteIdx, numCards, r);
    }
    return val;
}

float Probability::sellVal(int suiteIdx, int numCards, std::vector<float> likelihoods, float r) {
    return buyVal(suiteIdx, numCards - 1, likelihoods, r);
}

