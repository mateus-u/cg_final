#include "player.h"

player::player(circle* cir) : airplane(cir)
{
    this->materialEmission[0] = 0.5;
    this->materialEmission[1] = 0.5;
    this->materialEmission[2] = 0.5;
    this->materialEmission[3] = 1.0;

    this->materialColor[0] = 0.0;
    this->materialColor[1] = 1.0;
    this->materialColor[2] = 0.0;
    this->materialColor[3] = 1.0;

    this->mat_specular[0] = 0.6;
    this->mat_specular[1] = 0.6;
    this->mat_specular[2] = 0.6;
    this->mat_specular[3] = 1.0;

    this->mat_shininess[0] = 5.0;

    this->position[2] = 0;

    this->radius*=2;
}

player::~player()
{
}

