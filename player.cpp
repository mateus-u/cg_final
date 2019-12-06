#include "player.h"

player::player(circle *cir) : airplane(cir)
{
    this->materialEmission[0] = 0.4;
    this->materialEmission[1] = 0.4;
    this->materialEmission[2] = 0.4;
    this->materialEmission[3] = 1.0;

    this->materialColor[0] = 0.0;
    this->materialColor[1] = 0.8;
    this->materialColor[2] = 0.0;
    this->materialColor[3] = 1.0;

    this->mat_specular[0] = 0.9;
    this->mat_specular[1] = 0.9;
    this->mat_specular[2] = 0.9;
    this->mat_specular[3] = 1.0;

    this->mat_shininess[0] = 50.0;

    this->position[2] = 8;
}

player::~player()
{
}

void player::fire()
{

    if (bullets.size() < 5)
    {
        bullet *b = new bullet(position, foward);
        b->set_enemie(false);
        bullets.push_back(b);
    }
}
