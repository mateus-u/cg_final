#include "arena.h"

#include <iostream>
using namespace std;

arena::arena(config *arena_config)
{

    for (int i = 0; i < arena_config->get_circles().size(); i++)
    {

        if (arena_config->get_circles()[i]->get_color() == "blue")
        {

            this->ground = arena_config->get_circles()[i];
        }

        if (arena_config->get_circles()[i]->get_color() == "red")
        {
            this->enemies.push_back(new enemie(arena_config->get_circles()[i]));
        }

        if (arena_config->get_circles()[i]->get_color() == "orange")
        {

            this->gBases.push_back(new groundbase(arena_config->get_circles()[i]));
        }

        if (arena_config->get_circles()[i]->get_color() == "green")
        {

            this->player1 = new player(arena_config->get_circles()[i]);
            this->player1->set_foward(arena_config->get_lines()[0]->get_x2(),arena_config->get_lines()[0]->get_y2(), 0);
            
        }
    }

    this->runway = arena_config->get_lines()[0];
}

arena::~arena()
{
}

void arena::display(bool* key_status, int elapsed_time)
{

    this->ground->display();

    this->runway->display();

    this->player1->display();

    if(key_status['u']) player1->move(elapsed_time);

    for (int i = 0; i < this->gBases.size(); i++)
    {

        this->gBases[i]->display();
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {

        this->enemies[i]->display();
    }

}
