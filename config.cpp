#include "config.h"
#include <iostream>

using namespace std;

config::config(/* args */)
{
}

config::~config()
{
}

void config::addCircle(circle *circ)
{
    this->circles.push_back(circ);
}
void config::addLine(line *li)
{
    this->lines.push_back(li);
}

void config::display()
{
    for (int i = 0; i < circles.size(); i++)
    {
        circles[i]->display(0, 0, 1, 1);
    }

    for (int i = 0; i < lines.size(); i++)
    {
        lines[i]->display(0);
    }
}

vector<circle*> config::get_circles(){
    return this->circles;
}
vector<line *> config::get_lines(){
    return this->lines;
}
