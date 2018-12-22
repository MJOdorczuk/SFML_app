#pragma once
#include "form.hpp"

class FComponent
{
private:
	Form * parent;

public:
	FComponent();
	virtual ~FComponent();

	virtual sf::Shape * draw() = 0;
};

