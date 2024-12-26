#include "player.h";

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