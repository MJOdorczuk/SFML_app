#pragma once
#include "fcomponent.h"
class DummyComponent : public FComponent
{
public:
	DummyComponent();
	~DummyComponent();

	// Inherited via FComponent
	virtual sf::Shape *draw() override;
};

