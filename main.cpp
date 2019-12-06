#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <iostream>
#include <string>

#include "xml.h"
#include "groundbase.h"
#include "arena.h"

/*Window*/
int width = 500;
int height = 500;
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
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
        gluPerspective(45, (GLfloat)h / (GLfloat)w, 1, 5000);
    else
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

    game->display(key_status, elapsed);

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

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, GLdouble(width / height), 1, 5000);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);

    float l_p[4] = {500, 500, 50, 1};
    glLightfv(GL_LIGHT1, GL_POSITION, l_p);


}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(20000, 100);
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
    /*CallBack*/

    glutMainLoop();
    return 0;
}