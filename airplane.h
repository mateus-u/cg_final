#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "forms.h"
#include "loadTexture.h"

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
    double foward[3] = {1,1,1};

    double radius;
    double speed = 1;
    double theta_x = 0;
    double theta_y = 0;
    double theta_z = 0;

    
    
public:
    airplane(circle *cir);
    ~airplane();
    void set_foward(double x, double y, double z);
    double get_radius();
    void display();
    void move(int elapsed_time);
    void left();
    void right();
    double *get_position();
    double *get_foward();
    void up();
    void down();
    void foward_z_0();
    void teleport(circle* ground);
    double* intersection(double rad);
};

#endif