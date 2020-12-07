#include "Game.h"

std::unordered_map<Vector2i, Hex>& Game::getHexes() {

	return this->hexes;

};

void Game::addHex(Vector2i& pos, Hex& hex) {

	this->hexes[pos] = hex;

};