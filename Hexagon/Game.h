#pragma once
#include <unordered_map>
#include "Hex.h"
#include "Settings.h"
#include "Player.h"

class Game
{
private:
	static std::unordered_map<Vector2i, Hex> hexes;
	static std::vector<Player> players;
	static int turnIndex;
	static int turnCounter;
	static Hex* selectedHex;
	static Hex* prevSelection;
	static Player* currentPlayer;
public:
	static std::unordered_map<Vector2i, Hex>& getHexes();
	static void addHex(Vector2i& pos, Hex& hex);
	static void selectHex(Hex* hex);
	static void selectHex(Vector2i coordinates);
	static Hex* getHexAt(Vector2i coordinates);
	static Hex* getHexAt(int x, int z);
	static Hex* getSelectedHex();
	static Player* getCurrentPlayer();
	static std::vector<Player>& getPlayers();
	static void addPlayer(Player& player);
	static void nextTurn();
};

