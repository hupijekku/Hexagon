#pragma once
#include <SFML/Graphics.hpp>
#include "Hex.h"
#include "Game.h"
using namespace sf;
class Render
{
private:
	Game& game;
	RenderWindow& window;
	float dist;
	Vector2i offset;
	Font font;
	bool changed;
	Color clear;
public:
	Render(Game& game, RenderWindow& window, Color clear, float dist);
	void drawShape(Shape& shape, Vector2i& position);
	void drawShape(Shape& shape, Vector2i& position, Color fillColor);
	void drawShape(Shape& shape, Vector2i& position, Color fillColor, Color outlineColor);
	void update();
	void setOffset(Vector2i offset);
	Vector2i getOffset();
	void setDist(float dist);
	float getDist();
	void setChanged(bool changed);
};

