#include <vector>
#include "formas.h"

using namespace std;

#ifndef ARENA_H
#define ARENA_H

class Arena
{
private:
    vector<Circulo*> circulos;
    vector<Linha*> linhas;

public:
    Arena() {}
    ~Arena() {}

    void addCirculo(Circulo* circ);
    void addLinha(Linha* li);

    void display();
};

#endif