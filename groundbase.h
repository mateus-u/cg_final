#ifndef GROUNDBASE_H
#define GROUNDBASE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "forms.h"

class groundbase
{
private:
    circle* circ;
    double position[3] = {};

    double angle = rand() %360;
    double speed = (rand() % 10 + 1) / 50.00;

public:
    groundbase(circle* cir);
    ~groundbase();
    void display();
    double* get_position();
    double get_radius();
    void load_obj();
};

#endif
