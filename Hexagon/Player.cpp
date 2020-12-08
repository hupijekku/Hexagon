#include "Player.h"

Player::Player(std::string name, int g, int c, int s) {
	this->name = name;
	this->gold = g;
	this->culture = c;
	this->science = s;
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