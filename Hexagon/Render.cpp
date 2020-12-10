#include "Render.h"
#include "Hex.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Settings.h"
#include "Game.h"
#include "Util.h"
#include "MapGen.h"

using namespace sf;

Render::Render(RenderWindow& window, tgui::Gui& gui, float radius) : window(window), gui(gui) {
	this->font.loadFromFile("Roboto-Light.ttf");
	this->changed = true;
	this->radius = radius;
	ContextSettings cSettings;
	cSettings.antialiasingLevel = 4;
	this->baseMap.create(MapGen::mapWidth * this->radius + 1, MapGen::mapHeight * this->radius, cSettings);
	View view(Vector2f(MapGen::mapWidth * this->radius / 2, MapGen::mapHeight * this->radius / 2.0f), Vector2f(Settings::screenWidth, Settings::screenHeight));
	this->view = view;
	if (!this->textHex.loadFromFile("images/text_hexagon.png")) {
		std::cout << "Couldn't load hexagon texture" << std::endl;
	}
};

void Render::setChanged(bool changed) {
	this->changed = changed;
}

void Render::generateTexture()
{
	Vector2u vec = this->baseMap.getSize();
	// Render the basic map shape to the RenderTexture baseMap
	for (auto& h : Game::getHexes()) {
		Vector2i pos = h.first;
		Hex& hex = h.second;

		float drawX = this->radius * (sqrtf(3.0f) * hex.getX() + sqrtf(3.0f) / 2.0f * hex.getZ()) + vec.x / 2;
		float drawZ = this->radius * (3.0f / 2.0f * hex.getZ()) + vec.y / 2;

		CircleShape shape(this->radius, 6);
		shape.setTexture(&this->textHex);
		shape.setOrigin(this->radius, this->radius);
		shape.setPosition(drawX, drawZ);
		shape.setOutlineThickness(2.0f);
		shape.setOutlineColor(Color::Black);
		shape.setFillColor(Color::White);
		this->baseMap.draw(shape);
	}
	Sprite sprite(this->baseMap.getTexture());
	this->sprite = sprite;
	this->baseMap.display();

}

void Render::update(float delta) {
	this->window.setView(this->view);
	// Draw base
	this->window.draw(this->sprite);

	// Draw details (e.g. player colors)
	for (auto& pair : Game::getHexes()) {
		Vector2i pos = pair.first;
		Hex& h = pair.second;
		if (h.getOwner()) {
			CircleShape shape(this->radius, 6);
			Color c = h.getOwner()->getColor();
			this->drawHexOutlines(shape, pos, *h.getOwner());
			c.a = 50;
			this->drawShape(shape, pos, c);
			
		}
	}

	this->gui.draw();
	this->changed = false;
}

