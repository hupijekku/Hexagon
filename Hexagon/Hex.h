#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

namespace std
{
	template <class T>
	struct hash<sf::Vector2<T>>
	{
		std::size_t operator()(const sf::Vector2<T>& v) const
		{
			using std::hash;

			// Compute individual hash values for first
			// and second. Combine them using the Boost-func

			std::size_t tmp0 = hash<T>()(v.x);
			std::size_t tmp1 = hash<T>()(v.y);

			tmp0 ^= tmp1 + 0x9e3779b9 + (tmp0 << 6) + (tmp0 >> 2);
			return tmp0;
		}
	};
}

class Player;

class Hex {
private:
	int x;
	int z;
	Player* owner;
	Color c;
public:
	int getX();
	int getZ();
	int getY();
	Player* getOwner();
	void setOwner(Player& owner);
	Color getColor();
	void setColor(Color color);
	Hex(int x, int z, Color c);
	Hex(int x, int z);
	Hex();

	std::string display();

	bool operator==(const Hex& h) const;
};