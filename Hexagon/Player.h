#pragma once
class Player
{
private:
	static int gold;
	static int culture;
	static int science;
public:
	static int getGold();
	static void setGold(int gold);
	static void changeGold(int change);
	static int getCulture();
	static void setCulture(int culture);
	static void changeCulture(int change);
	static int getScience();
	static void setScience(int science);
	static void changeScience(int change);
};

