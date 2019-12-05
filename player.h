#ifndef PLAYER_H
#define PLAYER_H

#include "airplane.h"

class player : public airplane
{
private:
public:
    player(circle* cir);
    ~player();
};

#endif