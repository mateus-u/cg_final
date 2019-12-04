#include <math.h>
#include <iostream>
using namespace std;

void normalize(double *vector)
{

    double norma = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
    cout << norma << endl;
    vector[0] /= norma;
    vector[1] /= norma;
    vector[2] /= norma;
}

void rotate_z(double *vector, double angle)
{

    vector[0] = cos(angle) * vector[0] - sin(angle) * vector[1];
    vector[1] = sin(angle) * vector[0] + cos(angle) * vector[1];
    vector[2] = vector[2];

    normalize(vector);
}

void rotate_y(double *vector, double angle)
{

    vector[0] = cos(angle) * vector[0] + sin(angle) * vector[1];
    vector[1] = vector[1];
    vector[2] = -sin(angle) * vector[0] + cos(angle) * vector[1];

    normalize(vector);
}

void rotate_x(double *vector, double angle)
{

    vector[0] = vector[0];
    vector[1] = cos(angle) * vector[1] - sin(angle) * vector[2];
    vector[2] = sin(angle) * vector[1] + cos(angle) * vector[2];

    normalize(vector);
}