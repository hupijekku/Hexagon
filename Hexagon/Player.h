#pragma once
#include <string>
class Player
{
private:
	std::string name;
	int gold;
	int culture;
	int science;
public:
	Player(std::string name, int g, int c, int s);
	int getGold();
	void setGold(int gold);
	void changeGold(int change);
	int getCulture();
	void setCulture(int culture);
	void changeCulture(int change);
	int getScience();
	void setScience(int science);
	void changeScience(int change);
	std::string getName();
	void setName(std::string name);
};

