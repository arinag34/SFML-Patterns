#include "Controller.h"

Controller* Controller::controller_instance = nullptr;

Controller::Controller()
{
	count = 0;
	vector <Figure*> array_of_figures(count);
	current_composite = nullptr;
}

Controller::~Controller()
{
	array_of_figures.clear();
	current_composite = nullptr;
	delete current_composite;
	controller_instance = nullptr;
}

Controller* Controller::get_instance() {
	if (controller_instance == nullptr) {
		controller_instance = new Controller();
	}

	return controller_instance;
}

int Controller::get_figure_index(Figure* figure) {
	for (int i = 0; i < count; i++) {
		if (figure == array_of_figures[i])
			return i;
	}

	return -1;
}

void Controller::add(Figure* figure)
{
	if (get_figure_index(figure) != -1)
	{
		return;
	}
	vector<Figure*> newarray_of_figures(count + 1);
	for (int i = 0; i < count; i++)
	{
		newarray_of_figures[i] = array_of_figures[i];
		array_of_figures[i] = nullptr;
		delete array_of_figures[i];
	}
	newarray_of_figures[count++] = figure;
	array_of_figures.clear();
	array_of_figures = newarray_of_figures;
}

void Controller::set_composite(Composite* composite)
{
	current_composite = composite;
}

void Controller::add_composite(Composite* composite)
{
	set_composite(composite);
	add(composite);
}

