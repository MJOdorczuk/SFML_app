#pragma once
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <list>

using namespace std;

struct formParams {
	int width;
	int height;
	string title;
	int x, y;
	bool visible = true;
	bool closing = false;
};

/*
Windows form class
The really basic one
Only for educational use
*/
class Form
{
public:
	static const int CLOSE = 1;
	static const int NONE = 0;
private:
	// The form's thread
	thread * formThread;
	formParams params;
	mutex mu;
	bool threadRunning = true;

	void closeForm();
	bool getThreadRunning();
public:
	Form(int width, int height);
	Form(int width, int height, string title);
	~Form();

	void detachThread();
	void joinThread();
	void setTitle(string title);
	int update(sf::RenderWindow * window);
	string getTitle();
	
	bool hasToClose();
};

