#include "cubo.h"

void DesenharCubo() {
    glColor3f(1, 0, 1);
    glLineWidth(1);
    glutSolidCube(1);

    glLineWidth(1);
    glColor3f(1, 1, 0);
    glutWireCube(1);
}
