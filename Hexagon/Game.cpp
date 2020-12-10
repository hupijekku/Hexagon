#include "Game.h"
#include <iostream>

Hex* Game::prevSelection = nullptr;
Hex* Game::selectedHex = nullptr;
Player* Game::currentPlayer = nullptr;

int Game::turnIndex = 0;
int Game::turnCounter = 0;

std::unordered_map<Vector2i, Hex> Game::hexes;
std::vector<Player> Game::players;

std::unordered_map<Vector2i, Hex>& Game::getHexes() {

	return Game::hexes;

};

void Game::addHex(Vector2i& pos, Hex& hex) {

	Game::hexes[pos] = hex;

};

void Game::selectHex(Hex* hexptr) {

	if (Game::selectedHex) {
		Hex& prev = *Game::selectedHex;
		prev.setColor(Color::White);
	}
	Hex& hex = *hexptr;
	hex.setColor(Color::Red);
	Game::prevSelection = Game::selectedHex;
	Game::selectedHex = &hex;

}

void Game::selectHex(Vector2i coordinates) {
	
	// No hex found at coordinates, a nullptr was returned
	if (!Game::getHexAt(coordinates)) {
		Game::selectHex(nullptr);
		return;
	}

	Hex& hex = *Game::getHexAt(coordinates);
	Game::selectHex(&hex);

}

Hex* Game::getHexAt(Vector2i coordinates) {

	if (Game::hexes.find(coordinates) != Game::hexes.end()) {
		return &Game::hexes.at(coordinates);
	}
	else {
		return nullptr;
	}

}

Hex* Game::getHexAt(int x, int z) {

	Vector2i vec(x, z);
	if (Game::hexes.find(vec) != Game::hexes.end()) {
		return &Game::hexes.at(vec);
	}
	else {
		return nullptr;
	}
}

Hex* Game::getSelectedHex() {
	return Game::selectedHex;
}

Player* Game::getCurrentPlayer() {
	return Game::currentPlayer;
}

std::vector<Player>& Game::getPlayers() {
	return Game::players;
}

void Game::addPlayer(Player& player) {
	if (Game::players.size() == 0) {
		Game::currentPlayer = &player;
	}
	Game::players.push_back(player);
}

void Game::nextTurn() {
	int i = Game::turnIndex;
	if (i >= Game::players.size()) {
		i = 0;
		Game::turnIndex = 1;
		Game::turnCounter += 1;
	}
	else {
		Game::turnIndex++;
	}
	Game::currentPlayer = &Game::players.at(i);
}