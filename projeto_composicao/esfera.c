#include "esfera.h"

void DesenharEsfera(void) {
    glColor3f(0.4, 1, 0.2); // Define a cor como branca para usar a textura
    glLineWidth(1);
    glutSolidSphere(0.35, 50, 50); // Desenha uma esfera com a textura especificada
}
