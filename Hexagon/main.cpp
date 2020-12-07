#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "Hex.h"
#include "Render.h"
#include "Settings.h"
#include "Game.h"
#include "Util.h"

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
	Render render(game, window, 100);
	
	// Map size
	int c = 50;

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
			switch (event.type) {
			// TODO: Input class
			case Event::Closed:
			{
				window.close();
			}
			break;
			case Event::MouseWheelMoved:
			{
				// Zooming in and out. Large dist => Small hexes
				float dist = render.getDist();
				float delta = event.mouseWheel.delta * 3.0f;
				dist -= delta;
				dist = fmax(fmin(dist, 1.0f / Settings::screenHeight * 100000.0f), 1.0f / Settings::screenHeight * 30000.0f);
				render.setDist(dist);
				doRender = true;
			}
			break;
			case Event::MouseButtonPressed:
			{
				// Get hex under mouse position on click
				Vector2i pos(event.mouseButton.x, event.mouseButton.y);
				Vector2i hexCoord = Util::pointToHex(pos, render.getOffset(), render.getDist());
				std::cout << hexCoord.x << ", " << hexCoord.y << std::endl;
				if (game.getHexes().find(hexCoord) != game.getHexes().end()) {
					Hex& hex = game.getHexes().at(hexCoord);
					std::cout << hex.display() << std::endl;
					hex.c = (hex.c == Color::White) ? Color::Red : Color::White;
					doRender = true;
				}
			}
			break;
			case Event::Resized:
			{
				std::cout << "Resized" << std::endl;
				Settings::screenWidth = event.size.width;
				Settings::screenHeight = event.size.height;
				FloatRect area(0, 0, event.size.width, event.size.height);
				window.setView(View(area));
				doRender = true;
			}
			break;
			
			}
		}

		// Check camera movement
		Vector2i offset = render.getOffset();

		if (Keyboard::isKeyPressed(Keyboard::A)) {
			offset.x--;
		}
		if (Keyboard::isKeyPressed(Keyboard::D)) {
			offset.x++;
		}
		if (Keyboard::isKeyPressed(Keyboard::W)) {
			offset.y--;
		}
		if (Keyboard::isKeyPressed(Keyboard::S)) {
			offset.y++;
		}

		if (offset != render.getOffset()) {
			render.setOffset(offset);
			doRender = true;
		}

		// If something changed, render the screen
		if (doRender) {
			window.clear(Color(128, 128, 128));
			render.update();
			doRender = false;
		}

		window.display();

		// Calculate FPS
		currTime = clock.getElapsedTime();
		float fps = 1.0f / (currTime.asSeconds() - prevTime.asSeconds());
		window.setTitle("Hexagon - FPS: " + std::to_string((int)fps));
		prevTime = currTime;
	}

	return 0;
}