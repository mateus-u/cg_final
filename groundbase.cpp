#include "groundbase.h"

#include <iostream>
using namespace std;

groundbase::groundbase(circle *cir)
{
    this->circ = cir;
}

groundbase::~groundbase()
{
}

void groundbase::display()
{


    glPushMatrix();
        GLfloat materialEmission[] = {0.4, 0.5, 0.6, 1};
        GLfloat materialColor[] = {0.5, 0.5, 0.5, 1};
        GLfloat mat_specular[] = {0.5, 0.5, 0.5, 1};
        GLfloat mat_shininess[] = {5.0};
        glMaterialfv(GL_FRONT, GL_EMISSION, materialEmission);
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
        
        glTranslated(this->circ->get_centerx(), this->circ->get_centery(), 0);
        glutSolidSphere(this->circ->get_radius(), 360, 360);
    glPopMatrix();

}
