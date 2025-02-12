#pragma once
#include "Circle.h"
#include "Rectangle.h"

class FigureCreator
{
public:
	virtual Figure* create_figure(int type);
};

