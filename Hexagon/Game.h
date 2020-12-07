#pragma once
#include <unordered_map>
#include "Hex.h"
#include "Settings.h"

class Game
{
private:
	std::unordered_map<Vector2i, Hex> hexes;
public:
	std::unordered_map<Vector2i, Hex>& getHexes();
	void addHex(Vector2i& pos, Hex& hex);
};

