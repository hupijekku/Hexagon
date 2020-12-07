#pragma once

#include<SFML/Graphics.hpp>
#include <unordered_set>
#include "Game.h"
#include "Render.h"

using namespace sf;
class Input
{
private:
	std::unordered_set<Keyboard::Key> pressed;
	bool mouse[3];
	Game& game;
	Render& render;
public:
	Input(Game& game, Render& render) : game(game), render(render) {};
	void onKeyDown(Keyboard::Key& key);
	void onKeyUp(Keyboard::Key& key);
	void onMouseDown(Mouse::Button& button, Vector2f& position);
	void onMouseUp(Mouse::Button& button, Vector2f& position);
	void onMouseMove(Vector2f& position);
	void onMouseScroll(int delta);
	void update();
};

