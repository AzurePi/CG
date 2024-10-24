#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat AspectRatio;
int fazCalculoPonto;

GLfloat AnguloDeVisao;
GLfloat Obs[3];
GLfloat Alvo[3];

float rotacao_X = 0;
float rotacao_Y = 0;
float rotacao_Z = 0;


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
    glPushMatrix();

    glTranslatef(0.0f, 0.7f, 0.0f);

    glRotatef(rotacao_X, 1, 0, 0);
    glRotatef(rotacao_Y, 0, 1, 0);
    glRotatef(rotacao_Z, 0, 0, 1);

    glColor3f(0, 0.5, 1);
    glutSolidTeapot(1.2);

    glColor3f(0.7, 0.7, 0);
    glutWireTeapot(1.2);

    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 600, 500);

    PosicUser();
    DesenhaCenario();

    rotacao_X += 0.2;
    rotacao_Y += 0.3;
    rotacao_Z += 0.5;

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
    case GLUT_KEY_DOWN: glutInitWindowSize(600, 500);
        break;
    default: break;
    }
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(600, 500);
    glutCreateWindow("Projeto CG - Bule");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(arrow_keys);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
