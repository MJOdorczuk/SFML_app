#include "stdafx.h"
#include "EventHandler.h"


EventHandler::EventHandler(function<void(sf::Event*)> func)
{
	this->func = func;
}

EventHandler::EventHandler() {
	this->func = [](Event *e) {};
}


EventHandler::~EventHandler()
{
}
