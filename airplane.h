#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <vector>

#include "forms.h"
#include "loadTexture.h"
#include "bomb.h"
#include "bullet.h"

using namespace std;

class airplane
{
private:
    circle *circ;

protected:
    GLfloat materialEmission[5] = {0};
    GLfloat materialColor[5] = {0};
    GLfloat mat_specular[5] = {0};
    GLfloat mat_shininess[5] = {0};

    double position[3] = {0};
    double foward[3] = {1, 1, 1};

    bomb *bomb_ = NULL;

    double radius;

    double theta_x = 0;
    double theta_y = 0;
    double theta_z = 0;

    double angle_helix = 0.0;

    bool up_ = false;
    bool down_ = false;
    bool left_ = false;
    bool right_ = false;

    bool show_cannon = true;

public:
    airplane(circle *cir);
    ~airplane();
    void set_foward(double x, double y, double z);
    double get_radius();
    void set_radius(double r);
    void display();
    void move(int elapsed_time);
    void left(int elapsed_time);
    void right(int elapsed_time);
    double *get_position();
    double *get_foward();
    void up();
    void down();
    void foward_z_0();
    void teleport(circle *ground);
    double *intersection(double rad);
    void load_obj();

    void fire_bomb();
    double *get_bomb_position();
    void delete_bomb();
    void move_bomb(double elapsed_time);
    bool bomb_lauched();
    void display_bomb();
    void set_bomb_cam();

    vector<bullet *> bullets;

    double speed = 1;
    double bullet_speed = 1;

    double cannon_foward[3] = {1, 1, 1};
    double cannon_angle = 0;
};

#endif