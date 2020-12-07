#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
using namespace sf;

class Util
{
public:
	static Vector2i pointToHex(Vector2i& pos, Vector2i offset, float dist);
private:
	static Vector2i roundHex(Vector2f& pos);
};

