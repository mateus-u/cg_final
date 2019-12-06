#include "enemie.h"
#include <stdlib.h>

enemie::enemie(circle *cir) : airplane(cir)
{
    this->materialEmission[0] = 0.4;
    this->materialEmission[1] = 0.4;
    this->materialEmission[2] = 0.4;
    this->materialEmission[3] = 1.0;

    this->materialColor[0] = 0.8;
    this->materialColor[1] = 0.0;
    this->materialColor[2] = 0.0;
    this->materialColor[3] = 1.0;

    this->mat_specular[0] = 0.9;
    this->mat_specular[1] = 0.9;
    this->mat_specular[2] = 0.9;
    this->mat_specular[3] = 1.0;

    this->mat_shininess[0] = 50.0;

    this->position[2] = 100;
}

enemie::~enemie()
{
}

void enemie::random_move(int elapsed_time)
{

    if (cont > 10)
    {
        i = rand() % 5;
        cont = 0;
    }
    if (i == 1)
    {
        right();
        foward_z_0();
    }
    else if (i == 2)
    {
        left();
        foward_z_0();
    }
    else if (i == 3)
    {
        up();
    }
    else if (i == 4)
    {
        down();
    }

    move(elapsed_time);
    foward_z_0();

    cont++;
}

