#include <iostream>
#include <string>
#include "xml.h"

xml arq;
config *arena_config;

int main(int argc, char **argv)
{
    arq.readXML(argv[1]);
    arena_config = arq.readSVG();

    return 0;
}