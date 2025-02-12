#pragma once
#include  "SFML/Graphics.hpp"
#include <fstream>
#include "Memento.h"
using namespace sf;

class Figure : public Memento {
private:
	const int RADIUS = 30;
	CircleShape figure;
public:
	bool is_selected = false;
	CircleShape make_new_figure(int sides);
	virtual Figure* clone() = 0;
	virtual CircleShape& get_shape();
	virtual bool mouse_clicked(int mouse_x, int mouse_y);
	virtual void move(int x_vector, int y_vector);
	virtual void select();
	virtual void cancel_select();
	virtual void emphasized(Color col);
	virtual void Draw(RenderWindow* window);
	void return_default();

	virtual FloatRect get_global_bounds() = 0;
	void set_scale();
	virtual void set_color() {

		figure.setFillColor(Color::Blue);
		figure.setOutlineThickness(3);
		figure.setOutlineColor(Color::White);
	}

	Vector2f  memento_get_position() const  override { return figure.getPosition(); }
	int       memento_get_points() const override { return figure.getPointCount(); }
	Color     memento_get_color()  const override { return figure.getFillColor(); }
	int       memento_get_radius() const override { return figure.getRadius(); }

	friend std::ostream& operator<<(std::ostream& os, const Figure* figure) {
		os << "\tPointCount:" << figure->memento_get_points()
			<< "\n\t R: " << (int)figure->memento_get_color().r
			<< "\n\t G: " << (int)figure->memento_get_color().g
			<< "\n\t B: " << (int)figure->memento_get_color().b
			<< "\n\tPosX: " << figure->memento_get_position().x
			<< "\n\tPosY: " << figure->memento_get_position().y
			<< "\n\tRadius: " << figure->memento_get_radius();

		return os;
	}
};

