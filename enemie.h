#ifndef ENEMIE_H
#define ENEMIE_H

#include "airplane.h"

class enemie : public airplane
{

private:
    circle* circ;
    int cont =0;
    int i = -1;
    
public:
    enemie(circle* cir);
    ~enemie();
    void random_move(int elapsed_time);
    void fire();
};

#endif