void Render::drawHexOutlines(Shape& shape, Vector2i& position, Player& player) {
	Vector2u vec = this->baseMap.getTexture().getSize();
	float drawX = this->radius * (sqrtf(3.0f) * position.x + sqrtf(3.0f) / 2.0f * position.y) + vec.x / 2;
	float drawZ = this->radius * (3.0f / 2.0f * position.y) + vec.y / 2;

	// Side 1
	if (Game::getHexAt(position.x, position.y - 1)) {
		Hex& h = *Game::getHexAt(position.x, position.y - 1);
		if (!h.getOwner() || (h.getOwner() && *h.getOwner() != player )) {
			float lX = drawX - radius * sqrtf(3.0f)/2.0f;
			float lY = drawZ - radius / 2.0f;
			RectangleShape outLine(Vector2f(radius, 10.0f));
			outLine.setOrigin(0, 5.0f);
			outLine.setPosition(lX, lY);
			outLine.rotate(-30.0f);
			outLine.setFillColor(player.getColor());
			this->window.draw(outLine);
		}
	}

	// Side 2
	if (Game::getHexAt(position.x + 1, position.y - 1)) {
		Hex& h = *Game::getHexAt(position.x + 1, position.y - 1);
		if (!h.getOwner() || (h.getOwner() && *h.getOwner() != player)) {
			float lX = drawX;
			float lY = drawZ - radius;
			RectangleShape outLine(Vector2f(radius, 10.0f));
			outLine.setOrigin(0, 5.0f);
			outLine.setPosition(lX, lY);
			outLine.rotate(30.0f);
			outLine.setFillColor(player.getColor());
			this->window.draw(outLine);
		}
	}

	// Side 3
	if (Game::getHexAt(position.x + 1, position.y)) {
		Hex& h = *Game::getHexAt(position.x + 1, position.y);
		if (!h.getOwner() || (h.getOwner() && *h.getOwner() != player)) {
			float lX = drawX + radius * sqrtf(3.0f) / 2.0f;
			float lY = drawZ - radius / 2.0f;
			RectangleShape outLine(Vector2f(radius, 10.0f));
			outLine.setOrigin(0, 5.0f);
			outLine.setPosition(lX, lY);
			outLine.rotate(90.0f);
			outLine.setFillColor(player.getColor());
			this->window.draw(outLine);
		}
	}

	// Side 4
	if (Game::getHexAt(position.x, position.y + 1)) {
		Hex& h = *Game::getHexAt(position.x, position.y + 1);
		if (!h.getOwner() || (h.getOwner() && *h.getOwner() != player)) {
			float lX = drawX + radius * sqrtf(3.0f) / 2.0f;
			float lY = drawZ + radius / 2.0f;
			RectangleShape outLine(Vector2f(radius, 10.0f));
			outLine.setOrigin(0, 5.0f);
			outLine.setPosition(lX, lY);
			outLine.rotate(150.0f);
			outLine.setFillColor(player.getColor());
			this->window.draw(outLine);
		}
	}

	// Side 5
	if (Game::getHexAt(position.x - 1, position.y - 1)) {
		Hex& h = *Game::getHexAt(position.x - 1, position.y - 1);
		if (!h.getOwner() || (h.getOwner() && *h.getOwner() != player)) {
			float lX = drawX;
			float lY = drawZ + radius;
			RectangleShape outLine(Vector2f(radius, 10.0f));
			outLine.setOrigin(0, 5.0f);
			outLine.setPosition(lX, lY);
			outLine.rotate(210.0f);
			outLine.setFillColor(player.getColor());
			this->window.draw(outLine);
		}
	}

	// Side 6
	if (Game::getHexAt(position.x - 1, position.y)) {
		Hex& h = *Game::getHexAt(position.x - 1, position.y);
		if (!h.getOwner() || (h.getOwner() && *h.getOwner() != player)) {
			float lX = drawX - radius * sqrtf(3.0f) / 2.0f;
			float lY = drawZ + radius / 2.0f;
			RectangleShape outLine(Vector2f(radius, 10.0f));
			outLine.setOrigin(0, 5.0f);
			outLine.setPosition(lX, lY);
			outLine.rotate(-90.0f);
			outLine.setFillColor(player.getColor());
			this->window.draw(outLine);
		}
	}
}

void Render::drawShape(Shape& shape, Vector2i& position, Color fillColor, Color outlineColor) {
	// Calculate shape position
	// Position = radius * hexmath - cameraPos
	Vector2u vec = this->baseMap.getTexture().getSize();
	float drawX = this->radius * (sqrtf(3.0f) * position.x + sqrtf(3.0f) / 2.0f * position.y) + vec.x / 2;
	float drawZ = this->radius * (3.0f / 2.0f * position.y) + vec.y / 2;

	shape.setOrigin(this->radius, this->radius);
	shape.setPosition(drawX, drawZ);
	shape.setFillColor(fillColor);
	//shape.setOutlineColor(outlineColor);
	//shape.setOutlineThickness(2.0f);
	this->window.draw(shape);
}

void Render::drawShape(Shape& shape, Vector2i& position, Color fillColor) {
	drawShape(shape, position, fillColor, Color::Black);
}

void Render::drawShape(Shape& shape, Vector2i& position) {
	drawShape(shape, position, Color::White);
}

RenderTexture& Render::getTexture() {
	return this->baseMap;
}

void Render::pointCameraAtHex(Hex& hex) {
	Vector2f centerF = this->view.getCenter();
	Vector2f pointF(Util::hexToWorldPoint(hex, *this));
	float x = pointF.x - centerF.x;
	float y = pointF.y - centerF.y;
	this->view.move(x, y);	
}

float Render::getRadius() {
	return this->radius;
}

View& Render::getView() {
	return this->view;
}