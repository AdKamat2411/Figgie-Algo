#include "order.h"

int Order::getSuite() { return suite; }

int Order::getDirection() { return direction; }

Player& Order::getPlayer() { return player; }

float Order::getPrice() { return price; }
