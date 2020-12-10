#pragma once
#include <SFML/Graphics.hpp>
#include "Settings.h"
#include "Render.h"
using namespace sf;

class Util
{
public:
	static Vector2i screenPointToHex(Vector2f& pos, RenderWindow& window, Render& render);
private:
	static Vector2i roundHex(Vector2f& pos);
};

