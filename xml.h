#include <string>
#include <iostream>
#include "tinyxml.h"
#include "arena.h"

using namespace std;

#ifndef XML_H
#define XML_H

class xml
{
private:

    string caminho_arena;
    double vel_jogador;
    double vel_tiro;
    Arena* arena;

public:

    xml();
    ~xml();

    void readXML(char* caminho);
    Arena* readSVG();

};

#endif