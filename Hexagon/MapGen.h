#pragma once
class MapGen
{
private:
	static std::vector<float> biomeNoise;
	static std::vector<float> heightNoise;
	static std::vector<float> resourceNoise;
	static void generateBiomes();
public:
	// How big is the map in hex-radius units. For creating base rendertexture
	static float mapWidth;
	static float mapHeight;
	static void generateMap(int c);
};

