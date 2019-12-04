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
        circles[i]->display();
    }

    for (int i = 0; i < lines.size(); i++)
    {
        lines[i]->display();
    }
}

circle* config::get_circle(int i){
    return this->circles[i];
}
vector<line *> config::get_lines(){
    return this->lines;
}
