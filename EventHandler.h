#pragma once

#include "Figure.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Composite.h"
#include "Controller.h"

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class EventHandler {
private:
    vector<Figure*> _figures_vector;
    Circle circle;
    Rectangle rectangle;
    RenderWindow* window;
    static Controller* scene_controller_;
    string path = "memento.txt";
    ofstream output;

public:
    EventHandler();
    ~EventHandler();

    void display_figures();
    void unselect_all_figures();

    EventHandler(EventHandler& other) = delete;
    void operator=(const EventHandler&) = delete;

    void event_action();
    void save_in_file();
    void load_file(string path);
    void ininitialize(int pointCount, int r, int g, int b, int posX, int posY, int radius);
    int get_data(string line, string tag);
};

