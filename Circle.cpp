#include "Circle.h"
#include "Figure.h"

Circle::Circle()
{
	get_shape() = make_new_figure(30);
	set_color();
}

Circle::~Circle()
{
	delete circle;
}

Circle* Circle::clone(){
	return new Circle(*this);
}

FloatRect  Circle::get_global_bounds()
{
	return circle->getGlobalBounds();
}

