#include "EventHandler.h"
#include "Figure.h"

EventHandler::EventHandler() {
    window = new RenderWindow(VideoMode(800, 800), "Coursova");
}

EventHandler::~EventHandler() {
    window = 0;
    _figures_vector.clear();
    delete window, _figures_vector;
}

void EventHandler::display_figures() {
    window->clear(Color(205, 92, 92));

    for (Figure* figure : _figures_vector) {
        figure->Draw(window);
    }

    window->display();
}

void EventHandler::unselect_all_figures() {
    for (Figure* figure : _figures_vector) {
        figure->cancel_select();
        figure->set_color();
    }
}

void EventHandler::event_action() {
    while (window->isOpen())
    {
        Event event;

        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case Event::Closed:
                window->close();
                break;

            case Event::KeyPressed: {

                if (event.key.code == Keyboard::R) {
                    _figures_vector.emplace_back(rectangle.clone());

                }

                if (event.key.code == Keyboard::C) {
                    _figures_vector.emplace_back(circle.clone());
                }

                if (Keyboard::isKeyPressed(Keyboard::A))
                {
                    Composite *composite = new Composite();
                    for (Figure* figure : _figures_vector)
                    {
                        if (figure->is_selected)
                        {
                            Controller::get_instance()->add_composite(composite);
                            composite->Add(figure);
                        }
                    }

                    _figures_vector.push_back(composite);
                }

                if (Keyboard::isKeyPressed(Keyboard::F2)) {
                    save_in_file();
                }

                if (Keyboard::isKeyPressed(Keyboard::F3)) {
                    load_file(path);
                }

                if (Keyboard::isKeyPressed(Keyboard::D))
                {

                    for (Figure* figure : _figures_vector) {
                        if (figure->is_selected) {
                            figure->return_default();
                        }
                    }
                    
                }
                if (Keyboard::isKeyPressed(Keyboard::H))
                {
                    for (Figure* figure : _figures_vector)
                    {
                        if (figure->is_selected)
                        {
                            figure->set_scale();
                        }
                    }
                }

                if (Keyboard::isKeyPressed(Keyboard::Key::Up))
                {
                    for (Figure* figure : _figures_vector) {
                        if (figure->is_selected) {
                            figure->move(-1.0f, -1.0f);
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Left))
                {
                    for (Figure* figure : _figures_vector) {
                        if (figure->is_selected) {
                            figure->move(-1.0f, 1.0f);
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Down))
                {
                    for (Figure* figure : _figures_vector) {
                        if (figure->is_selected) {
                            figure->move(1.0f, 1.0f);
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::Key::Right))
                {
                    for (Figure* figure : _figures_vector) {
                        if (figure->is_selected) {
                            figure->move(1.0f, -1.0f);
                        }
                    }
                }
                break;
            }

            case Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    int i = 0;
                    for (; i < _figures_vector.size(); i++)
                    {
                        if (_figures_vector[i]->mouse_clicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            unselect_all_figures();
                            _figures_vector[i]->select();
                            _figures_vector[i]->emphasized(Color::Green);

                            break;
                        }
                    }
                    if (i == _figures_vector.size()) unselect_all_figures();
                }

                if (event.mouseButton.button == Mouse::Right)
                {
                    int i = 0;
                    for (; i < _figures_vector.size(); i++)
                    {
                        if (_figures_vector[i]->mouse_clicked(event.mouseButton.x, event.mouseButton.y))
                        {
                            _figures_vector[i]->select();
                            _figures_vector[i]->emphasized(Color::Cyan);

                            break;
                        }
                    }
                    if (i == _figures_vector.size()) unselect_all_figures();
                }
            }

            default:
                break;
            }
        }

        display_figures();

    }


};


