#include "forms.h"

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

void circle::display()
{
    int i;
    GLfloat x, y;
    glDisable(GL_LIGHTING);
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (i = 0; i < 360; i += 1)
    {
        x = cx + r * cos(M_PI * i / 180);
        y = cy + r * sin(M_PI * i / 180);
        glVertex3f(x, y, 0);
    }
    glEnd();
    glEnable(GL_LIGHTING);
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

void line::display()
{
    glDisable(GL_LIGHTING);

    glLineWidth(500.0);
    glBegin(GL_LINES);

    glColor3f(R, G, B);
    glVertex3f(x1, y1, 0.03);
    glVertex3f(x2, y2, 0.03);

    glEnd();

    glEnable(GL_LIGHTING);
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