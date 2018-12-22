#pragma once
#include <SFML/Graphics.hpp>

class Clicker
{
private:
	sf::RectangleShape * shape;
	sf::Vector2i position;
	sf::Vector2i size;
	
public:
	Clicker();
	~Clicker();
	void setPosition(int x, int y);
	void setSize(int width, int height);
	void setColor(uint8_t r, uint8_t g, uint8_t b);
	sf::Shape * draw();
	sf::IntRect getHitBox();
};

