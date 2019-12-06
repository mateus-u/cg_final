class bullet
{
private:

    double position[3] = {0};
    double foward[3] = {0};
    double speed = 1.0;
    double radius = 3;

    bool enemie;

public:

    bullet(double *pos, double *fow);
    ~bullet();

    void move(int elapsed_time);
    void display();
    double *get_position();
    bool is_enemie();
    void set_enemie(bool e);
};
