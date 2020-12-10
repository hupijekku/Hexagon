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
	RenderTexture baseMap;
	Sprite sprite;
	View view;
	tgui::Gui& gui;
	Font font;
	bool changed;
	Color clear;
	Texture textHex;
	float radius;
public:
	Render(RenderWindow& window, tgui::Gui& gui, float radius);
	void drawShape(Shape& shape, Vector2i& position);
	void drawShape(Shape& shape, Vector2i& position, Color fillColor);
	void drawShape(Shape& shape, Vector2i& position, Color fillColor, Color outlineColor);
	void update(float delta);
	RenderTexture& getTexture();
	void pointCameraAtHex(Hex& hex);
	float getRadius();
	void setChanged(bool changed);
	void generateTexture();
	View& getView();
};

