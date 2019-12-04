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
            this->player1->set_foward(arena_config->get_lines()[0]->get_x2(), arena_config->get_lines()[0]->get_y2(), 0);
        }
    }

    this->runway = arena_config->get_lines()[0];
}

arena::~arena()
{
}

void arena::display(bool *key_status, int elapsed_time)
{
    double* player_pos = player1->get_position();
    double* player_fow = player1->get_foward();
    glLoadIdentity();
    gluLookAt(player_pos[0] - 50 * player_fow[0], player_pos[1] - 50 * player_fow[1] , player_pos[2] + 15, player_pos[0] + 150 * player_fow[0], player_pos[1] + 150 * player_fow[1], player_pos[2] + 1 * player_fow[2], 0, 0, 1);

    this->ground->display();

    this->runway->display();

    this->player1->display();

    if (key_status['u'])
        player1->move(elapsed_time);

    if (key_status['a']){
        player1->left();
        player1->foward_z_0();
    }
        

    if (key_status['d']){
        player1->right();
        player1->foward_z_0();
    }

    if (key_status['w']){
        
        player1->up();
    }
        
    else if (key_status['s']){
        
        player1->down();
    }

    else{

        player1->foward_z_0();
    }

    for (int i = 0; i < this->gBases.size(); i++)
    {

        this->gBases[i]->display();
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {

        this->enemies[i]->display();
    }
}
