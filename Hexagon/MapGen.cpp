#include "MapGen.h"
#include "Hex.h"
#include "Game.h"

float MapGen::mapHeight = 0;
float MapGen::mapWidth = 0;

void MapGen::generateMap(int c) {
	
	// Dimensions of the generated map as radii of hexes
	// E.g. if map is 2 hexes wide, 1 hex width is radius * sqrt(3) wide
	// mapWidth => sqrtf(3) * 2
	// Current map shape is hexagon (radius c), so it's (c * 2 + 1) hexes wide
	// These values are used in render.cpp to initialize the RenderTexture
	// If values are too large it's just wasted RAM
	// Too small means clipping at edges
	MapGen::mapWidth = sqrtf(3.0f) * (c * 2 + 1);
	MapGen::mapHeight = (2.0f * (3.0f / 4.0f))* (c * 2 + 1) + 0.5f;
	for (int i = -c; i < c + 1; i++) {
		for (int j = -c; j < c + 1; j++) {
			if (i + j > -c - 1 && i + j < c + 1) {
				Hex hex(i, j, Color::White);
				Vector2i vec(i, j);
				Game::addHex(vec, hex);
			}
		}
	}
}