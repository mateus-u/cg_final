#include "enemie.h"
#include <stdlib.h>

enemie::enemie(circle *cir) : airplane(cir)
{
    this->materialEmission[0] = 0.0;
    this->materialEmission[1] = 0.0;
    this->materialEmission[2] = 0.0;
    this->materialEmission[3] = 1.0;

    this->materialColor[0] = 1.0;
    this->materialColor[1] = 0.0;
    this->materialColor[2] = 0.0;
    this->materialColor[3] = 1.0;

    this->mat_specular[0] = 1.0;
    this->mat_specular[1] = 0.2;
    this->mat_specular[2] = 0.2;
    this->mat_specular[3] = 1.0;

    this->mat_shininess[0] = 50.0;

    this->position[2] = 50;

    this->show_cannon = false;
}

enemie::~enemie()
{
}
void enemie::fire()
{

    if (bullets.size() < 5)
    {
        bullet *b = new bullet(position, cannon_foward);
        b->set_enemie(true);
        b->speed = this->bullet_speed;
        bullets.push_back(b);
    }
}
void enemie::random_move(int elapsed_time)
{

    int f = rand() % (int)(10 / this->fire_freq);

    if (cont > 60)
    {
        i = rand() % 5;
        cont = 0;
    }
    if (i == 1)
    {
        right(elapsed_time);
        foward_z_0();
    }
    else if (i == 2)
    {
        left(elapsed_time);
        foward_z_0();
    }
    else if (i == 3)
    {
        if(this->position[0] < this->radius * 8);
        up();
    }
    else if (i == 4)
    {
        if(this->position[0] > 10);
        down();
    }

    if (f == 0)
    {
        fire();
    }

    move(elapsed_time);
    foward_z_0();

    cont++;
}
