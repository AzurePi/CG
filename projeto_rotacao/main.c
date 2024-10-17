#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "esfera.h"
#include "cubo.h"
#include "cone.h"


GLfloat AspectRatio;
int fazCalculoPonto;

GLfloat AnguloDeVisao;
GLfloat Obs[3];
GLfloat Alvo[3];

float esfera_rotacao_X = 0;
float esfera_rotacao_Y = 0;
float esfera_rotacao_Z = 0;

float cone_rotacao_X = 0;
float cone_rotacao_Y = 0;
float cone_rotacao_Z = 0;

float cubo_rotacao_X = 0;
float cubo_rotacao_Y = 0;
float cubo_rotacao_Z = 0;


// Inicializa os parâmetros globais de OpenGL e do cenário
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    Obs[0] = 0;
    Obs[1] = 3;
    Obs[2] = 3;
    Alvo[0] = 0;
    Alvo[1] = 0;
    Alvo[2] = -1;
    AnguloDeVisao = 70;
    fazCalculoPonto = 0;
}

// Faz o posicionamento do observador no cenário.
void PosicUser() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(AnguloDeVisao, AspectRatio, 0.01, 200);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(Obs[0], Obs[1], Obs[2], Alvo[0], Alvo[1], Alvo[2], 0.0f, 1.0f, 0.0f);
}


// trata o redimensionamento da janela OpenGL
void reshape(int w, int h) {
    if (h == 0)
        h = 1;

    AspectRatio = 1.0f * w / h;
    PosicUser();
}


void DesenhaCenario() {
    // Esfera
    glPushMatrix();
    glTranslatef(-3.0f, 0.0f, -1.0f);
    DesenharEsfera(0);
    glPopMatrix();

    // Cubo
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(cubo_rotacao_X, 1, 0, 0);
    glRotatef(cubo_rotacao_Y, 0, 1, 0);
    glRotatef(cubo_rotacao_Z, 0, 0, 1);
    DesenharCubo();
    glPopMatrix();

    // Cone
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, -1.0f);
    glRotatef(cone_rotacao_X, 1, 0, 0);
    glRotatef(cone_rotacao_Y, 0, 1, 0);
    glRotatef(cone_rotacao_Z, 0, 0, 1);

    Vector3f direcao = {0.0f, 1.0f, 0.0f}; // direção apontando para cima no eixo Y
    Vector3f vertice = {0.0f, 1.0f, 0.0f}; // vértice do cone na origem (após translação)
    float altura = 1.5f;
    float raioBase = 0.7f;
    int segmentos = 1500;

    DesenharCone(&direcao, &vertice, altura, raioBase, segmentos);

    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 255, 255);

    PosicUser();
    DesenhaCenario();

    cone_rotacao_X += 0.4;
    cone_rotacao_Y += 0.2;
    cone_rotacao_Z += 0.4;

    cubo_rotacao_X += 0.1;
    cubo_rotacao_Y += 0.2;
    cubo_rotacao_Z += 0.5;

    glutSwapBuffers();
}

void keyboard(unsigned char key) {
    switch (key) {
    case 27: exit(0);
    case ' ': fazCalculoPonto = 1;
        break;
    default: break;
    }
}

void arrow_keys(int a_keys) {
    switch (a_keys) {
    case GLUT_KEY_UP: glutFullScreen();
        break;
    case GLUT_KEY_DOWN: glutInitWindowSize(700, 500);
        break;
    default: break;
    }
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(700, 500);
    glutCreateWindow("Projeto CG - Composição");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
