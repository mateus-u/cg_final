#include "forms.h"
#include "matrix.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>

using namespace std;

forms::forms()
{
    this->R = 1.0;
    this->G = 1.0;
    this->B = 1.0;
}

forms::~forms()
{
}

void forms::set_color(double r, double g, double b)
{
    this->R = r;
    this->G = g;
    this->B = b;
}

circle::circle(double cx, double cy, double radius, string color)
{
    this->cx = cx;
    this->cy = cy;
    this->r = radius;

    this->color = color;
    double Red, Green, Blue;
    string2rgb(color, &Red, &Green, &Blue);
    set_color(Red, Green, Blue);
}

void circle::string2rgb(string color, double *r, double *g, double *b)
{

    if (color == "blue")
    {
        *r = 0.0;
        *g = 0.0;
        *b = 1.0;
    }

    else if (color == "red")
    {
        *r = 1.0;
        *g = 0.0;
        *b = 0.0;
    }

    else if (color == "orange")
    {
        *r = 1.0;
        *g = 0.6;
        *b = 0.0;
    }

    else if (color == "green")
    {
        *r = 0.0;
        *g = 1.0;
        *b = 0.0;
    }
    else
    {
        *r = 1.0;
        *g = 1.0;
        *b = 1.0;
    }
}

void circle::display(double z, int text, int pos_normal, int qtd_text)
{
    int i;
    GLfloat x, y;

    GLfloat materialEmission[] = {0.3, 0.3, 1, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 1, 1};
    GLfloat materialColorD[] = {0.2, 0.2, 1, 1};
    GLfloat mat_specular[] = {0.2, 0.2, 1, 1};
    GLfloat mat_shininess[] = {100.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, text);
    glBegin(GL_POLYGON);

    double t = 1.3;

    for (i = 0; i < 360; i += 1)
    {
        x = cx + t * r * cos(M_PI * i / 180);
        y = cy + t * r * sin(M_PI * i / 180);
        glNormal3d(x, y, pos_normal * (z + 2));
        glTexCoord2d(qtd_text * cos(M_PI * i / 180), qtd_text * sin(M_PI * i / 180));
        glVertex3f(x, y, z);
    }
    glEnd();
}

string circle::get_color()
{

    return this->color;
}

line::line(double x1, double y1, double x2, double y2, string style)
{

    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;

    this->R = 0.0;
    this->G = 0.0;
    this->B = 0.0;
}

void line::display(int text)
{

    GLfloat materialEmission[] = {0.3, 0.3, 1, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 1, 1};
    GLfloat materialColorD[] = {0.2, 0.2, 1, 1};
    GLfloat mat_specular[] = {0.2, 0.2, 1, 1};
    GLfloat mat_shininess[] = {100.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPushMatrix();

    glBindTexture(GL_TEXTURE_2D, text);
    glTranslated((x2 + x1) / 2, (y2 + y1) / 2, 0.2);

    double vec[3] = {x2 - x1, y2 - y1, 0};
    double x_axys[3] = {1, 0, 0};
    double s = mag(vec);

    if (vec[0] > 0 && vec[1] < 0)
        glRotated(-angle_2_vector(vec, x_axys), 0, 0, 1);
    else if (vec[0] < 0 && vec[1] > 0)
        glRotated(angle_2_vector(vec, x_axys), 0, 0, 1);

    glScaled(s, 25, 1);

    glBegin(GL_POLYGON);

    glVertex3d(-1, -1, 0);
    glTexCoord2d(0, 0);
    glVertex3d(-1, 1, 0);
    glTexCoord2d(0, 1);
    glVertex3d(1, 1, 0);
    glTexCoord2d(1, 1);
    glVertex3d(1, -1, 0);
    glTexCoord2d(1, 0);

    glEnd();

    glPopMatrix();
}

double line::get_x1()
{
    return this->x1;
}
double line::get_y1()
{
    return this->y1;
}
double line::get_x2()
{
    return this->x2;
}
double line::get_y2()
{
    return this->y2;
}

double circle::get_radius()
{
    return this->r;
}
double circle::get_centerx()
{

    return this->cx;
}
double circle::get_centery()
{

    return this->cy;
}

void circle::set_radius(double radius)
{
    this->r = radius;
}