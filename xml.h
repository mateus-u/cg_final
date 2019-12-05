#ifndef XML_H
#define XML_H

#include <string>
#include <iostream>

#include "tinyxml.h"
#include "config.h"

using namespace std;

class xml
{
private:
    string caminho_arena;
    double vel_jogador;
    double vel_tiro;
    config *arena_config;

public:
    xml();
    ~xml();
    void readXML(char *caminho);
    config *readSVG();
};

#endif