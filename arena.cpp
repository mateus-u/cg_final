#include "arena.h"
#include <iostream>

using namespace std;

void Arena::addCirculo(Circulo *circ)
{
    this->circulos.push_back(circ);
}
void Arena::addLinha(Linha *li)
{
    this->linhas.push_back(li);
}

void Arena::display()
{

    for (int i = 0; i < circulos.size(); i++)
    {
        circulos[i]->display();
    }

    for (int i = 0; i < linhas.size(); i++)
    {
        linhas[i]->display();
    }
}