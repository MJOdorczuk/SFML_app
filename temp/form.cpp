#include "stdafx.h"
#include "form.h"





Form::Form(int width, int height)
{
	this->width = width;
	this->height = height;
	int a = 0;
	this->formThread = new thread([&](Form * parent) {
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);
		sf::RenderWindow window(sf::VideoMode(parent->width, parent->height), "");
		while (window.isOpen())
		{
			window.setTitle(parent->getTitle());
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			window.clear();
			window.draw(shape);
			window.display();
			this_thread::sleep_for(chrono::milliseconds(100));
		}
	}, this);
}

Form::Form(int width, int height, string title) : Form(width,height)
{
	this->setTitle(title);
}

Form::~Form()
{
}

void Form::detachThread()
{
	this->formThread->detach();
}

void Form::joinThread()
{
	this->formThread->join();
}

void Form::setTitle(string title)
{
	mu.lock();
	this->title = title;
	mu.unlock();
}

string Form::getTitle()
{
	mu.lock();
	string ret = this->title;
	mu.unlock();
	return ret;
}
