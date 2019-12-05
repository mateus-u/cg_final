#ifndef FORMS_H
#define FORMS_H 

#include <string>

using namespace std;

class forms
{
protected:
    double R;
    double G;
    double B;

public:
    forms();
    ~forms();
    void set_color(double r, double g, double b);
};

class circle : public forms
{
private:
    double cx;
    double cy;
    double r;
    string color;
    void string2rgb(string cor, double *r, double *g, double *b);

public:
    circle(double cx, double cy, double r, string cor);
    ~circle() {}
    void display();
    double get_radius();
    double get_centerx();
    double get_centery();
    string get_color();
};

class line : public forms
{
private:
    double x1;
    double y1;
    double x2;
    double y2;

public:
    line(double x1, double y1, double x2, double y2, string style);
    ~line() {}
    void display();
    double get_x1();
    double get_y1();
    double get_x2();
    double get_y2();
};

#endif