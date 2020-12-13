#include "Hex.h"
#include "Game.h"
#include "FastNoiseLite.h"
#include <vector>
#include "MapGen.h"
#include <iostream>

float MapGen::mapHeight = 0;
float MapGen::mapWidth = 0;
std::vector<float> MapGen::biomeNoise;
std::vector<float> MapGen::heightNoise;
std::vector<float> MapGen::resourceNoise;

void MapGen::generateMap(int c) {

	MapGen::generateBiomes();
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
				Color col;
				// From cubic coordinates to col/row
				// Because with cubic, you'll get thin stretched \-shapes
				int ofX = i + (j + (j & 1)) / 2;
				int ofZ = j;
				float f = MapGen::biomeNoise.at((ofX + c) * 256 + (ofZ + c));
				if (f < 0.0f) {
					col = Color::Blue;
				}
				else if (f < 0.15f) {
					col = Color::Yellow;
				}
				else if (f < 0.3f) {
					col = Color::Cyan;
				}
				else if (f < 0.85f) {
					col = Color::Green;
				}
				else {
					col = Color(120.0f, 120.0f, 120.0f);
				}
				Hex hex(i, j, col);
				Vector2i vec(i, j);
				Game::addHex(vec, hex);
			}
		}
	}
}

void MapGen::generateBiomes() {
	srand(time(NULL));
	FastNoiseLite noise;
	noise.SetNoiseType(FastNoiseLite::NoiseType::NoiseType_OpenSimplex2);
	noise.SetSeed(rand() % 10000);
	noise.SetFrequency(0.05f);
	noise.SetFractalType(FastNoiseLite::FractalType::FractalType_FBm);
	noise.SetFractalOctaves(2);
	noise.SetFractalGain(1.5f);
	
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			float n = noise.GetNoise(float(i), float(j));
			// Force a landmass at the middle for now
			if (i >= 10 && i < 30 && j >= 10 && j < 30 && i + j > 25 && i + j < 55 && i - j > -15 && j - i > -15) {
				n = abs(n) * 1.2f;
			}
			MapGen::biomeNoise.push_back(n);
		}
	}
}