#include "stdafx.h"
#include "form.h"

Form::Form(int width, int height)
{
	this->params.width = width;
	this->params.height = height;
	this->formThread = new thread([&](Form * parent) {
		sf::CircleShape shape(100.f);
		shape.setFillColor(sf::Color::Green);
		sf::RenderWindow window(sf::VideoMode(parent->params.width, parent->params.height), "");
		int code = NONE;
		while (window.isOpen() && code == NONE)
		{
			parent->update(&window);
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
	this->closeForm();
	this->formThread->join();
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
	this->params.title = title;
	mu.unlock();
}

int Form::update(sf::RenderWindow * window)
{
	if (this->hasToClose())
	{
		window->close();
		return CLOSE;
	}
	window->setTitle(this->getTitle());
	return NONE;
}

string Form::getTitle()
{
	mu.lock();
	string ret = this->params.title;
	mu.unlock();
	return ret;
}

void Form::closeForm()
{
	mu.lock();
	this->params.closing = true;
	mu.unlock();
}

bool Form::getThreadRunning()
{
	mu.lock();
	bool ret = this->threadRunning;
	mu.unlock();
	return ret;
}

bool Form::hasToClose()
{
	mu.lock();
	bool ret = this->params.closing;
	mu.unlock();
	return ret;
}
