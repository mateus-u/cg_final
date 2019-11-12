#include <string>

using namespace std;

#ifndef FORMAS_H
#define FORMAS_H

class Circulo
{
private:
    double cx;
    double cy;
    double r;

    double R;
    double G;
    double B;

    void string2rgb(string c);

public:
    Circulo(double cx, double cy, double r, string cor);
    ~Circulo() {}
    void display();
};

class Linha
{
private:
    double x1;
    double y1;
    double x2;
    double y2;

    double R;
    double G;
    double B;

public:
    Linha(double x1, double y1, double x2, double y2, string style);
    ~Linha() {}
    void display();
};

#endif