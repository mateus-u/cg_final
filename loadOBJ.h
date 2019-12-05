#ifndef LOADOBJ_H
#define LOADOBJ_H

#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

class point
{
public:
    double x;
    double y;
    double z;

    point(double x, double y, double z)
    {

        this->x = x;
        this->y = y;
        this->z = z;
    }
    ~point()
    {
    }
};

class mesh
{
public:
    vector<point *> v;
    vector<point *> vn;
    vector<point *> vt;

    mesh()
    {
    }
    ~mesh()
    {
    }
};

class obj
{

public:
    vector<mesh *> meshes;
    int mesh_count = 0;
    obj()
    {
    }
    ~obj()
    {
    }

    void load(char *nome)
    {

        int count = 0;

        FILE *objFILE = fopen(nome, "rw");

        char previus[50] = {'\0'};

        meshes.push_back(new mesh());

        bool prox = false;

        while (!feof(objFILE))
        {
            char data[50] = {'\0'};

            fscanf(objFILE, "%s", data);

            if (data[0] == 'f' && !prox)
            {
                count++;
                meshes.push_back(new mesh());
                prox = true;
            }
            double x, y, z;

            if (data[0] == 'v')
            {

                prox = false;
                if (data[1] == 't')
                {
                    //cout << "vt" << endl;
                    fscanf(objFILE, "%lf %lf %lf", &x, &y, &z);

                    meshes[count]->vt.push_back(new point(x, y, z));
                }

                else if (data[1] == 'n')
                {
                    //cout << "vn" << endl;
                    fscanf(objFILE, "%lf %lf %lf", &x, &y, &z);

                    meshes[count]->vn.push_back(new point(x, y, z));
                }

                else
                {

                    //cout << "v" << endl;
                    fscanf(objFILE, "%lf %lf %lf", &x, &y, &z);

                    meshes[count]->v.push_back(new point(x, y, z));
                }
            }

            strcpy(previus, data);
        }

        mesh_count = count + 1;
    }
};

#endif