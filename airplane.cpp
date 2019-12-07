#include "airplane.h"
#include "matrix.h"
#include "OBJ_Loader.h"
#include "imageloader.h"
#include "loadTexture.h"
#include <iostream>

using namespace std;

GLuint texture_plane = 0;
objl::Loader Loader;

airplane::airplane(circle *cir)
{
    this->circ = cir;
    this->position[0] = this->circ->get_centerx();
    this->position[1] = this->circ->get_centery();
    this->radius = this->circ->get_radius();

    Loader.LoadFile("model/plane.obj");

    texture_plane = LoadTextureRAW("model/plane.bmp");
}

airplane::~airplane()
{
}

/*TESTES*/

void airplane::load_obj()
{
    for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
    {
        glPushMatrix();

        objl::Mesh curMesh = Loader.LoadedMeshes[i];

        if (up_ && right_)
        {
            glRotated(-15, 1, 0, 0);
            glRotated(25, 0, 0, 1);
        }
        else if (up_ && left_)
        {
            glRotated(-15, 1, 0, 0);
            glRotated(-25, 0, 0, 1);
        }
        else if (down_ && right_)
        {
            glRotated(+15, 1, 0, 0);
            glRotated(25, 0, 0, 1);
        }
        else if (down_ && left_)
        {
            glRotated(+15, 1, 0, 0);
            glRotated(-25, 0, 0, 1);
        }
        else if (up_)
        {
            glRotated(-20, 1, 0, 0);
        }
        else if (down_)
        {
            glRotated(+20, 1, 0, 0);
        }
        else if (left_)
        {
            glRotated(-30, 0, 0, 1);
        }
        else if (right_)
        {
            glRotated(30, 0, 0, 1);
        }

        if (i == 5)
        {

            glRotated(angle_helix, 0, 0, 1);
            angle_helix += 20;

            if (angle_helix > 360)
                angle_helix = 0;
        }

        for (int j = 0; j < curMesh.Indices.size(); j += 3)
        {
            int j_1 = curMesh.Indices[j];
            int j_2 = curMesh.Indices[j + 1];
            int j_3 = curMesh.Indices[j + 2];

            glBegin(GL_TRIANGLES);

            glVertex3d(curMesh.Vertices[j_1].Position.X, curMesh.Vertices[j_1].Position.Y, curMesh.Vertices[j_1].Position.Z);
            glNormal3d(curMesh.Vertices[j_1].Normal.X, curMesh.Vertices[j_1].Normal.Y, curMesh.Vertices[j_1].Normal.Z);
            glTexCoord2d(curMesh.Vertices[j_1].TextureCoordinate.X, curMesh.Vertices[j_1].TextureCoordinate.Y);

            glVertex3d(curMesh.Vertices[j_2].Position.X, curMesh.Vertices[j_2].Position.Y, curMesh.Vertices[j_2].Position.Z);
            glNormal3d(curMesh.Vertices[j_2].Normal.X, curMesh.Vertices[j_2].Normal.Y, curMesh.Vertices[j_2].Normal.Z);
            glTexCoord2d(curMesh.Vertices[j_2].TextureCoordinate.X, curMesh.Vertices[j_2].TextureCoordinate.Y);

            glVertex3d(curMesh.Vertices[j_3].Position.X, curMesh.Vertices[j_3].Position.Y, curMesh.Vertices[j_3].Position.Z);
            glNormal3d(curMesh.Vertices[j_3].Normal.X, curMesh.Vertices[j_3].Normal.Y, curMesh.Vertices[j_3].Normal.Z);
            glTexCoord2d(curMesh.Vertices[j_3].TextureCoordinate.X, curMesh.Vertices[j_3].TextureCoordinate.Y);

            glEnd();
        }

        glPopMatrix();
    }
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
    glBindTexture(GL_TEXTURE_2D, texture_plane);
    glTranslated(position[0], position[1], position[2]);
    glRotated(-theta_z, 0, 0, 1);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, 1);

    int a = 450;

    glScaled(this->radius / a, this->radius / a, this->radius / a);

    load_obj();

    glPopMatrix();

    up_ = false;
    down_ = false;
    left_ = false;
    right_ = false;

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i]->display();
    }
}

void airplane::move(int elapsed_time)
{
    double time = double(elapsed_time) / 10;

    position[0] += foward[0] * this->speed * time;
    position[1] += foward[1] * this->speed * time;
    position[2] += foward[2] * this->speed * time;

    for (int i = 0; i < bullets.size(); i++)
    {
        bullets[i]->move(elapsed_time);
    }
}

void airplane::left(int elapsed_time)
{
    double angle = elapsed_time * speed / 1000;
    rotate_z(foward, angle);

    left_ = true;
}

void airplane::right(int elapsed_time)
{
    double angle = elapsed_time * speed / 1000;
    rotate_z(foward, -angle);

    right_ = true;
}

void airplane::up()
{
    foward[2] = 0.3;
    if (position[2] > 8 * this->radius)
    {
        foward[2] = 0.0;
    }

    up_ = true;
}

void airplane::down()
{

    foward[2] = -0.3;
    if (position[2] < 10)
    {
        foward[2] = 0.0;
    }

    down_ = true;
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

void airplane::set_radius(double r)
{
    this->radius = r;
}

void airplane::fire_bomb()
{

    this->bomb_ = new bomb(position, foward);
}

double *airplane::get_bomb_position()
{

    return bomb_->get_position();
}

void airplane::move_bomb(double elapsed_time)
{

    bomb_->move(elapsed_time);
    bomb_->display();
}

void airplane::display_bomb()
{
    bomb_->display();
}

void airplane::delete_bomb()
{

    delete (bomb_);
    bomb_ = NULL;
}

bool airplane::bomb_lauched()
{
    if (bomb_ == NULL)
        return false;
    else
        return true;
}

void airplane::set_bomb_cam()
{
    bomb_->set_cam();
}
