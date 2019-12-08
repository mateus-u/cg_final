#include "arena.h"
#include "math.h"
#include "raster.h"
#include "loadTexture.h"
#include <iostream>

using namespace std;

GLuint ground_texture = 0;
GLuint sky_texture = 0;
GLuint background_texture = 0;
GLuint way_texture = 0;

/*Testes*/
/*Testes*/

arena::arena(config *arena_config)
{

    this->arena_config = arena_config;

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
            e->set_foward(e->get_position()[0] * (-500), e->get_position()[1] * 500, 50);
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
            this->player1 = new player(arena_config->get_circles()[i]);
            this->player1->set_radius(this->player1->get_radius() * 2);
            this->player1->set_foward(arena_config->get_lines()[0]->get_x2(), arena_config->get_lines()[0]->get_y2(), 8);
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

void arena::reset()
{
    delete player1;

    for (int i = 0; i < enemies.size(); i++)
    {
        delete enemies[i];
    }
    enemies.clear();
    for (int i = 0; i < gBases.size(); i++)
    {
        delete gBases[i];
    }
    gBases.clear();

    for (int i = 0; i < arena_config->get_circles().size(); i++)
    {

        if (arena_config->get_circles()[i]->get_color() == "red")
        {
            enemie *e = new enemie(arena_config->get_circles()[i]);
            e->set_foward(this->ground->get_centerx(), this->ground->get_centery(), 50);
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
            this->player1 = new player(arena_config->get_circles()[i]);
            this->player1->set_radius(this->player1->get_radius() * 2);
            this->player1->set_foward(arena_config->get_lines()[0]->get_x2(), arena_config->get_lines()[0]->get_y2(), 8);
            player1->bullet_speed = arena_config->bullet_player_speed;
            player1->speed = arena_config->player_speed;
        }
    }

    collision = false;
    win = false;
    kills_gbase = 0;
    kills_plane = 0;
}

bool arena::display(bool *key_status, bool *mouse_status, int elapsed_time, double mouseX, double mouseY)
{

    char msg[50] = "";

    glLoadIdentity();
    sprintf(msg, "FPS: %d", 1000 / elapsed_time);
    PrintText(0.0, 0.0, msg, 0, 1, 0);

    if (collision)
    {
        if (key_status['r'] || key_status['R'])
        {
            reset();
            key_status['u'] = false;
        }

        glLoadIdentity();
        sprintf(msg, "VOCE PERDEU");
        PrintText(0.4, 0.5, msg, 1, 0, 0);

        sprintf(msg, "ESTATISTICAS");
        PrintText(0.4, 0.4, msg, 1, 0, 0);

        sprintf(msg, "Avioes Mortos %d", kills_plane);
        PrintText(0.17, 0.3, msg, 1, 0, 0);

        sprintf(msg, "Bases Destruidas %d", kills_gbase);
        PrintText(0.57, 0.3, msg, 1, 0, 0);

        return false;
    }
    else if (win)
    {

        if (key_status['r'] || key_status['R'])
        {
            reset();
            key_status['u'] = false;
        }

        glLoadIdentity();
        sprintf(msg, "           VOCE VENCEU");
        PrintText(0.4, 0.5, msg, 0, 1, 0);

        sprintf(msg, "PRESSIONE R PARA JOGAR NOVAMENTE");
        PrintText(0.4, 0.3, msg, 0, 1, 0);

        return false;
    }

    double *player_pos = player1->get_position();
    double *player_fow = player1->get_foward();

    if (key_status['1'])
    {
        glLoadIdentity();
        gluLookAt(player_pos[0] + 9 * player_fow[0], player_pos[1] + 9 * player_fow[1], player_pos[2] + 7,
                  player_pos[0] + 150 * player_fow[0], player_pos[1] + 150 * player_fow[1], player_pos[2] + 1 * player_fow[2], 0, 0, 1);
    }
    else if (key_status['2'])
    {
    }
    else if (key_status['3'])
    {
        glLoadIdentity();
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
        if (key_status['u'])
            enemies[i]->random_move(elapsed_time);

        if (dist2d(this->enemies[i]->get_position(), center) >= this->radius +15)
            enemies[i]->teleport(this->ground);

        if (dist(player1->get_position(), enemies[i]->get_position()) < (player1->get_radius() + enemies[i]->get_radius()))
        {
            collision = true;
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

                collision = true;
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
                plane_ = true;
                index = k;
                kills_plane++;
            }
        }
    }

    for (int i = 0; i < this->gBases.size(); i++)
    {
        if (dist(player1->get_position(), gBases[i]->get_position()) < gBases[i]->get_radius() + player1->get_radius())
        {

            collision = true;
        }

        if (player1->bomb_lauched())
        {
            if (dist(player1->get_bomb_position(), gBases[i]->get_position()) < gBases[i]->get_radius())
            {
                gbase_ = true;
                index = i;
                kills_gbase++;

                player1->delete_bomb();
            }
        }
    }

    if (key_status['u'])
    {
        player1->move(elapsed_time);

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
    }

    if (key_status['+'])
    {
        this->player1->speed += 0.3;
        key_status['+'] = false;
    }

    if (key_status['-'])
    {
        this->player1->speed -= 0.3;
        key_status['-'] = false;
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
        }
    }

    for (int i = 0; i < this->gBases.size(); i++)
    {
        this->gBases[i]->display();
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i]->display();
    }

    if (gbase_)
    {

        vector<groundbase *>::iterator it;
        it = gBases.begin();
        it += index;

        gBases.erase(it);

        index = 0;
        gbase_ = false;
    }

    if (plane_)
    {

        vector<enemie *>::iterator it;
        it = enemies.begin();
        it += index;

        enemies.erase(it);

        index = 0;
        plane_ = false;
    }

    glLoadIdentity();

    int r_ = 0;
    int g_ = 1;
    int b_ = 0;

    sprintf(msg, "Aviões Destruidos: %d", kills_plane);
    PrintText(0.0, 0.69, msg, r_, g_, b_);
    sprintf(msg, "Aviões Restantes: %d", (int)enemies.size());
    PrintText(0.4, 0.69, msg, r_, g_, b_);
    sprintf(msg, "Bases Destruidos: %d", kills_gbase);
    PrintText(0.0, 0.67, msg, r_, g_, b_);
    sprintf(msg, "Bases Restantes: %d", (int)gBases.size());
    PrintText(0.4, 0.67, msg, r_, g_, b_);

    if (gBases.size() == 0)
        win = true;
    
    collision = false;
    
    return true;

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