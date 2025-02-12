#pragma once
#include "Figure.h"
class Circle : public Figure {
	Color color;
	CircleShape* circle;
public:
	~Circle();
	Circle();
	Circle* clone();
	FloatRect get_global_bounds();
};