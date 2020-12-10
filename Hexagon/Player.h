#pragma once
#include <string>
#include <vector>
#include "City.h"


class Player
{
private:
	std::string name;
	std::vector<City> cities;
	Color color;
	int gold;
	int culture;
	int science;
public:
	Player(std::string name, Color color, int g, int c, int s);
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
	std::vector<City>& getCities();
	City* getCity(int index);
	void addCity(City& city);
	Color getColor();
};

