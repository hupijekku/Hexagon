#include "City.h"

City::City(Hex& hex) : hex(hex)
{
    this->owner = nullptr;
}

City::City(Hex& hex, Player* player) : hex(hex)
{
    this->owner = player;
}

Hex& City::getHex()
{
    return this->hex;
}

Player* City::getOwner()
{
    return this->getOwner();
}

void City::setOwner(Player* player)
{
    this->owner = player;
}
