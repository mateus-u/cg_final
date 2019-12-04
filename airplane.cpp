#include "airplane.h"
#include "matrix.h"

#include <iostream>

using namespace std;

airplane::airplane(circle *cir)
{
    this->circ = cir;

    this->position[0] = this->circ->get_centerx();
    this->position[1] = this->circ->get_centery();
    this->radius = this->circ->get_radius();
}

airplane::~airplane()
{
}

void airplane::display()
{

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, this->materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, this->mat_shininess);

    glTranslated(position[0], position[1], position[2]);
    glutSolidSphere(radius, 360, 360);
    glPopMatrix();
}

void airplane::move(int elapsed_time)
{

    double time = double(elapsed_time) / 10;

    position[0] += foward[0] * this->speed * time;
    position[1] += foward[1] * this->speed * time;
    position[2] += foward[2] * this->speed * time;
}

void airplane::set_foward(double x, double y, double z)
{

    this->foward[0] = x;
    this->foward[1] = y;
    this->foward[2] = z;

    cout << foward[0] << " " << foward[1] << " " << foward[2] << endl;
    normalize(foward);
    cout << foward[0] << " " << foward[1] << " " << foward[2] << endl;

}