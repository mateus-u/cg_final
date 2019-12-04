#ifndef CONFIG_H 
#define CONFIG_H

#include "forms.h"
#include <vector>

using namespace std;

class config
{
private:
    vector<circle*> circles;
    vector<line*> lines;

public:
    config();
    ~config();

    void addCircle(circle *circ);
    void addLine(line *li);

    circle* get_circle(int i);
    vector<line*> get_lines();
    
    void display();
};

#endif