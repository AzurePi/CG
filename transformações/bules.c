#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLfloat AspectRatio;


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
    gluPerspective(45, AspectRatio, 1, 1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
}


// trata o redimensionamento da janela OpenGL
void reshape(int w, int h) {
    if (h == 0) h = 1;
    AspectRatio = 1.0f * w / h;
    glViewport(0, 0, w, h);
    PosicUser();
}


void DesenhaCenario() {
    float size = 0.6;

    // Primeiro bule
    glPushMatrix();
    glTranslatef(-2.6f, 0.0f, 0.0f);
    glRotatef(0, 1, 0, 0);
    glRotatef(0, 0, 1, 0);
    glRotatef(0, 0, 0, 1);

    glColor3f(0, 0.5, 1);
    glutWireTeapot(size);
    glColor3f(1, 0.5, 0);
    glutSolidTeapot(size);

    glPopMatrix();

    // Segundo bule
    glPushMatrix();
    glTranslatef(-0.85f, 0.0f, 0.0f);
    glRotatef(0, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(0, 0, 0, 1);

    glColor3f(0, 0.5, 1);
    glutWireTeapot(size);
    glColor3f(1, 0.5, 0);
    glutSolidTeapot(size);

    glPopMatrix();

    // Terceiro bule
    glPushMatrix();
    glTranslatef(0.6f, 0.0f, 0.0f);
    glRotatef(0, 1, 0, 0);
    glRotatef(00, 0, 1, 0);
    glRotatef(90, 0, 0, 1);

    glColor3f(0, 0.5, 1);
    glutWireTeapot(size);
    glColor3f(1, 0.5, 0);
    glutSolidTeapot(size);

    glPopMatrix();

    // Quarto bule
    glPushMatrix();
    glTranslatef(2.4f, 0.0f, 0.0f);
    glRotatef(90, 1, 0, 0);
    glRotatef(0, 0, 1, 0);
    glRotatef(0, 0, 0, 1);

    glColor3f(0, 0.5, 1);
    glutWireTeapot(size);
    glColor3f(1, 0.5, 0);
    glutSolidTeapot(size);

    glPopMatrix();
}


void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    PosicUser();
    DesenhaCenario();
    glutSwapBuffers();
}

void keyboard(unsigned char key) {
    if (key == 27) exit(0);
}

void arrow_keys(int a_keys) {
    if (a_keys == GLUT_KEY_UP) glutFullScreen();
    if (a_keys == GLUT_KEY_DOWN) glutReshapeWindow(600, 500);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(900, 500);
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
