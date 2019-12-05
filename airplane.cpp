#include "airplane.h"
#include "matrix.h"
#include "loadOBJ.h"
#include "imageloader.h"

#include <iostream>

using namespace std;

void load_obj();
GLuint LoadTextureRAW(const char *nome);
GLuint texture = 0;

airplane::airplane(circle *cir)
{
    this->circ = cir;
    this->position[0] = this->circ->get_centerx();
    this->position[1] = this->circ->get_centery();
    this->radius = this->circ->get_radius();

    load_obj();
    texture = LoadTextureRAW("model/plane.bmp");
}

airplane::~airplane()
{
}

/*TESTES*/

GLuint LoadTextureRAW(const char *filename)
{

    GLuint texture;

    Image *image = loadBMP(filename);

    cout << image->width << endl;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D,               //Always GL_TEXTURE_2D
                 0,                           //0 for now
                 GL_RGB,                      //Format OpenGL uses for image
                 image->width, image->height, //Width and height
                 0,                           //The border of the image
                 GL_RGB,                      //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE,            //GL_UNSIGNED_BYTE, because pixels are stored
                                              //as unsigned numbers
                 image->pixels);              //The actual pixel data
    delete image;

    return texture;
}

vector<float> vx[200];
vector<float> vy[200];
vector<float> vz[200];
vector<float> nx[200];
vector<float> ny[200];
vector<float> nz[200];
vector<float> tx[200];
vector<float> ty[200];
vector<float> tz[200];
int tam;

void load_obj()
{

    obj *ob = new obj();
    char name[50] = "model/plane.obj";
    ob->load(name);

    tam = ob->mesh_count;

    for (int i = 0; i < tam; i++)
    {
        for (int j = 0; j < ob->meshes[i]->v.size(); j++)
        {

            vx[i].push_back(ob->meshes[i]->v[j]->x);
            vy[i].push_back(ob->meshes[i]->v[j]->y);
            vz[i].push_back(ob->meshes[i]->v[j]->z);
        }
        for (int j = 0; j < ob->meshes[i]->vn.size(); j++)
        {
            nx[i].push_back(ob->meshes[i]->vn[j]->x);
            ny[i].push_back(ob->meshes[i]->vn[j]->y);
            nz[i].push_back(ob->meshes[i]->vn[j]->z);
        }

        for (int j = 0; j < ob->meshes[i]->vt.size(); j++)
        {
            tx[i].push_back(ob->meshes[i]->vt[j]->x);
            ty[i].push_back(ob->meshes[i]->vt[j]->y);
        }
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
    //glutSolidSphere(this->circ->get_radius() * 2, 360, 360);
    glRotated(180, 0, 0, 1);
    glRotated(-theta_z, 0, 0, 1);
    glScaled(this->circ->get_radius() / 3, this->circ->get_radius() / 3, this->circ->get_radius() / 3);

    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS);

    for (int i = 0; i < 1; i++)
    {

        for (int j = 0; j < vx[i].size(); j++)
        {
            glTexCoord2f(tx[i][j], ty[i][j]);
            glNormal3f(nx[i][j], ny[i][j], nz[i][j]);
            glVertex3f(vx[i][j], vy[i][j], vz[i][j]);
            
            
        }
    }
    glEnd();

    glPopMatrix();
}
/*TESTES*/

/*
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

        glTranslated(position[0], position[1], position[2]);
        glRotated(-theta_z, 0, 0, 1);
        glRotated(90, 1, 0, 0);
        glutSolidTeapot(radius);

    glPopMatrix();
}
*/
void airplane::move(int elapsed_time)
{
    double time = double(elapsed_time) / 10;

    position[0] += foward[0] * this->speed * time;
    position[1] += foward[1] * this->speed * time;
    position[2] += foward[2] * this->speed * time;
}

void airplane::left()
{
    rotate_z(foward, 0.04);
}

void airplane::right()
{
    rotate_z(foward, -0.04);
}

void airplane::up()
{
    foward[2] = 0.3;
}

void airplane::down()
{
    
    foward[2] = -0.3;
    if(position[2] < 0){
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

void airplane::teleport(double radius)
{
}