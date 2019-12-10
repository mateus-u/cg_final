#include "player.h"

player::player(circle *cir) : airplane(cir)
{
    this->materialEmission[0] = 0.0;
    this->materialEmission[1] = 0.0;
    this->materialEmission[2] = 0.0;
    this->materialEmission[3] = 1.0;

    this->materialColor[0] = 1.0;
    this->materialColor[1] = 1.0;
    this->materialColor[2] = 1.0;
    this->materialColor[3] = 1.0;

    this->mat_specular[0] = 1.0;
    this->mat_specular[1] = 1.0;
    this->mat_specular[2] = 1.0;
    this->mat_specular[3] = 1.0;

    this->mat_shininess[0] = 50.0;

    this->position[2] = 8;

    this->light = true;

}

player::~player()
{
}

void player::fire()
{

    if (bullets.size() < 5)
    {
        bullet *b = new bullet(position, cannon_foward);
        b->set_enemie(false);
        b->speed = this->bullet_speed;
        bullets.push_back(b);
    }
}
