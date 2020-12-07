#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "Hex.h"
#include "Render.h"
#include "Settings.h"
#include "Game.h"
#include "Util.h"
#include "Input.h"
#include "EventHandler.h"

using namespace sf;



int main() {
	ContextSettings cSettings;
	cSettings.antialiasingLevel = 4;

	RenderWindow window(VideoMode(Settings::screenWidth, Settings::screenHeight), "Hexagons", Style::Default, cSettings);
	window.setFramerateLimit(60);


	// For fps counter
	Clock clock; 
	Time prevTime = clock.getElapsedTime();
	Time currTime;

	// Main objects
	Game game;
	Render render(game, window, Color(120, 120, 120), 100);
	Input input(game, render);
	
	// Map size
	int c = 30;

	// Initialize map
	// Currently hexagon shaped with (0, 0) at the center.
	// Map generator? Terrain types, elevations etc.
	for (int i = -c; i < c + 1; i++) {
		for (int j = -c; j < c + 1; j++) {
			if (i + j > -c - 1 && i + j < c + 1) {
				Hex hex(i, j, Color::White);
				Vector2i vec(i, j);
				game.addHex(vec, hex);
			}
		}
	}

	// Has anything changed that needs re-rendering?
	bool doRender = true;
	while (window.isOpen()) {

		
		Event event;
		while (window.pollEvent(event)) {
			EventHandler::handleEvent(event, window, input);
		}
		
		input.update();
		render.update();

		window.display();

		// Calculate FPS
		currTime = clock.getElapsedTime();
		float fps = 1.0f / (currTime.asSeconds() - prevTime.asSeconds());
		window.setTitle("Hexagon - FPS: " + std::to_string((int)fps));
		prevTime = currTime;
	}

	return 0;
}