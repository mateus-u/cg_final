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

    void display();
};
