#pragma once
#include "Figure.h"
class Rectangle : public Figure {
	Color color;
	RectangleShape* rectangle;
public:

	Rectangle();
	~Rectangle();
	Rectangle* clone();
	FloatRect get_global_bounds();
};