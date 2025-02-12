#include "Figure.h"

CircleShape Figure:: make_new_figure(int sides) {
	CircleShape temp;
	temp.setPointCount(sides);
	temp.setRadius(RADIUS);
	return temp;
}

CircleShape& Figure::get_shape() {
	return figure;
}

bool Figure::mouse_clicked(int mouse_x, int mouse_y) {
	if (figure.getGlobalBounds().contains(mouse_x, mouse_y)) {
		return true;
	}
	return false;
}

void Figure::move(int x_vector, int y_vector) {
	figure.move(x_vector, y_vector);
}

void Figure::select() {
	is_selected = true;
}

void Figure::cancel_select() {
	is_selected = false;
}

void Figure::emphasized(Color col) {
	figure.setFillColor(col);
}

void Figure::Draw(RenderWindow* window) {
	window->draw(figure);
}

void  Figure::return_default()
{
	figure.setRadius(RADIUS);
	set_color();
}

void Figure::set_scale() {
	figure.setRadius(2*RADIUS);
}