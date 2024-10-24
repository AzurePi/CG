#ifndef CONE_H
#define CONE_H

#include <math.h>
#include <GL/glut.h>

#define PI 3.14159265
#define DEG2RAD (PI/180.0)

typedef struct {
    float x;
    float y;
    float z;
} Vector3f;

void DesenharCone(const Vector3f *d, const Vector3f *a, const float h, const float rd, const int n);

#endif //CONE_H
