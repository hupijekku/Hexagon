#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Render.h"
#include "Input.h"

using namespace sf;

class EventHandler
{
private:
public:
	static void handleEvent(Event& event, RenderWindow& window, Input& input);
};

