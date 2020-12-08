#include "Hex.h"

int Hex::getY()
{
	return -this->x-this->z;
}

Hex::Hex(int x, int z, Color c)
{
	this->x = x;
	this->z = z;
	this->c = c;
	this->owner = 0;
}

Hex::Hex(int x, int z)
{
	this->x = x;
	this->z = z;
	this->c = Color::White;
	this->owner = 0;
}

Hex::Hex() {
	this->x = 0;
	this->z = 0;
	this->c = Color::White;
	this->owner = 0;
}

std::string Hex::display()
{
	std::string x = std::to_string(this->x);
	std::string z = std::to_string(this->z);
	return x + ", " + z;
}

int Hex::getX() {
	return this->x;
}

int Hex::getZ() {
	return this->z;
}

Color Hex::getColor() {
	return this->c;
}

void Hex::setColor(Color color) {
	this->c = color;
}

void Hex::setOwner(int owner) {
	this->owner = owner;
}

int Hex::getOwner() {
	return this->owner;
}

bool Hex::operator==(const Hex& h) const
{
	// x + y + z = 0, no need to check for Y.
	return (this->x == h.x && this->z == h.z);
}
