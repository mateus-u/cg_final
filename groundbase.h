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
public:
    groundbase(circle* cir);
    ~groundbase();

    void display();
};

#endif
