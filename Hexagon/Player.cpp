#include "Player.h"
#include <iostream>

Player::Player(std::string name, Color color, int g, int c, int s) {
	this->name = name;
	this->color = color;
	this->gold = g;
	this->culture = c;
	this->science = s;
	this->cities;
}

int Player::getGold() {
	return this->gold;
}

void Player::setGold(int gold) {
	this->gold = gold;
}

void Player::changeGold(int change) {
	this->gold += change;
}

int Player::getCulture() {
	return this->culture;
}

void Player::setCulture(int culture) {
	this->culture = culture;
}

void Player::changeCulture(int change) {
	this->culture += change;
}

int Player::getScience() {
	return this->science;
}

void Player::setScience(int science) {
	this->science = science;
}

void Player::changeScience(int change) {
	this->science += change;
}

std::string Player::getName() {
	return this->name;
}

void Player::setName(std::string name) {
	this->name = name;
}

std::vector<City>& Player::getCities() {
	return this->cities;
}

City* Player::getCity(int index) {
	if (this->cities.size() > index) {
		return &this->cities.at(index);
	}
	return nullptr;
}

void Player::addCity(City& city) {
	this->cities.push_back(city);
}

Color Player::getColor() {
	return this->color;
}

bool Player::operator==(const Player& p) const
{
	return this->name == p.name;
}

bool Player::operator!=(const Player& p) const
{
	return this->name != p.name;
}
