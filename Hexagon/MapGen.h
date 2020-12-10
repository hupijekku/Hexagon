#pragma once
class MapGen
{
private:
public:
	// How big is the map in hex-radius units. For creating base rendertexture
	static float mapWidth;
	static float mapHeight;
	static void generateMap(int c);
};

