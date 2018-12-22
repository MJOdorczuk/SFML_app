#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <stdio.h>
#include <functional>

using namespace std;
using namespace sf;

static class EventHandler
{
private:
	function<void(Event*)> func;
public:
	EventHandler(function<void(Event*)> func);
	EventHandler();
	~EventHandler();

	void operator+=(const EventHandler * other) {
		auto temp = this->func;
		this->func = [&](Event *e) {
			temp(e);
			other->func(e);
		};
	}

	void operator+=(const EventHandler other) {
		auto temp = this->func;
		this->func = [&](Event *e) {
			temp(e);
			other.func(e);
		};
	}

	EventHandler operator+(const EventHandler * other) {
		return EventHandler([&](Event *e) {
			this->func(e);
			other->func(e);
		});
	}

	EventHandler operator+(const EventHandler other) {
		return EventHandler([&](Event *e) {
			this->func(e);
			other.func(e);
		});
	}

	void operator=(const EventHandler * other) {
		this->func = other->func;
	}

	void operator=(const EventHandler other) {
		this->func = other.func;
	}
};

