#include "Util.h"

// TODO: Some bug here causing clicking near right edge of hex to select the one next to it.

Vector2i Util::pointToHex(Vector2i& pos, Vector2i offset, float dist)
{
	float radius = 1.0f / dist * 5000;
	int pX = (int)(pos.x - 600 + (100 * Settings::cameraSpeed * offset.x * 1 / dist) - sqrt(3) * radius / 2);
	int pY = (int)(pos.y - 300 + (100 * Settings::cameraSpeed * offset.y * 1 / dist) - radius);
	float x = (float)((sqrt(3) / 3.0f * pX - pY / 3.0f) / radius);
	float z = (2.0f / 3.0f * pY) / radius;
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
