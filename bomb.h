class bomb
{
private:
    double position[3] = {0};
    double foward[3] = {0};

    double speed = 1.0;
    double radius = 5.0;

public:
    bomb(double* pos, double* fow);
    ~bomb();

    void move(int elapsed_time);
    void display();
    double* get_position();
    
    void set_cam();
};
