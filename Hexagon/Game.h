#pragma once
#include <unordered_map>
#include "Hex.h"
#include "Settings.h"

class Game
{
private:
	static std::unordered_map<Vector2i, Hex> hexes;
	static Hex* selectedHex;
	static Hex* prevSelection;
public:
	static std::unordered_map<Vector2i, Hex>& getHexes();
	static void addHex(Vector2i& pos, Hex& hex);
	static void selectHex(Hex* hex);
	static void selectHex(Vector2i coordinates);
	static Hex& getHexAt(Vector2i coordinates);
	static Hex& getHexAt(int x, int z);
	static Hex* getSelectedHex();
};

