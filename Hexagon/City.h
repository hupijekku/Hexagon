#pragma once
#include "Hex.h"
class City
{
private:
	Hex& hex; // Ref since city is always on a hex
	Player* owner; // Pointer since city might be abandoned/neutral/barbarian?
	//std::vector<Building> ?
public:
	City(Hex& hex);
	City(Hex& hex, Player* player);
	Hex& getHex(); // No setter for hex, cities don't move
	Player* getOwner();
	void setOwner(Player* player);
};

