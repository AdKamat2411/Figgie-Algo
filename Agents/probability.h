#ifndef PROBABILITY_H
#define PROBABILITY_H

#include <iostream>


class Probability {
    float factorial(int n);
    float nCr(int n, int r);
    public:
        std::vector<float> multinomial(std::vector<int> counts);
        float buyVal(int suiteIdx, int numCards, std::vector<float> likelihoods, float r);
        float sellVal(int suiteIdx, int numCards, std::vector<float> likelihoods, float r);
};

#endif //  PROBABILITY_H
