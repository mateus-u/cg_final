#ifndef MATRIX_H
#define MATRIX_H

void normalize(double *vector);


void rotate_z(double *vector, double angle);


void rotate_y(double *vector, double angle);


void rotate_x(double *vector, double angle);

float dot(double *a, double *b);

float mag(double *a);

double angle_2_vector(double *a, double *b);


#endif