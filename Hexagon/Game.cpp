#include "Game.h"
#include <iostream>

Hex* Game::prevSelection = nullptr;
Hex* Game::selectedHex = nullptr;
std::unordered_map<Vector2i, Hex> Game::hexes;

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

	Hex& hex = Game::getHexAt(coordinates);
	std::cout << hex.display() << std::endl;
	Game::selectHex(&hex);

}

Hex& Game::getHexAt(Vector2i coordinates) {

	if (Game::hexes.find(coordinates) != Game::hexes.end()) {
		return Game::hexes.at(coordinates);
	}
	else {
		std::cout << "HEX NOT FOUND" << std::endl;
	}

}

Hex& Game::getHexAt(int x, int z) {

	Vector2i vec(x, z);
	if (Game::hexes.find(vec) != Game::hexes.end()) {
		return Game::hexes.at(vec);
	}
	else {
		std::cout << "HEX NOT FOUND" << std::endl;
	}
}

Hex* Game::getSelectedHex() {
	return Game::selectedHex;
}