#include "bomb.h"
#include "matrix.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

bomb::bomb(double *pos, double *fow)
{

    this->position[0] = pos[0];
    this->position[1] = pos[1];
    this->position[2] = pos[2];

    this->foward[0] = fow[0];
    this->foward[1] = fow[1];
    this->foward[2] = fow[2];
}
bomb::~bomb() {}

void bomb::move(int elapsed_time)
{

    double d = elapsed_time * speed * 0.03;

    this->position[0] += this->foward[0] * d;
    this->position[1] += this->foward[1] * d;
    this->position[2] -= d;
}

void bomb::display()
{

    double theta_z;

    double x_axys[3] = {1, 0, 0};

    if (foward[1] < 0)
        theta_z = angle_2_vector(x_axys, this->foward);
    else
        theta_z = 360 - angle_2_vector(x_axys, this->foward);

    glPushMatrix();

    GLfloat materialEmission[] = {0.3, 0.2, 0.2, 1};
    GLfloat materialColor[] = {0.0, 0.0, 0.0, 1};
    GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1};
    GLfloat mat_shininess[] = {50.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTranslated(this->position[0], this->position[1], this->position[2]);
    glRotated(-theta_z, 0, 0, 1);
    glScaled(3, 1, 1);
    glutSolidSphere(this->radius / 3, 360, 360);

    glPopMatrix();
}

double *bomb::get_position()
{

    return this->position;
}

void bomb::set_cam()
{   
    glLoadIdentity();
    gluLookAt(position[0], position[1], position[2] + 20,
              position[0], position[1], position[2]-20,
              0, 1, 0);
}
