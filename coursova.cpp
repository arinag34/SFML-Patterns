#include <iostream>
#include <SFML/Graphics.hpp>
#include "Controller.h"
#include "Circle.h"
#include "EventHandler.h"
using namespace sf;
int main()
{
	
	cout << "H - deformation" << endl;
	cout << "C - circle" << endl;
	cout << " R - rectangle" << endl;
	cout << "D - reset figure" << endl;
	cout << "Arrows - move" << endl;
	cout << " A - add to composite" << endl;
	cout << "Left click mouse - select one" << endl;
	cout << "Right click mouse - select 2+" << endl;
	cout << "F2 - save scene" << endl;
	cout << "F3 - load scene" << endl;

	EventHandler scene;
	scene.event_action();


	return 0;
	
}