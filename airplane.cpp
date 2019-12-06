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

        if(i == 0){

            glRotated(angle_helix, 0, 0, 1);
            angle_helix += 15;

            if(angle_helix > 360) angle_helix = 0;

        }
        objl::Mesh curMesh = Loader.LoadedMeshes[i];
        glBindTexture(GL_TEXTURE_2D, texture_plane);

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

    glTranslated(position[0], position[1], position[2]);

    glRotated(-theta_z, 0, 0, 1);
    glRotated(180, 0, 0, 1);
    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, 1);
    int a = 120;
    glScaled(this->circ->get_radius() / a, this->circ->get_radius() / a, this->circ->get_radius() / a);

    load_obj();

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
    if (position[2] < 10)
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