void EventHandler::save_in_file() {
    output.open(path, ofstream::out | ofstream::trunc);

    if (!output.is_open()) {
        cout << "Error!\n";
        return;
    }

    Composite* ifcomposite = new Composite();
    int i = 0;

    for (Figure* figure : _figures_vector) {
        ifcomposite = dynamic_cast<Composite*>(figure);

        if (ifcomposite)
        {
            output << "[composite#" << i << "]\n";
            for (auto c_figures : ifcomposite->get_group()) {
                output << "->" << c_figures;
                output << "\n";
            }
            output << "\t-> (end)\n";
        }
        else
        {
            output << "[figure #" << i << "]\n";
            output << "->" << figure;
            output << "\n\t-> (end)\n";
        }

        i++;

    }

    ifcomposite = 0;
    delete ifcomposite;

    output.close();
    cout << "saved\n";
}

void EventHandler::load_file(string path) {
    _figures_vector.clear();
    ifstream reader(path, ofstream::in);

    if (!reader.is_open()) {
        cout << "error" << path << "\n";
        return;
    }

    int pointCount = 0;
    int r = 0;
    int g = 0;
    int b = 0;
    int posX = 0;
    int posY = 0;
    int radius = 0;

    string line;

    while (!reader.eof())
    {
        int dots_pos;
        getline(reader, line);
        if (line.find("[figure") != string::npos) {
            cout << "\n:: figure";

            getline(reader, line);
            pointCount = get_data(line, "PointCount:");

            getline(reader, line);
            r = get_data(line, "R:");

            getline(reader, line);
            g = get_data(line, "G:");

            getline(reader, line);
            b = get_data(line, "B:");

            getline(reader, line);
            posX = get_data(line, "PosX:");

            getline(reader, line);
            posY = get_data(line, "PosY:");

            getline(reader, line);
            radius = get_data(line, "Radius:");

            _figures_vector.emplace_back(circle.clone());
            ininitialize(pointCount, r, g, b, posX, posY, radius);
        } 
        else if (line.find("[composite") != string::npos)
        {
            cout << "\n::composite";

            int c_size = 0;
            while (!reader.eof()) {

                getline(reader, line);
                if (line.find("-> (end)") != string::npos) break;

                pointCount = get_data(line, "PointCount:");

                getline(reader, line);
                r = get_data(line, "R:");

                getline(reader, line);
                g = get_data(line, "G:");

                getline(reader, line);
                b = get_data(line, "B:");

                getline(reader, line);
                posX = get_data(line, "PosX:");

                getline(reader, line);
                posY = get_data(line, "PosY:");

                getline(reader, line);
                radius = get_data(line, "Radius:");

                cout << "\ninit one...\n";

                _figures_vector.emplace_back(circle.clone());
                ininitialize(pointCount, r, g, b, posX, posY, radius);
                c_size++;
            }

            Composite* tempComposite = new Composite();

            for (int i = 0; i < c_size; i++) {
                tempComposite->Add(
                    _figures_vector[_figures_vector.size() - i - 1]
                );
            }

            for (int i = 0; i < c_size; i++) {
                _figures_vector.erase(_figures_vector.end() - 1);             
            }

            _figures_vector.emplace_back(tempComposite);
        }

    }
    cout << "\ndone\n";
    reader.close();
}

void EventHandler::ininitialize(int pointCount, int r, int g, int b, int posX, int posY, int radius) {
    _figures_vector.back()->get_shape().setPointCount(pointCount);
    _figures_vector.back()->get_shape().setFillColor(Color(r, g, b));
    _figures_vector.back()->get_shape().setPosition(posX, posY);
    _figures_vector.back()->get_shape().setRadius(radius);
}
int EventHandler::get_data(string line, string tag)
{
    int dots_pos;
    if (line.find(tag) != string::npos)
    {
        if (dots_pos = line.find(":"))
        {
            string sub_str = line.substr(dots_pos + 1);
            cout << "\n-> " << tag << " = " << sub_str << "\n";
            return std::stoi(sub_str);
        }
    }
    throw exception();
}
