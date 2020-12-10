#include "Util.h"

#include <iostream>
Vector2i Util::screenPointToHex(Vector2f& pos, RenderWindow& window, Render& render)
{
	Vector2i screenPos(pos.x, pos.y);
	Vector2f mapPos = window.mapPixelToCoords(screenPos);
	Vector2u mapDimensions = render.getTexture().getSize();
	float radius = render.getRadius();
	float x = (mapPos.x - mapDimensions.x / 2)/(radius * sqrtf(3.0f)) - (mapPos.y - mapDimensions.y/2)/(radius*3.0f);
	float z = (mapPos.y - mapDimensions.y / 2)/(radius * (3.0f / 2.0f));
	std::cout << x << ", " << z << std::endl;
	Vector2f ret(x, z);
	return roundHex(ret);
}

// Get closest hex to the position
Vector2i Util::roundHex(Vector2f& pos)
{
	float z = -pos.x - pos.y;
	int rx = (int)round(pos.x);
	int ry = (int)round(pos.y);
	int rz = (int)round(z);

	float xDiff = abs(rx - pos.x);
	float yDiff = abs(ry - pos.y);
	float zDiff = abs(rz - z);

	if (xDiff > yDiff && xDiff > zDiff) {
		rx = -ry - rz;
	}
	else if (yDiff > zDiff) {
		ry = -rx - rz;
	}
	else {
		rz = -rx - ry;
	}

	Vector2i ret(rx, ry);
	return ret;
}
