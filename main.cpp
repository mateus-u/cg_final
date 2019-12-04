#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string>

#include "xml.h"
#include "groundbase.h"

/*Window*/
int width = 500;
int height = 500;
/*Window*/

/*xml*/
xml arq;
config *arena_config;
/*xml*/

/*Ground Bases*/
vector<groundbase *> gb;
/*Ground Bases*/

/*Testes*/

/*Testes*/

void idle()
{
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluPerspective(45, (GLfloat)h / (GLfloat)w, 2, 50);
    else
        gluPerspective(45, (GLfloat)w / (GLfloat)h, 2, 50);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    GLfloat position[] = {0.0, 0.00, 0.0, 1.0};
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(5, 5, 40, 5, 5, 0.0, 0.0, 1.0, 0.0);

    arena_config->get_circle(0)->display();
    gb[0]->display();
    gb[1]->display();
    gb[2]->display();
    gb[3]->display();
    gb[4]->display();

    glFlush();
}

void init(char *namexml)
{
    arq.readXML(namexml);
    arena_config = arq.readSVG();

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    gb.push_back(new groundbase(arena_config->get_circle(1)));
    gb.push_back(new groundbase(arena_config->get_circle(2)));
    gb.push_back(new groundbase(arena_config->get_circle(3)));
    gb.push_back(new groundbase(arena_config->get_circle(4)));
    gb.push_back(new groundbase(arena_config->get_circle(5)));
}

int main(int argc, char **argv)
{

    /*OpenGl*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Trabalho Final");

    init(argv[1]);

    glutDisplayFunc(display);
    glutIdleFunc(idle);

    glutReshapeFunc(reshape);

    glutMainLoop();

    /*OpenGl*/

    return 0;
}