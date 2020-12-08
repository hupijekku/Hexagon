#include "Input.h"
#include "Render.h"
#include "Game.h"
#include "Util.h"
#include <iostream>

using namespace sf;

void Input::onKeyDown(Keyboard::Key& key) {
	this->pressed.insert(key);
}

void Input::onKeyUp(Keyboard::Key& key) {
	this->pressed.erase(key);
}

void Input::onMouseDown(Mouse::Button& button, Vector2f& position) {
	this->mouse[button] = true;
	// Get hex under mouse position on click
	Vector2i hexCoord = Util::pointToHex(position, this->render.getOffset(), this->render.getDist());
	if (Game::getHexes().find(hexCoord) != Game::getHexes().end() && button == Mouse::Left) {
		Game::selectHex(hexCoord);
		this->render.setChanged(true);
	}
}

void Input::onMouseUp(Mouse::Button& button, Vector2f& position) {
	this->mouse[button] = false;
}

void Input::onMouseMove(Vector2f& position) {
	if (mouse[0]) {
		std::cout << "Dragging mouse to x:" << position.x << " y:" << position.y << std::endl;
	}
}

void Input::onMouseScroll(int delta) {
	float dist = this->render.getDist();
	dist = fmax(fmin(dist - (delta * 3.0f), 1.0f / Settings::screenHeight * 100000.0f), 1.0f / Settings::screenHeight * 30000.0f);
	this->render.setChanged(true);
	this->render.setDist(dist);
}

void Input::update(float delta) {

	Vector2f offset = this->render.getOffset();
	const auto& it = this->pressed.end();

	// Camera controls
	if (this->pressed.find(Keyboard::A) != it) {
		offset.x -= 50 * delta;
	}
	if (this->pressed.find(Keyboard::D) != it) {
		offset.x += 50 * delta;
	}
	if (this->pressed.find(Keyboard::W) != it) {
		offset.y -= 50 * delta;
	}
	if (this->pressed.find(Keyboard::S) != it) {
		offset.y += 50 * delta;
	}

	if (offset != this->render.getOffset()) this->render.setChanged(true);

	this->render.setOffset(offset);

}