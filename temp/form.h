#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

using namespace std;

class Form
{
private:
	sf::RenderWindow window;
	thread * formThread;
	int width, height;
	string title;
	mutex mu;
public:
	Form(int width, int height);
	Form(int width, int height, string title);
	~Form();

	void detachThread();
	void joinThread();
	void setTitle(string title);
	string getTitle();
};

