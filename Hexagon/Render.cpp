#include "Render.h"
#include "Hex.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"
#include "Game.h"
#include "Util.h"

using namespace sf;

Render::Render(RenderWindow& window, tgui::Gui& gui, float dist) : window(window), gui(gui) {
	this->dist = dist;
	this->font.loadFromFile("Roboto-Light.ttf");
	this->changed = true;
	if (!this->textHex.loadFromFile("images/text_hexagon.png")) {
		std::cout << "Couldn't load hexagon texture" << std::endl;
	}
};

void Render::setChanged(bool changed) {
	this->changed = changed;
}

void Render::update(float delta) {
	//if (!this->changed) {
	//	this->gui.draw();
	//	return;
	//}
	this->window.clear(Color(120, 120, 120));
	// Get hexes around the visible screen and draw those
	float radius = 5000.0f / this->dist;
	Vector2f topLeft(0.0f, 0.0f);
	Vector2f bottomRight(Settings::screenWidth, Settings::screenHeight);
	Vector2i tlHex = Util::pointToHex(topLeft, this->getOffset(), this->dist);
	Vector2i brHex = Util::pointToHex(bottomRight, this->getOffset(), this->dist);
	// Using axial coordinates so we want to get some extra or we end up with a rhombus
	int hBuff = (int)((brHex.y - tlHex.y) / 2);
	tlHex.x -= hBuff + 1;
	tlHex.y -= 1;
	brHex.x += hBuff + 2;
	brHex.y += 2;
	for (int i = tlHex.x; i < brHex.x; i++) {
		for (int j = tlHex.y; j < brHex.y; j++) {
			Vector2i currPos(i, j);
			if (Game::getHexes().find(currPos) == Game::getHexes().end()) {
				continue;
			}
			Hex& hex = Game::getHexes().at(currPos);
			CircleShape shape(radius, 6);
			shape.setTexture(&this->textHex);
			this->drawShape(shape, currPos, hex.getColor());
		}
	}
	this->gui.draw();
	this->changed = false;
}

void Render::drawShape(Shape& shape, Vector2i& position, Color fillColor, Color outlineColor) {
	// Calculate shape position
	float radius = 5000.0f / this->dist;
	// Position = radius * hexmath - cameraPos
	float drawX = radius * (sqrtf(3.0f) * position.x + sqrtf(3.0f) / 2.0f * position.y) - (800.0f * this->offset.x / this->dist);
	float drawZ = radius * (3.0f / 2.0f * position.y) - (800.0f * this->offset.y / this->dist);

	shape.setOrigin(radius, radius);
	shape.setPosition(drawX, drawZ);
	shape.setFillColor(fillColor);
	shape.setOutlineColor(outlineColor);
	shape.setOutlineThickness(2.0f);
	this->window.draw(shape);
}

void Render::drawShape(Shape& shape, Vector2i& position, Color fillColor) {
	drawShape(shape, position, fillColor, Color::Black);
}

void Render::drawShape(Shape& shape, Vector2i& position) {
	drawShape(shape, position, Color::White);
}


void Render::setOffset(Vector2f offset) {
	this->offset = offset;
}

Vector2f Render::getOffset() {
	return this->offset;
}

float Render::getDist() {
	return this->dist;
}

void Render::setDist(float dist) {
	this->dist = dist;
}

void Render::pointCameraAtHex(Hex& hex) {
	//offset.x = (r*sqrt(3)*p.x+sqrt(3)/2*p.y+600)*dist/800
	//offset.y = (r * (3 / 2) * p.y + 300) * dist / 800
	float radius = 5000.0f / this->dist;
	std::cout << radius << std::endl;
	this->offset.x = (radius * sqrtf(3.0f) * hex.getX() + sqrtf(3.0f) / 2.0f * hex.getZ() - Settings::screenWidth / 2.0f) * this->dist / 800.0f;
	this->offset.y = (radius * (3.0f / 2.0f) * hex.getZ() - Settings::screenHeight / 2.0f) * this->dist / 800.0f;
}