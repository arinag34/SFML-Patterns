#pragma once
#include  "SFML/Graphics.hpp"
using namespace sf;
class Memento {
	virtual Vector2f  memento_get_position()const = 0;
	virtual Color  memento_get_color()const = 0;
	virtual int  memento_get_points() const = 0;
	virtual int  memento_get_radius() const = 0;
};