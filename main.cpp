#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string>

#include "xml.h"
#include "groundbase.h"
#include "arena.h"
#include "raster.h"

/*Window*/
int width = 500;
int height = 700;
/*Window*/

/*xml*/
xml arq;
config *arena_config;
/*xml*/

/*Arena*/
arena *game;
/*Arena*/

/*Keys*/
bool key_status[256] = {false};
bool mouse_status[2] = {false};
/*Keys*/

/*Time Control*/
int previous_time;
int now;
/*Time Control*/

/*Testes*/

/*Testes*/

void keyPress(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ('r' | 'R'):
        key_status[(int)('r')] = true;
        break;

    case ('a' | 'A'):
        key_status[(int)('a')] = true;
        break;
    case ('d' | 'D'):
        key_status[(int)('d')] = true;
        break;

    case ('w' | 'W'):
        key_status[(int)('w')] = true;
        break;

    case ('s' | 's'):
        key_status[(int)('s')] = true;
        break;

    case ('u' | 'U'):
        key_status[(int)('u')] = true;
        break;

    case ('+'):
        key_status[(int)('+')] = true;
        break;

    case ('-'):
        key_status[(int)('-')] = true;
        break;

    case 27:     // Termina o programa qdo
        exit(0); // a tecla ESC for pressionada
        break;
    default:
        break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case ('r' | 'R'):
        key_status[(int)('r')] = false;
        break;

    case ('a' | 'A'):
        key_status[(int)('a')] = false;
        break;

    case ('d' | 'D'):
        key_status[(int)('d')] = false;
        break;

    case ('w' | 'W'):
        key_status[(int)('w')] = false;
        break;

    case ('s' | 's'):
        key_status[(int)('s')] = false;
        break;

    case ('+'):
        key_status[(int)('+')] = false;
        break;

    case ('-'):
        key_status[(int)('-')] = false;
        break;

    default:
        break;
    }
}

void idle()
{
    glutPostRedisplay();
}

void reshape(int w, int h)
{
    double view_h;

    view_h = 200.0 / 700.0 * h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, view_h, (GLsizei)w, (GLsizei)h);
    gluPerspective(45, (GLfloat)w / (GLfloat)h, 1, 5000);
    glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*time control*/
    now = glutGet(GLUT_ELAPSED_TIME);
    int elapsed = now - previous_time;
    previous_time = now;
    /*time control*/

    double view_h, w, h;

    h = glutGet(GLUT_WINDOW_HEIGHT);
    w = glutGet(GLUT_WINDOW_WIDTH);

    view_h = 200.0 / 700.0 * h;

    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, view_h, (GLsizei)w, (GLsizei)h);
        gluPerspective(45, (GLfloat)w / (GLfloat)h, 1, 5000);
    glMatrixMode(GL_MODELVIEW);

    game->display(key_status, mouse_status, elapsed);

    glPushMatrix();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glViewport(0, 0, (GLsizei)w, view_h - 10);
        gluPerspective(45, (GLfloat)w / (GLfloat)h, 1, 5000);
        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    game->display_bomb();

    glFlush();
}

void init(char *namexml)
{
    arq.readXML(namexml);
    arena_config = arq.readSVG();
    game = new arena(arena_config);

    glClearColor(0.0, 0.1, 0.2, 0.0);
    glShadeModel(GL_SMOOTH);

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    float l_p[4] = {500, 500, 50, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, l_p);
}
void mouse(int button, int state, int x, int y)
{

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse_status[0] = true;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        mouse_status[1] = true;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        mouse_status[0] = false;
    }

    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        mouse_status[1] = false;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Trabalho Final");

    /*Init*/
    init(argv[1]);
    /*Init*/

    /*CallBack*/
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyPress);
    glutKeyboardUpFunc(keyUp);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    /*CallBack*/

    glutMainLoop();
    return 0;
}