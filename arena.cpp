#include "arena.h"
#include "math.h"
#include "loadTexture.h"
#include <iostream>

using namespace std;

GLuint ground_texture = 0;
GLuint sky_texture = 0;

arena::arena(config *arena_config)
{

    for (int i = 0; i < arena_config->get_circles().size(); i++)
    {

        if (arena_config->get_circles()[i]->get_color() == "blue")
        {

            this->ground = arena_config->get_circles()[i];
            this->sky = arena_config->get_circles()[i];
        }

        if (arena_config->get_circles()[i]->get_color() == "red")
        {
            enemie *e = new enemie(arena_config->get_circles()[i]);
            e->set_foward(this->ground->get_centerx(), this->ground->get_centery(), 0);
            this->enemies.push_back(e);
        }

        if (arena_config->get_circles()[i]->get_color() == "orange")
        {

            this->gBases.push_back(new groundbase(arena_config->get_circles()[i]));
        }

        if (arena_config->get_circles()[i]->get_color() == "green")
        {
            arena_config->get_circles()[i]->set_radius(arena_config->get_circles()[i]->get_radius() * 2);
            this->player1 = new player(arena_config->get_circles()[i]);
            this->player1->set_foward(arena_config->get_lines()[0]->get_x2(), arena_config->get_lines()[0]->get_y2(), 0);
        }
    }

    this->runway = arena_config->get_lines()[0];
    this->center[0] = ground->get_centerx();
    this->center[1] = ground->get_centery();
    this->center[2] = 0;
    this->radius = ground->get_radius();

    ground_texture = LoadTextureRAW("model/Grass.bmp");
    sky_texture = LoadTextureRAW("model/sky.bmp");
}

arena::~arena()
{
}

double dist(double *p1, double *p2)
{
    double p[3];

    p[0] = p1[0] - p2[0];
    p[1] = p1[1] - p2[1];
    p[2] = p1[2] - p2[2];

    return sqrt(p[0] * p[0] + p[1] * p[1] + p[2] * p[2]);
}

double dist2d(double *p1, double *p2)
{
    double p[3];

    p[0] = p1[0] - p2[0];
    p[1] = p1[1] - p2[1];
    p[2] = p1[2] - p2[2];

    return sqrt(p[0] * p[0] + p[1] * p[1]);
}

void arena::display(bool *key_status, int elapsed_time)
{
    double *player_pos = player1->get_position();
    double *player_fow = player1->get_foward();

    glLoadIdentity();
    gluLookAt(player_pos[0] - 90 * player_fow[0], player_pos[1] - 90 * player_fow[1], player_pos[2] + 25, player_pos[0] + 150 * player_fow[0], player_pos[1] + 150 * player_fow[1], player_pos[2] + 1 * player_fow[2], 0, 0, 1);

    this->ground->display(0, ground_texture, 1);

    this->sky->display(player1->get_radius() * 9, sky_texture, -1);

    this->runway->display();

    this->player1->display();

    if (dist2d(player_pos, center) > this->radius)
    {
        player1->teleport(this->ground);
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {
        enemies[i]->random_move(elapsed_time);

        if (dist2d(this->enemies[i]->get_position(), center) >= this->radius - 10)
            enemies[i]->teleport(this->ground);

        if (dist(player1->get_position(), enemies[i]->get_position()) < (player1->get_radius() + enemies[i]->get_radius()))
        {

            cout << dist(player1->get_position(), enemies[i]->get_position()) << endl;

            cout << "colisão" << endl;
        }
    }

    for (int i = 0; i < this->gBases.size(); i++)
    {
        if (dist(player1->get_position(), gBases[i]->get_position()) < gBases[i]->get_radius() + player1->get_radius())
        {

            cout << dist(player1->get_position(), gBases[i]->get_position()) << endl;

            cout << "colisão gb" << endl;
        }
    }

    if (key_status['u'])
    {
        player1->move(elapsed_time);
    }

    if (key_status['a'])
    {
        player1->left();
        player1->foward_z_0();
    }

    else if (key_status['d'])
    {
        player1->right();
        player1->foward_z_0();
    }

    if (key_status['w'])
    {
        player1->up();
    }

    else if (key_status['s'])
    {
        player1->down();
    }

    else
    {
        player1->foward_z_0();
    }

    for (int i = 0; i < this->gBases.size(); i++)
    {
        this->gBases[i]->display();
    }

    {
        for (int i = 0; i < this->enemies.size(); i++)
        {
            //this->enemies[i]->display();
        }
    }
}
