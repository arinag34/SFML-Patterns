#include "Rectangle.h"
#include "Figure.h"

Rectangle::Rectangle() {
	get_shape() = make_new_figure(4);
	set_color();
}

Rectangle::~Rectangle()
{
	delete rectangle;
}


Rectangle* Rectangle::clone(){
	return new Rectangle(*this);
}

FloatRect  Rectangle::get_global_bounds()
{
	return rectangle->getGlobalBounds();
}
