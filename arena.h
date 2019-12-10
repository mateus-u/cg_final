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
    config *arena_config;
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

    double f[3] = {0,0,0};

    double lastX = 0;
    double lastY = 0;

    double angleXY = 0;
    double angleXZ = 0;
    
    void display_backgroud();
    void reset();

    bool collision = false;
    bool win = false;

    int kills_gbase = 0;
    int kills_plane = 0;

    bool gbase_ = false;
    bool plane_ = false;
    int index = 0;

    void draw(double x, double y, double z, double r, double g, double b);

public:
    arena(config *arena_config);
    ~arena();
    bool display(bool *key_status, bool *mouse_status, int elapsed_time, double mouseX, double mouseY);
    void display_bomb();
    double height;

    void display_map();
};

#endif