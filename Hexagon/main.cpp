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
#include "MapGen.h"

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

	Game();
	int c = 20;
	MapGen::generateMap(c);
	Render render(window, tgui, 100.0f);
	Input input(render, window);
	GUI mGui(tgui);
	mGui.createGUI();


	// Temp for testing
	Player player1("Player 1", Color(0, 255, 0), 100, 0, 0);
	Game::addPlayer(player1);
	Player player2("Player 2", Color(0, 0, 255), 100, 0, 0);
	Game::addPlayer(player2);
	Hex& hex1 = *Game::getHexAt(0, 0);
	Hex& hex2 = *Game::getHexAt(5, 0);
	// See Trello->Bugs
	hex1.setOwner(Game::getPlayers().at(0));
	hex2.setOwner(Game::getPlayers().at(1));
	City city1(hex1);
	City city2(hex2);
	// See Trello->Bugs
	Game::getPlayers().at(0).addCity(city1);
	Game::getPlayers().at(1).addCity(city2);
	render.generateTexture();
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
		window.clear(Color(120, 120, 120));
		input.update(delta);
		render.update(delta);
		
		mGui.update();
		window.display();
	}

	return 0;
}