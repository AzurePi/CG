#include "esfera.h"

void DesenharEsfera(void) {
    glColor3f(0.4, 1, 0.2);
    glLineWidth(1);
    glutSolidSphere(0.7, 50, 50);

    glColor3f(1, 0.2, 0.4);
    glLineWidth(2);
    glutWireSphere(0.7, 15, 15);
}
