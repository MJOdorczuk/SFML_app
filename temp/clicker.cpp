#include "stdafx.h"
#include "clicker.h"


Clicker::Clicker()
{
	this->shape = new sf::RectangleShape();
	this->position.x = this->shape->getPosition().x;
	this->position.y = this->shape->getPosition().y;
	this->size.x = this->shape->getSize().x;
	this->size.y = this->shape->getSize().y;
	this->shape->setFillColor(sf::Color(10, 255, 10));
}


Clicker::~Clicker()
{
}

void Clicker::setPosition(int x, int y)
{
	this->shape->setPosition(x, y);
	this->position.x = x;
	this->position.y = y;
}

void Clicker::setSize(int width, int height)
{
	this->shape->setSize(sf::Vector2f(width, height));
	this->size.x = width;
	this->size.y = height;
}

void Clicker::setColor(uint8_t r, uint8_t g, uint8_t b)
{
	this->shape->setFillColor(sf::Color(r,g,b));
}

sf::Shape * Clicker::draw()
{
	return this->shape;
}

sf::IntRect Clicker::getHitBox()
{
	return sf::IntRect(position,size);
}


