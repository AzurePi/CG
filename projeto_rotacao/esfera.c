#include "esfera.h"

void DesenharEsfera(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();

    // Desenha uma esfera usando uma malha
    glColor3f(0.4, 1, 0.2); // Define a cor como branca para usar a textura
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE); // Habilitar textura na quadric
    gluSphere(quad, 0.35, 50, 50); // Desenha uma esfera com a textura especificada

    gluDeleteQuadric(quad);

    glPopMatrix();
}
