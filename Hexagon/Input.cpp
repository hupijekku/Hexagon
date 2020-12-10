#include "Input.h"
#include "Render.h"
#include "Game.h"
#include "Util.h"
#include <iostream>

using namespace sf;

void Input::onKeyDown(Keyboard::Key& key) {
	this->pressed.insert(key);
	if (key == Keyboard::Enter) {
		Game::nextTurn();
		if (Game::getCurrentPlayer()) {
			Player& p = *Game::getCurrentPlayer();
			if (p.getCity(0)) {
				City& c = *p.getCity(0);
				Hex& h = c.getHex();
				this->render.pointCameraAtHex(h);
			}
		}
		
	}
}

void Input::onKeyUp(Keyboard::Key& key) {
	this->pressed.erase(key);
}

void Input::onMouseDown(Mouse::Button& button, Vector2f& position) {
	this->mouse[button] = true;
	// Get hex under mouse position on click
	Vector2i hexCoord = Util::screenPointToHex(position, this->window, this->render);
	std::cout << hexCoord.x << ", " << hexCoord.y << std::endl;
	if (Game::getHexes().find(hexCoord) != Game::getHexes().end() && button == Mouse::Left) {
		Game::selectHex(hexCoord);
		this->render.setChanged(true);
	}
}

void Input::onMouseUp(Mouse::Button& button, Vector2f& position) {
	this->mouse[button] = false;
}

void Input::onMouseMove(Vector2f& position) {
	if (mouse[Mouse::Left]) {
		std::cout << "Dragging mouse to x:" << position.x << " y:" << position.y << std::endl;
	}
}

void Input::onMouseScroll(int delta) {
	this->render.setChanged(true);
	this->render.getView().zoom(1.0f-delta*0.1f);
}

void Input::update(float delta) {

	const auto& it = this->pressed.end();
	float h = this->render.getView().getSize().y/200.0f * delta * Settings::cameraSpeed;
	// Camera controls
	if (this->pressed.find(Keyboard::A) != it) {
		this->render.getView().move(-10.0f * h, 0.0f);
	}
	if (this->pressed.find(Keyboard::D) != it) {
		this->render.getView().move(10.0f * h, 0.0f);
	}
	if (this->pressed.find(Keyboard::W) != it) {
		this->render.getView().move(0.0f, -10.0f * h);
	}
	if (this->pressed.find(Keyboard::S) != it) {
		this->render.getView().move(0.0f, 10.0f * h);
	}
}