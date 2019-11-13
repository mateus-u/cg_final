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

void forms::set_color(double r, double g, double b){

    this->R = r;
    this->G = g;
    this->B = b;
}

circle::circle(double cx, double cy, double radius, string color)
{
    this->cx = cx;
    this->cy = cy;
    this->r = radius;

    double r, g, b;

    string2rgb(color, &r, &g, &b);

    set_color(r, g, b);

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
    glColor3f(R, G, B);
    glBegin(GL_POLYGON);
    for (i = 0; i < 360; i += 1)
    {
        x = cx + r * cos(M_PI * i / 180);
        y = cy + r * sin(M_PI * i / 180);
        glVertex3f(x, y, 0);
    }
    glEnd();
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

    glLineWidth(5.0);
    glBegin(GL_LINES);

    glColor3f(R, G, B);
    glVertex3f(x1, y1, -10);
    glVertex3f(x2, y2, -10);

    glEnd();
}
