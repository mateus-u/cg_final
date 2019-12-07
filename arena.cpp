#include "arena.h"
#include "math.h"
#include "loadTexture.h"
#include <iostream>

using namespace std;

GLuint ground_texture = 0;
GLuint sky_texture = 0;
GLuint background_texture = 0;
GLuint way_texture = 0;

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
            e->fire_freq = arena_config->fire_frequency;
            e->speed = arena_config->enemie_speed;
            e->bullet_speed = arena_config->bullet_enemy_speed;
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
    background_texture = LoadTextureRAW("model/back.bmp");
    way_texture = LoadTextureRAW("model/way.bmp");

    this->height = player1->get_radius() * 9;

    player1->bullet_speed = arena_config->bullet_player_speed;
    player1->speed = arena_config->player_speed;
}

arena::~arena()
{
}

void arena::display_backgroud()
{
    int i;
    GLfloat x, y;

    GLfloat materialEmission[] = {0.3, 0.3, 1, 1};
    GLfloat materialColorA[] = {0.2, 0.2, 1, 1};
    GLfloat materialColorD[] = {0.2, 0.2, 1, 1};
    GLfloat mat_specular[] = {0.2, 0.2, 1, 1};
    GLfloat mat_shininess[] = {100.0};

    glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
    glMaterialfv(GL_FRONT, GL_AMBIENT, materialColorA);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialColorD);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, background_texture);

    glPushMatrix();

    glTranslated(center[0], center[1], 0);
    glRotated(90, 1, 0, 0);
    // Number of segments a circle is divided into.
    const unsigned DIV_COUNT = 4096;

    // Calculate angle increment from point to point, and its cos/sin.
    float angInc = 2.0f * M_PI / static_cast<float>(DIV_COUNT);
    float cosInc = cos(angInc);
    float sinInc = sin(angInc);

    float texInc = 1.0f / static_cast<float>(DIV_COUNT);
    float rad = radius * 1.3;

    // Draw cylinder.
    glBegin(GL_TRIANGLE_STRIP);

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(rad, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(rad, height, 0.0f);

    float xc = 1.0f;
    float yc = 0.0f;
    float texCoord = 0.0f;
    for (unsigned iDiv = 1; iDiv < DIV_COUNT; ++iDiv)
    {
        float xcNew = cosInc * xc - sinInc * yc;
        yc = sinInc * xc + cosInc * yc;
        xc = xcNew;
        texCoord += texInc;
        glTexCoord2f(texCoord, 0.0f);
        glVertex3f(rad * xc, 0.0f, rad * yc);
        glTexCoord2f(texCoord, 1.0f);
        glVertex3f(rad * xc, height, rad * yc);
    }

    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(rad, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(rad, height, 0.0f);

    glEnd();

    glPopMatrix();
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

void arena::display(bool *key_status, bool *mouse_status, int elapsed_time, double mouseX, double mouseY)
{
    double *player_pos = player1->get_position();
    double *player_fow = player1->get_foward();

    glLoadIdentity();

    if (key_status['1'])
    {

        gluLookAt(player_pos[0] + 9 * player_fow[0], player_pos[1] + 9 * player_fow[1], player_pos[2] + 7,
                  player_pos[0] + 150 * player_fow[0], player_pos[1] + 150 * player_fow[1], player_pos[2] + 1 * player_fow[2], 0, 0, 1);
    }
    else if (key_status['2'])
    {
    }
    else if (key_status['3'])
    {
        gluLookAt(player_pos[0] - 90 * player_fow[0], player_pos[1] - 90 * player_fow[1], player_pos[2] + 25,
                  player_pos[0] + 150 * player_fow[0], player_pos[1] + 150 * player_fow[1], player_pos[2] + 1 * player_fow[2], 0, 0, 1);
    }

    display_backgroud();
    this->ground->display(0, ground_texture, 1, 10);

    this->sky->display(player1->get_radius() * 9, sky_texture, -1, 1);

    this->runway->display(way_texture);

    this->player1->display();
    this->player1->ligh_control();

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

        vector<bullet *>::iterator it;
        it = this->enemies[i]->bullets.begin();
        for (int j = 0; j < enemies[i]->bullets.size(); j++)
        {
            if (dist2d(this->enemies[i]->bullets[j]->get_position(), center) >= this->radius)
            {
                this->enemies[i]->bullets.erase(it);
            }
            it++;

            if (dist(player1->get_position(), enemies[i]->bullets[j]->get_position()) < (player1->get_radius()))
            {

                cout << "Faleceu" << endl;
            }
        }
    }

    vector<bullet *>::iterator it;
    it = this->player1->bullets.begin();
    for (int j = 0; j < player1->bullets.size(); j++)
    {
        if (dist2d(this->player1->bullets[j]->get_position(), center) >= this->radius)
        {
            this->player1->bullets.erase(it);
        }
        it++;

        for (int k = 0; k < enemies.size(); k++)
        {

            if (dist(enemies[k]->get_position(), player1->bullets[j]->get_position()) < (enemies[k]->get_radius()))
            {

                cout << "matou" << endl;
            }
        }
    }

    for (int i = 0; i < this->gBases.size(); i++)
    {
        if (dist(player1->get_position(), gBases[i]->get_position()) < gBases[i]->get_radius() + player1->get_radius())
        {

            cout << dist(player1->get_position(), gBases[i]->get_position()) << endl;

            cout << "colisão gb" << endl;
        }

        if (player1->bomb_lauched())
        {
            if (dist(player1->get_bomb_position(), gBases[i]->get_position()) < gBases[i]->get_radius())
            {
                cout << "acertou miseravel" << endl;
                player1->delete_bomb();
                cout << "deleted" << endl;
            }
        }
    }

    if (key_status['u'])
    {
        player1->move(elapsed_time);
    }

    if (key_status['a'])
    {
        player1->left(elapsed_time);
    }

    else if (key_status['d'])
    {
        player1->right(elapsed_time);
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
    if (mouse_status[2])
    {
        camXYAngle += mouseX - lastX;
        camXZAngle += mouseY - lastY;

        camXYAngle = (int)camXYAngle % 360;
        camXZAngle = (int)camXZAngle % 360;

        lastX = mouseX;
        lastY = mouseY;
    }
    if (mouse_status[1])
    {
        if (!player1->bomb_lauched())
            player1->fire_bomb();
    }

    if (mouse_status[0])
    {
        player1->fire();
        mouse_status[0] = false;
    }

    if (player1->bomb_lauched())
    {
        player1->move_bomb(elapsed_time);
        if (player1->get_bomb_position()[2] < 0)
        {
            player1->delete_bomb();
            cout << "deleted" << endl;
        }
        cout << "lancou" << endl;
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

void arena::display_bomb()
{

    if (player1->bomb_lauched())
    {
        player1->set_bomb_cam();

        this->ground->display(0, ground_texture, 1, 10);

        this->runway->display(way_texture);

        //this->player1->display();

        for (int i = 0; i < this->gBases.size(); i++)
        {
            this->gBases[i]->display();
        }

        for (int i = 0; i < this->enemies.size(); i++)
        {
            this->enemies[i]->display();
        }

        player1->display_bomb();
    }
}