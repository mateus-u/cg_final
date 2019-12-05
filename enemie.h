#ifndef ENEMIE_H
#define ENEMIE_H

#include "airplane.h"

class enemie : public airplane
{

private:
    circle* circ;
public:
    enemie(circle* cir);
    ~enemie();
};

#endif