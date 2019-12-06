#include <math.h>
#include <iostream>

using namespace std;

#include "matrix.h"

void normalize(double *vector)
{
    double norma = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);
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

float dot(double *a, double *b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float mag(double *a)
{
    return std::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

double angle_2_vector(double *a, double *b)
{
    double v1[3], v2[3];

    v1[0] = a[0];
    v1[1] = a[1];
    v1[2] = 0;

    v2[0] = b[0];
    v2[1] = b[1];
    v2[2] = 0;

    double angle = std::acos(dot(v1, v2) / (mag(v1) * mag(v2)));
    double PI = 3.14159265;
    angle = angle * 180.0 / PI;
    return angle;
}
