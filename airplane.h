#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "forms.h"

class airplane
{
private:
    circle *circ;

protected:
    GLfloat materialEmission[5] = {0};
    GLfloat materialColor[5] = {0};
    GLfloat mat_specular[5] = {0};
    GLfloat mat_shininess[5] = {0};

    double position[3] = {0};
    double foward[3] = {0};
    double up[3] = {0};

    double radius;
    double speed = 1;

public:
    airplane(circle *cir);
    ~airplane();

    void set_foward(double x, double y, double z);
    void display();
    void move(int elapsed_time);
};

#endif