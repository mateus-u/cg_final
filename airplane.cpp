#include "airplane.h"
#include "matrix.h"
#include "loadOBJ.h"
#include "imageloader.h"
#include "loadTexture.h"
#include <iostream>

using namespace std;

void load_obj();
GLuint texture_plane = 0;
obj *ob = new obj();

airplane::airplane(circle *cir)
{
    this->circ = cir;
    this->position[0] = this->circ->get_centerx();
    this->position[1] = this->circ->get_centery();
    this->radius = this->circ->get_radius();

    load_obj();
    texture_plane = LoadTextureRAW("model/plane.bmp");
}

airplane::~airplane()
{
}

/*TESTES*/

void load_obj()
{
    char name[50] = "model/plane.obj";
    ob->load(name);
}

void airplane::display()
{

    double x_axys[3] = {1, 0, 0};

    if (foward[1] < 0)
        theta_z = angle_2_vector(x_axys, this->foward);
    else
        theta_z = 360 - angle_2_vector(x_axys, this->foward);

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, this->materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, this->mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, this->mat_shininess);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTranslated(position[0], position[1], position[2]);
    //glutSolidSphere(this->circ->get_radius(), 360, 360);
    glRotated(180, 0, 0, 1);
    glRotated(-theta_z, 0, 0, 1);

    int a = 3;
    glScaled(this->circ->get_radius() / a, this->circ->get_radius() / a, this->circ->get_radius() / a);

    glBindTexture(GL_TEXTURE_2D, texture_plane);

    for (int i = 0; i < ob->poly.size(); i += 4)
    {
        glBegin(GL_QUADS);

        glTexCoord2f(ob->meshes[0]->vt[ob->poly[i]->t]->x, ob->meshes[0]->vt[ob->poly[i]->t]->y);
        glNormal3f(ob->meshes[0]->vn[ob->poly[i]->n]->x, ob->meshes[0]->vn[ob->poly[i]->n]->y, ob->meshes[0]->vn[ob->poly[i]->n]->z);
        glVertex3f(ob->meshes[0]->v[ob->poly[i]->v]->x, ob->meshes[0]->v[ob->poly[i]->v]->y, ob->meshes[0]->v[ob->poly[i]->v]->z);

        glTexCoord2f(ob->meshes[0]->vt[ob->poly[i + 1]->t]->x, ob->meshes[0]->vt[ob->poly[i + 1]->t]->y);
        glNormal3f(ob->meshes[0]->vn[ob->poly[i + 1]->n]->x, ob->meshes[0]->vn[ob->poly[i + 1]->n]->y, ob->meshes[0]->vn[ob->poly[i + 1]->n]->z);
        glVertex3f(ob->meshes[0]->v[ob->poly[i + 1]->v]->x, ob->meshes[0]->v[ob->poly[i + 1]->v]->y, ob->meshes[0]->v[ob->poly[i + 1]->v]->z);

        glTexCoord2f(ob->meshes[0]->vt[ob->poly[i + 2]->t]->x, ob->meshes[0]->vt[ob->poly[i + 2]->t]->y);
        glNormal3f(ob->meshes[0]->vn[ob->poly[i + 2]->n]->x, ob->meshes[0]->vn[ob->poly[i + 2]->n]->y, ob->meshes[0]->vn[ob->poly[i + 2]->n]->z);
        glVertex3f(ob->meshes[0]->v[ob->poly[i + 2]->v]->x, ob->meshes[0]->v[ob->poly[i + 2]->v]->y, ob->meshes[0]->v[ob->poly[i + 2]->v]->z);

        glTexCoord2f(ob->meshes[0]->vt[ob->poly[i+3]->t]->x, ob->meshes[0]->vt[ob->poly[i+3]->t]->y);
        glNormal3f(ob->meshes[0]->vn[ob->poly[i+3]->n]->x, ob->meshes[0]->vn[ob->poly[i+3]->n]->y, ob->meshes[0]->vn[ob->poly[i+3]->n]->z);
        glVertex3f(ob->meshes[0]->v[ob->poly[i+3]->v]->x, ob->meshes[0]->v[ob->poly[i+3]->v]->y, ob->meshes[0]->v[ob->poly[i+3]->v]->z);

        glEnd();
    }

    glPopMatrix();

    float l_pos[4] = {(float)this->position[0], (float)this->position[1], (float)this->position[2], 1};
    float l_fw[4] = {(float)this->foward[0], (float)this->foward[1], (float)this->foward[2], 1};
    glLightfv(GL_LIGHT0, GL_POSITION, l_pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, l_fw);
     
}

void airplane::move(int elapsed_time)
{
    double time = double(elapsed_time) / 10;

    position[0] += foward[0] * this->speed * time;
    position[1] += foward[1] * this->speed * time;
    position[2] += foward[2] * this->speed * time;
}

void airplane::left()
{
    rotate_z(foward, 0.1);
}

void airplane::right()
{
    rotate_z(foward, -0.1);
}

void airplane::up()
{
    foward[2] = 0.3;
    if (position[2] > 8 * this->radius)
    {
        foward[2] = 0.0;
    }
}

void airplane::down()
{

    foward[2] = -0.3;
    if (position[2] < 0)
    {
        foward[2] = 0.0;
    }
}

void airplane::foward_z_0()
{
    foward[2] = 0;
}

void airplane::set_foward(double x, double y, double z)
{
    this->foward[0] = x - position[0];
    this->foward[1] = y - position[1];
    this->foward[2] = z - position[2];
    normalize(foward);
}

double *airplane::get_position()
{
    return this->position;
}

double *airplane::get_foward()
{
    return this->foward;
}

void airplane::teleport(circle *ground)
{
    this->position[0] = ground->get_centerx();
    this->position[1] = ground->get_centery();
}

double airplane::get_radius()
{
    return this->radius;
}
