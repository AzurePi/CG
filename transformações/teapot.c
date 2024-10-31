#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat AspectRatio;
GLfloat fazCalculoPonto;


// Inicializa os parâmetros globais de OpenGL e do cenário
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

// Faz o posicionamento do observador no cenário.
void PosicUser() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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

    glColor3f(0, 0.5, 1);
    glutSolidTeapot(0.3);

    glColor3f(0, 0.5, 1);
    glTranslatef(3, 0, 0);
    glutSolidTeapot(0.3);

    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, 600, 500);

    PosicUser();
    DesenhaCenario();

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
