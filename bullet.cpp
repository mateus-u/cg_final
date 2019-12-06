#include "bullet.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

bullet::bullet(double *pos, double *fow)
{

    this->position[0] = pos[0];
    this->position[1] = pos[1];
    this->position[2] = pos[2];

    this->foward[0] = fow[0];
    this->foward[1] = fow[1];
    this->foward[2] = fow[2];
}

bullet::~bullet()
{
}

void bullet::move(int elapsed_time)
{
    double d = elapsed_time * speed * 0.5;

    this->position[0] += this->foward[0] * d;
    this->position[1] += this->foward[1] * d;
}

void bullet::display()
{
    glPushMatrix();

    GLfloat materialEmission[] = {1, 1, 1, 1};
    GLfloat materialColor[] = {1, 1, 1, 1};
    GLfloat mat_specular[] = {1, 1, 1, 1};
    GLfloat mat_shininess[] = {50.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTranslated(this->position[0], this->position[1], this->position[2]);
    glutSolidSphere(this->radius / 3, 360, 360);

    glPopMatrix();
}

double *bullet::get_position()
{

    return position;
}

bool bullet::is_enemie()
{

    return enemie;
}

void bullet::set_enemie(bool e){

    enemie = e;
    
}
