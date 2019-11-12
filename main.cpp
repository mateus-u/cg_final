#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "xml.h"
#include "arena.h"

Arena* arena;

const GLint Width = 700;
const GLint Height = 700;


const GLint ViewingWidth = 500;
const GLint ViewingHeight = 500;
 

void renderScene(void)
{
     // Clear the screen.
     glClear(GL_COLOR_BUFFER_BIT);
 
     arena->display();

     glutSwapBuffers(); // Desenha the new frame of the game.
}

void init(void)
{

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black, no opacity(alpha).
 
    glMatrixMode(GL_PROJECTION); // Select the projection matrix    
    glOrtho(-(0),     // X coordinate of left edge             
            1000,     // X coordinate of right edge            
            1000,     // Y coordinate of bottom edge             
            0,     // Y coordinate of top edge             
            -100,     // Z coordinate of the “near” plane            
            100);    // Z coordinate of the “far” plane
    glMatrixMode(GL_MODELVIEW); // Select the projection matrix    
    glLoadIdentity();
      
}

void idle(void)
{
   
    glutPostRedisplay();
}
 
int main(int argc, char *argv[])
{

    xml arq;
    arq.readXML(argv[1]);
    arena = arq.readSVG();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 
    // Create the window.
    glutInitWindowSize(Width, Height);
    glutInitWindowPosition(150,50);
    glutCreateWindow("Trabalho Final");
 
    init();

    // Define callbacks.
    glutDisplayFunc(renderScene);
    glutIdleFunc(idle);
     
    glutMainLoop();
 
    return 0;
}
