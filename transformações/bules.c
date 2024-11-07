#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <unistd.h>

#include <GL/glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

GLuint textureID;
GLfloat AspectRatio;

// Função para carregar a textura
void CarregarTextura() {
    int largura, altura, canais;
    unsigned char *data = stbi_load("textura.jpg", &largura, &altura, &canais, 0);
    if (data == NULL) {
               printf("Erro ao carregar a imagem!\n");
        exit(1);
    }

    // Gera um ID de textura e configura os parâmetros
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data); // Libera a memória da imagem
}

// Inicializa os parâmetros globais de OpenGL e do cenário
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    CarregarTextura();
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
    if (h == 0)
        h = 1;
    AspectRatio = 1.0f * w / h;
    glViewport(0, 0, w, h);
    PosicUser();
}


void DesenhaCenario() {
    glBindTexture(GL_TEXTURE_2D, textureID);
    float size = 0.6;

    // Primeiro bule
    glPushMatrix();
    glTranslatef(-2.6f, 0.0f, 0.0f);
    glRotatef(0, 1, 0, 0);
    glRotatef(0, 0, 1, 0);
    glRotatef(0, 0, 0, 1);

    glutSolidTeapot(size);

    glPopMatrix();

    // Segundo bule
    glPushMatrix();
    glTranslatef(-0.85f, 0.0f, 0.0f);
    glRotatef(0, 1, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(0, 0, 0, 1);

    glutSolidTeapot(size);

    glPopMatrix();

    // Terceiro bule
    glPushMatrix();
    glTranslatef(0.6f, 0.0f, 0.0f);
    glRotatef(0, 1, 0, 0);
    glRotatef(00, 0, 1, 0);
    glRotatef(90, 0, 0, 1);

    glutSolidTeapot(size);

    glPopMatrix();

    // Quarto bule
    glPushMatrix();
    glTranslatef(2.4f, 0.0f, 0.0f);
    glRotatef(90, 1, 0, 0);
    glRotatef(0, 0, 1, 0);
    glRotatef(0, 0, 0, 1);

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
    if (key == 27)
        exit(0);
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(900, 500);
    glutCreateWindow("Projeto CG - Bules");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
