#include <string>
#include <iostream>
#include "tinyxml.h"
#include "config.h"

using namespace std;

#ifndef XML_H
#define XML_H

class xml
{
private:

    string caminho_arena;
    double vel_jogador;
    double vel_tiro;
    Config* arena;

public:

    xml();
    ~xml();

    void readXML(char* caminho);
    Config* readSVG();

};

#endif