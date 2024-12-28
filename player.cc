#include "player.h"
#include <iostream>

using namespace std;

float Player::getStack() {
    return stack;
}

float Player::getSuiteCount(int index) {
    return suiteCount[index];
}

void Player::addToStack(float amount) {
    stack += amount;
}

void Player::addToSuite(int index) {
    suiteCount[index]++;
}

void Player::removeFromStack(float amount) {
    stack -= amount;
}

void Player::removeFromSuite(int index) {
    suiteCount[index]--;
}

string Player::getName() { return name; }

void Player::playerStatus() {
    cout << "Player Name: " << name << endl;
    cout << "Stack: $" << stack << endl;
    cout << "Suite Counts:" << endl;
    cout << "  Spades: " << suiteCount[0] << endl;
    cout << "  Clubs: " << suiteCount[1] << endl;
    cout << "  Hearts: " << suiteCount[2] << endl;
    cout << "  Diamonds: " << suiteCount[3] << endl;
}
