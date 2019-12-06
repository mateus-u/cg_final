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

class polygon
{

public:

    polygon();
    ~polygon();

    int v;
    int n;
    int t;
};

polygon::polygon()
{
}

polygon::~polygon()
{
}



class obj
{

public:
    vector<mesh *> meshes;
    vector<polygon*> poly;
    int polygon_faces = 4;

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

            if(data[0] == 'f'){

                int v[4];
                int n[4];
                int t[4];

                fscanf(objFILE, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &v[0], &n[0], &t[0], &v[1], &n[1], &t[1], &v[2], &n[2], &t[2],&v[3], &n[3], &t[3]);

                polygon* p1 = new polygon();
                polygon* p2 = new polygon();
                polygon* p3 = new polygon();
                polygon* p4 = new polygon();

                p1->v = v[0];
                p1->n = n[0];
                p1->t = v[0];
                
                p2->v = v[1];
                p2->n = n[1];
                p2->t = v[1];
                
                p3->v = v[2];
                p3->n = n[2];
                p3->t = v[2];

                p4->v = v[3];
                p4->n = n[3];
                p4->t = v[3];
            
                poly.push_back(p1);
                poly.push_back(p2);
                poly.push_back(p3);
                poly.push_back(p4);



                
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

        cout << poly.back()->v << endl;
    }
};

#endif