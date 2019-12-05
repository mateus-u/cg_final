#ifndef ARENA_H
#define ARENA_H

#include <vector>

#include "forms.h"
#include "player.h"
#include "enemie.h"
#include "groundbase.h"
#include "forms.h"
#include "config.h"

using namespace std;

class arena
{
private:
    player* player1;
    vector<enemie*> enemies;
    vector<groundbase*> gBases;
    circle* ground;
    line* runway;

    double center[3];
    double radius;

public:
    arena(config* arena_config);
    ~arena();
    void display(bool* key_status, int elapsed_time);
};

#endif