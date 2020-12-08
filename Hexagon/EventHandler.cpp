#include "EventHandler.h"

void EventHandler::handleEvent(Event& event, RenderWindow& window, Input& input)
{
	switch (event.type) {
		// TODO: Input class
	case Event::Closed:
	{
		window.close();
	}
	break;
	case Event::MouseWheelMoved:
	{
		input.onMouseScroll(event.mouseWheel.delta);
	}
	break;
	case Event::MouseButtonPressed:
	{
		// Get hex under mouse position on click
		Vector2f pos(event.mouseButton.x, event.mouseButton.y);
		input.onMouseDown(event.mouseButton.button, pos);
	}
	break;
	case Event::MouseButtonReleased:
	{
		Vector2f pos(event.mouseButton.button, event.mouseButton.y);
		input.onMouseUp(event.mouseButton.button, pos);
	}
	break;
	case Event::MouseMoved:
	{
		Vector2f pos(event.mouseMove.x, event.mouseMove.y);
		input.onMouseMove(pos);
	}
	break;
	case Event::Resized:
	{
		Settings::screenWidth = event.size.width;
		Settings::screenHeight = event.size.height;
		FloatRect area(0, 0, event.size.width, event.size.height);
		input.onMouseScroll(0);
		window.setView(View(area));
	}
	break;
	case Event::KeyPressed:
	{
		input.onKeyDown(event.key.code);
	}
	break;
	case Event::KeyReleased:
	{
		input.onKeyUp(event.key.code);
	}
	break;
	}
}
