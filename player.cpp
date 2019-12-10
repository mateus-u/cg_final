#include "player.h"

player::player(circle *cir) : airplane(cir)
{
    this->materialEmission[0] = 0.0;
    this->materialEmission[1] = 0.0;
    this->materialEmission[2] = 0.0;
    this->materialEmission[3] = 1.0;

    this->materialColor[0] = 1.0;
    this->materialColor[1] = 1.0;
    this->materialColor[2] = 1.0;
    this->materialColor[3] = 1.0;

    this->mat_specular[0] = 1.0;
    this->mat_specular[1] = 1.0;
    this->mat_specular[2] = 1.0;
    this->mat_specular[3] = 1.0;

    this->mat_shininess[0] = 50.0;

    this->position[2] = 8;

}

player::~player()
{
}

void player::fire()
{

    if (bullets.size() < 5)
    {
        bullet *b = new bullet(position, cannon_foward);
        b->set_enemie(false);
        b->speed = this->bullet_speed;
        bullets.push_back(b);
    }
}

void player::ligh_control()
{

    glPushMatrix();

    GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light_specular[] = {1.0, 0.0, 0.0, 1.0};
    GLfloat light_position[] = {0,0 ,0, -1};

    glTranslated(position[0], position[1],position[2]);

    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0);

    glPopMatrix();
}
