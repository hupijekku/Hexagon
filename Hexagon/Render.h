#pragma once
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include "Hex.h"
#include "Game.h"
using namespace sf;
class Render
{
private:
	RenderWindow& window;
	tgui::Gui& gui;
	float dist;
	Vector2f offset;
	Font font;
	bool changed;
	Color clear;
	Texture textHex;
public:
	Render(RenderWindow& window, tgui::Gui& gui, float dist);
	void drawShape(Shape& shape, Vector2i& position);
	void drawShape(Shape& shape, Vector2i& position, Color fillColor);
	void drawShape(Shape& shape, Vector2i& position, Color fillColor, Color outlineColor);
	void update(float delta);
	void setOffset(Vector2f offset);
	Vector2f getOffset();
	void setDist(float dist);
	float getDist();
	void setChanged(bool changed);
};

