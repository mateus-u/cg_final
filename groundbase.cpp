#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "groundbase.h"
#include "OBJ_Loader2.h"
#include "loadTexture.h"

#include <iostream>
using namespace std;

GLuint texture_gbase = 0;
objl2::Loader loader;

groundbase::groundbase(circle *cir)
{
    this->circ = cir;

    this->position[0] = cir->get_centerx();
    this->position[1] = cir->get_centery();
    this->position[2] = 0;

    loader.LoadFile("model/gbase.obj");

    texture_gbase = LoadTextureRAW("model/gbase.bmp");
}

groundbase::~groundbase()
{
}

void groundbase::load_obj()
{
    
    glPushMatrix();

    glRotated(angle, 0, 1, 0);
    angle+=speed;

    for (int i = 0; i < loader.LoadedMeshes.size(); i++)
    {

        objl2::Mesh curMesh = loader.LoadedMeshes[i];

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
    }

    glPopMatrix();

}

void groundbase::display()
{
    glPushMatrix();
    GLfloat materialEmission[] = {0, 0, 0, 1};
    GLfloat materialColor[] = {1, 1, 1, 1};
    GLfloat mat_specular[] = {1, 1, 1, 1};
    GLfloat mat_shininess[] = {50.0};
    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTranslated(this->circ->get_centerx(), this->circ->get_centery(), 0);
    
    glutWireSphere(this->get_radius(), 10, 10);

    glRotated(90, 0, 1, 0);
    glRotated(90, 0, 0, 1);
    int a = 150;
    glScaled(this->circ->get_radius() / a, this->circ->get_radius() / a, this->circ->get_radius() / a);
    glBindTexture(GL_TEXTURE_2D, texture_gbase);

    load_obj();

    glPopMatrix();
}

double *groundbase::get_position()
{

    return this->position;
}

double groundbase::get_radius()
{

    return this->circ->get_radius();
}