#pragma once
#include <SFML/Graphics.hpp>
#include "Figure.h"
#include "Composite.h"
#include "Circle.h"
#include "Rectangle.h"
using namespace sf;

//class Memento;
//class CompositeHelper;

class Controller
{
	int count;
	vector<Figure*> array_of_figures;
	Composite* current_composite;
	string path = "memento.txt";
	Circle circle;
	Rectangle rectangle;
	ofstream output;
	static Controller* controller_instance;
public:
	Controller();
	~Controller();
	void set_composite(Composite* composite);
	void add_composite(Composite* composite);
	static Controller* get_instance();
	void add(Figure* figure);
	int get_figure_index(Figure* figure);
};

