#include "Player.h"

int Player::gold = 100000;
int Player::culture = 0;
int Player::science = 0;

int Player::getGold() {
	return Player::gold;
}

void Player::setGold(int gold) {
	Player::gold = gold;
}

void Player::changeGold(int change) {
	Player::gold += change;
}

int Player::getCulture() {
	return Player::culture;
}

void Player::setCulture(int culture) {
	Player::culture = culture;
}

void Player::changeCulture(int change) {
	Player::culture += change;
}

int Player::getScience() {
	return Player::science;
}

void Player::setScience(int science) {
	Player::science = science;
}

void Player::changeScience(int change) {
	Player::science += change;
}