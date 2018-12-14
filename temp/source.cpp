// temp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "form.h"
#include <thread>
#include <iostream>

using namespace std;


int main()
{
	Form * form;
	form = new Form(1280, 720);
	for (int i = 0; i < 10; i++)
	{
		form->setTitle(to_string(i) + "th second");
		this_thread::sleep_for(chrono::seconds(1));
		cout << i;
	}
	//this_thread::sleep_for(chrono::seconds(10));
	form->detachThread();
	system("pause");
	return 0;
}

