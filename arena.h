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
    player *player1;
    vector<enemie *> enemies;
    vector<groundbase *> gBases;
    circle *ground;
    circle *sky;

    line *runway;

    double center[3];
    double radius;

    double camXYAngle = 0.0;
    double camXZAngle = 0.0;

    double lastX = 0;
    double lastY = 0;

    void
    display_backgroud();

public:
    arena(config *arena_config);
    ~arena();
    void display(bool *key_status, bool *mouse_status, int elapsed_time, double mouseX, double mouseY);
    void display_bomb();
    double height;
};

#endif