#include "formas.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <math.h>
#include <iostream>

using namespace std;

Circulo::Circulo(double cx, double cy, double r, string cor)
{
    this->cx = cx;
    this->cy = cy;
    this->r = r;

    string2rgb(cor);
}

void Circulo::string2rgb(string cor)
{

    if (cor == "blue")
    {
        this->R = 0.0;
        this->G = 0.0;
        this->B = 1.0;
    }

    else if (cor == "red")
    {

        this->R = 1.0;
        this->G = 0.0;
        this->B = 0.0;
    }

    else if (cor == "orange")
    {

        this->R = 1.0;
        this->G = 0.6;
        this->B = 0.0;
    }

    else if (cor == "green")
    {

        this->R = 0.0;
        this->G = 1.0;
        this->B = 0.0;
    }
    else
    {

        this->R = 1.0;
        this->G = 1.0;
        this->B = 1.0;
    }
}

void Circulo::display()
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

Linha::Linha(double x1, double y1, double x2, double y2, string style)
{

    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;

    this->R = 0.0;
    this->G = 0.0;
    this->B = 0.0;
}

void Linha::display()
{

    glLineWidth(5.0);
    glBegin(GL_LINES);

        glColor3f(R, G, B);
        glVertex3f(x1, y1, -10);
        glVertex3f(x2, y2, -10);
    
    glEnd();
}