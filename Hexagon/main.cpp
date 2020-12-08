#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <iostream>
#include <unordered_map>
#include "Hex.h"
#include "Render.h"
#include "Settings.h"
#include "Game.h"
#include "Util.h"
#include "Input.h"
#include "EventHandler.h"
#include "GUI.h"
#include "Player.h"

using namespace sf;



int main() {
	ContextSettings cSettings;
	cSettings.antialiasingLevel = 4;

	RenderWindow window(VideoMode(Settings::screenWidth, Settings::screenHeight), "Hexagons", Style::Default, cSettings);
	window.setFramerateLimit(60);

	tgui::GuiSFML tgui(window);

	// For fps counter
	Clock clock;

	// Main objects
	Player player("Player 1", 100, 0, 0);
	Game();
	Game::addPlayer(player);
	Render render(window, tgui, 100);
	Input input(render);
	GUI mGui(tgui);
	mGui.createGUI();

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
				Game::addHex(vec, hex);
			}
		}
	}

	while (window.isOpen()) {

		// Calculate FPS
		Time time = clock.restart();
		float delta = time.asSeconds();
		float fps = 1.0f / delta;
		window.setTitle("Hexagon - FPS: " + std::to_string((int)fps));
		
		Event event;
		while (window.pollEvent(event)) {
			// returns true if event was handled, false if no gui-object handled the event
			bool guiHandled = tgui.handleEvent(event);
			if (event.type == Event::MouseButtonPressed && guiHandled) break;
			EventHandler::handleEvent(event, window, input);
		}

		input.update(delta);
		render.update(delta);
		mGui.update();
		window.display();
	}

	return 0;
}