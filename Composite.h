#pragma once
#include <vector>
#include <iostream>
#include "Figure.h"
using namespace std;
using namespace sf;

class Composite : public Figure {
private:
    vector<Figure*> array_of_figures;
	Color color;
public:
	Composite() {
		cout << "added\n";
	}

	Composite(Figure* figure)
	{
		vector<Figure*> array_of_figures(1);
		array_of_figures[array_of_figures.size() - 1] = figure;
		figure->set_color();
	}

	~Composite() {
		cout << "deleted\n";
		for (Figure* figures : array_of_figures) {
			delete figures;
		}

	}

	Composite* clone() {
		return new Composite(*this);
	}

	void return_default()
	{
		for (Figure* figure : array_of_figures) {
			figure->return_default();
		}
	}

    void Add(Figure* figures)
    {
        Composite* ifcomposite = dynamic_cast<Composite*>(figures);

        if (ifcomposite)
        {
            for (auto figures : ifcomposite->array_of_figures) {
                Add(figures);
            }
        }
        else {
            Figure* temp = figures->clone();
            temp->get_shape().move(20, 20);

            array_of_figures.push_back(temp);
			set_color();

            delete ifcomposite, temp;
        }


    }
    const vector<Figure*>& get_group() const {
        return array_of_figures;
    }
    bool mouse_clicked(int mouse_x, int mouse_y) override {
        for (Figure* figure : array_of_figures) 
		{
            if (figure->get_shape().getGlobalBounds().contains(mouse_x, mouse_y))
				return true;
        }

        return false;
    }
    void cancel_select() override {
        is_selected = false;
    }
    void select() override {
        is_selected = true;
    }
    void Draw(RenderWindow* window) override {
        for (Figure* figure : array_of_figures) {
            window->draw(figure->get_shape());
        }
    }
    void move(int x_vector, int y_vector) override {
        for (Figure* figure : array_of_figures) {
            figure->get_shape().move(x_vector, y_vector);
        }

    }
    void emphasized(Color col) override {
        for (Figure* figure : array_of_figures) {
            figure->get_shape().setFillColor(col);
        }
    }

	FloatRect get_global_bounds()
	{
		FloatRect composite, _figure;
		if (array_of_figures.size() == 0)
		{
			return FloatRect();
		}
		if (array_of_figures.size() >= 1)
		{
			composite = array_of_figures[0]->get_global_bounds();
		}
		float width = composite.left + composite.width;
		float height = composite.top + composite.height;
		for (Figure* figure : array_of_figures)
		{
			_figure = figure->get_global_bounds();
			if (height < _figure.top + _figure.height)
			{
				height = _figure.top + _figure.height;
			}
			if (width < _figure.left + _figure.width)
			{
				width = _figure.left + _figure.width;
			}
			if (composite.left > _figure.left)
			{
				composite.left = _figure.left;
			}

			if (composite.top > _figure.top)
			{
				composite.top = _figure.top;
			}
		}
		composite.width = width - composite.left;
		composite.height = height - composite.top;
		return composite;
	}
	int get_index(Figure* _figure)
	{
		if (array_of_figures.size() == 0)
		{
			return -1;
		}
		else
		{
			int i;
			for (i = 0; i < array_of_figures.size(); i++)
			{
				if (_figure == array_of_figures[i])
				{
					return i;
				}
			}
			return -1;
		}
	}
};