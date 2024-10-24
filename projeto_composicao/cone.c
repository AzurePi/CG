#include "cone.h"

Vector3f CrossProduct(const Vector3f *v1, const Vector3f *v2) {
    Vector3f result;
    result.x = v1->y * v2->z - v1->z * v2->y;
    result.y = v1->z * v2->x - v1->x * v2->z;
    result.z = v1->x * v2->y - v1->y * v2->x;
    return result;
}

// Função que retorna um vetor perpendicular a um vetor dado
Vector3f perp(const Vector3f *v) {
    float min = fabsf(v->x);
    Vector3f cardinalAxis = {1, 0, 0};

    if (fabsf(v->y) < min) {
        min = fabsf(v->y);
        cardinalAxis = (Vector3f){0, 1, 0};
    }

    if (fabsf(v->z) < min) { cardinalAxis = (Vector3f){0, 0, 1}; }

    return CrossProduct(v, &cardinalAxis);
}


// Desenha um cone para uma direção/diretriz d a partir de um vértice de topo a, com altura h, raio de base rd, e uma base desenhada com n segmentos.
void DesenharCone(const Vector3f *d, const Vector3f *a, const float h, const float rd, const int n) {
    Vector3f c; // centro da base do cone
    Vector3f e0, e1; // vetores perpendiculars que auxiliam na construção
    float angInc; // incremento angular do desenho da base
    Vector3f pts[n]; // vetor dos pontos da base

    // cálculo da base do cone
    c.x = a->x + (-d->x * h);
    c.y = a->y + (-d->y * h);
    c.z = a->z + (-d->z * h);

    e0 = perp(d); // vetor perpendicular a d, utilizado para definir a direção principal ao longo do círculo da base
    e1 = CrossProduct(&e0, d);
    // calcula o produto vetorial entre e0 e d, resultando em outro vetor perpendicular, necessário para definir a geometria circular da base do cone

    angInc = 360.0 / n * DEG2RAD; // Incremento angular em radianos

    // calcular pontos ao redor da diretriz d
    for (int i = 0; i < n; ++i) {
        float rad = angInc * i;
        pts[i].x = c.x + (((e0.x * cos(rad)) + (e1.x * sin(rad))) * rd);
        pts[i].y = c.y + (((e0.y * cos(rad)) + (e1.y * sin(rad))) * rd);
        pts[i].z = c.z + (((e0.z * cos(rad)) + (e1.z * sin(rad))) * rd);
    }

    glColor3f(0, 0.4, 0.8);

    // Desenhar o topo do cone (um triãngulo rodando)
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(a->x, a->y, a->z);
    for (int i = 0; i < n; ++i)
        glVertex3f(pts[i].x, pts[i].y, pts[i].z);
    glEnd();

    // Desenhar a base do cone
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(c.x, c.y, c.z);
    for (int i = n - 1; i >= 0; --i) { glVertex3f(pts[i].x, pts[i].y, pts[i].z); }
    glEnd();
}
