#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

#include "esfera.h"
#include "cubo.h"
#include "cone.h"


#ifdef WIN32
#include <windows.h>
#endif

GLfloat AspectRatio;
GLfloat AngY;
int fazCalculoPonto;

GLfloat AnguloDeVisao;
GLfloat Obs[3];
GLfloat Alvo[3];

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
    AngY = 0;
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

    glViewport(0, 0, w, h);
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
    DesenharCubo();
    glPopMatrix();

    // Cone
    glPushMatrix();
    glTranslatef(3.0f, 0.0f, -1.0f);

    // Definir os parâmetros do cone
    Vector3f direcao = {0.0f, 1.0f, 0.0f};  // Vetor direção apontando para cima no eixo Y
    Vector3f vertice = {0.0f, 0.0f, 0.0f};  // O vértice do cone na origem
    float altura = 2.0f;                    // Altura do cone (2 unidades)
    float raioBase = 1.0f;                  // Raio da base do cone (1 unidade)
    int segmentos = 36;                     // 36 segmentos para uma base circular suave

    // Chamar a função para desenhar o cone
    DesenharCone(&direcao, &vertice, altura, raioBase, segmentos);

    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PosicUser();
    DesenhaCenario(1);

    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 27: exit(0);
        break;
    case ' ': fazCalculoPonto = 1;
        break;
    case 'a':
    case 'A': AngY += 5;
        break;
    default: break;
    }
}

void arrow_keys(int a_keys, int x, int y) {
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
    glutCreateWindow("Computação Gráfica - Transformações Hierárquicas 3D");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
