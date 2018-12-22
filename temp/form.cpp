#include "stdafx.h"
#include "form.hpp"

Form::Form(int width, int height)
{
	this->params.width = width;
	this->params.height = height;
	Clicker c1, c2, c3;
	c1.setPosition(500, 500);
	c1.setColor(0, 0, 255);
	c2.setPosition(650, 500);
	c2.setColor(0, 255, 0);
	c3.setPosition(800, 500);
	c3.setColor(255, 0, 0);
	clickers.push_back(c1);
	clickers.push_back(c2);
	clickers.push_back(c3);

	this->formThread = new thread([&](Form * parent) {
		sf::CircleShape shape(20.f);
		shape.setFillColor(sf::Color::Green);
		sf::RenderWindow window(sf::VideoMode(parent->params.width, parent->params.height), "");
		int code = NONE;
		while (window.isOpen() && code == NONE)
		{
			parent->update(&window);
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
				if (event.type == sf::Event::MouseButtonPressed)
				{
					parent->mouseButtonPressed(event.mouseButton.x, event.mouseButton.y);
				}
			}
			ballParams ball = parent->getBall();
			shape.setPosition(ball.x, ball.y);
			if (ball.x < 20) ball.vx = abs(ball.vx);
			if (ball.x > 380) ball.vx = 0 - abs(ball.vx);
			if (ball.y < 20) ball.vy = abs(ball.vy);
			if (ball.y > 380) ball.vy = 0 - abs(ball.vy);
			ball.vy += 0.1f;
			ball.x += ball.vx;
			ball.y += ball.vy;
			parent->setBall(ball);
			
			parent->render(&window);

			this_thread::sleep_for(chrono::milliseconds(20));
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

void Form::render(sf::RenderWindow * window)
{
	window->clear();
	for (unsigned int i = 0; i < clickers.size(); i++)
	{
		window->draw(*(clickers.at(i).draw()));
	}
	window->display();
}

string Form::getTitle()
{
	mu.lock();
	string ret = this->params.title;
	mu.unlock();
	return ret;
}

void Form::setBall(ballParams ball)
{
	mu.lock();
	this->ball = ball;
	mu.unlock();
}

ballParams Form::getBall()
{
	mu.lock();
	ballParams ret = ball;
	mu.unlock();
	return ret;
}

void Form::mouseButtonPressed(int x, int y)
{
	for (int i = 0; i < clickers.size(); i++)
	{
		if()
	}
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
