#include<math.h>
#include <iostream>
using namespace std;

void normalize(double* vector){

    double norma = sqrt(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
    cout << norma << endl;
    vector[0] /=norma;
    vector[1] /=norma;
    vector[2] /=norma;

}