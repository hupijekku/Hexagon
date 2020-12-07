#include "Render.h"
#include "Hex.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"
#include "Game.h"
#include "Util.h"

using namespace sf;

Render::Render(Game& game, RenderWindow& window, float dist) : window(window), game(game) {
	this->dist = dist;
	this->font.loadFromFile("Roboto-Light.ttf");
};

void Render::update() {
	// Get hexes around the visible screen and draw those
	float radius = 1.0f / this->dist * 5000;
	Vector2i topLeft(0, 0);
	Vector2i bottomRight(Settings::screenWidth, Settings::screenHeight);
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
			if (game.getHexes().find(currPos) == game.getHexes().end()) {
				continue;
			}
			Hex& hex = game.getHexes().at(currPos);
			CircleShape shape(radius, 6);
			this->drawShape(shape, currPos, hex.c);
		}
	}
}

void Render::drawShape(Shape& shape, Vector2i& position, Color& fillColor, Color& outlineColor) {
	// Calculate shape position
	float radius = 1.0f / this->dist * 5000;
	float drawX = radius * (sqrt(3) * position.x + sqrt(3) / 2 * position.y) + 600 - (100 * Settings::cameraSpeed * this->offset.x * 1 / this->dist);
	float drawZ = radius * (3.0f / 2.0f * position.y) + 300 - (100 * Settings::cameraSpeed * this->offset.y * 1 / this->dist);

	// Check if shape is in screen
	if (drawX + radius * sqrt(3) < -radius/10 || drawZ + radius * 2 < 0) return;
	if (drawX > Settings::screenWidth || drawZ > Settings::screenHeight) return;

	shape.setPosition(drawX, drawZ);
	shape.setFillColor(fillColor);
	shape.setOutlineColor(Color::Black);
	shape.setOutlineThickness(2.0f);
	this->window.draw(shape);
}

void Render::drawShape(Shape& shape, Vector2i& position, Color& fillColor) {
	Color outlineColor = Color::Black;
	drawShape(shape, position, fillColor, outlineColor);
}

void Render::drawShape(Shape& shape, Vector2i& position) {
	Color color = Color::White;
	drawShape(shape, position, color);
}


void Render::setOffset(Vector2i offset) {
	this->offset = offset;
}

Vector2i Render::getOffset() {
	return this->offset;
}

float Render::getDist() {
	return this->dist;
}

void Render::setDist(float dist) {
	this->dist = dist;
}