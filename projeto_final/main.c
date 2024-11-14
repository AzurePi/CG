#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <GL/glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb_image.h"

GLuint maca_textureID, bola_textureID;
GLfloat AspectRatio;

// Função para carregar a textura
void CarregarTexturas() {
    int largura, altura, canais;

    // Carregar a textura da maçã
    unsigned char *data = stbi_load("maca.jpg", &largura, &altura, &canais, 0);
    if (data == NULL) {
        printf("Erro ao carregar a imagem da maçã!\n");
        exit(1);
    }

    // Gera um ID de textura para a maçã e configura os parâmetros
    glGenTextures(1, &maca_textureID);
    glBindTexture(GL_TEXTURE_2D, maca_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data); // Libera a memória da imagem da maçã

    // Carregar a textura da bola
    data = stbi_load("bola.jpg", &largura, &altura, &canais, 0);
    if (data == NULL) {
        printf("Erro ao carregar a imagem da bola!\n");
        exit(1);
    }

    // Gera um ID de textura para a bola e configura os parâmetros
    glGenTextures(1, &bola_textureID);
    glBindTexture(GL_TEXTURE_2D, bola_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    stbi_image_free(data); // Libera a memória da imagem da bola
}

// Inicializa os parâmetros globais de OpenGL e do cenário
void init(void) {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fundo de tela preto
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    CarregarTexturas();
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
    // esfera de cor sólida
    glPushMatrix();

    glColor3f(0.75f, 0.35f, 0.30f);
    glTranslatef(-2.6f, 1.5f, 0.0f);
    glutSolidSphere(0.4f, 40, 30);

    glPopMatrix();

    // esfera em wireframe
    glPushMatrix();

    glColor3f(0.70f, 0.25f, 0.80f);
    glTranslatef(-1.0f, 0.75f, 0.0f);
    glRotatef(45, 0, 1, 0);
    glRotatef(35, 1, 0, 0);
    glutWireSphere(0.5f, 15, 15);

    glPopMatrix();

    // bola
    glBindTexture(GL_TEXTURE_2D, bola_textureID);

    glPushMatrix();

    glColor3f(1.0f, 1.0f, 0.97f);
    glTranslatef(0.6f, 0.0f, 0.0f);
    glRotatef(40, 0, 1, 0);
    glRotatef(40, 1, 0, 0);
    GLUquadric *quadric1 = gluNewQuadric();
    gluQuadricTexture(quadric1, GL_TRUE); // Habilita textura na esfera
    gluSphere(quadric1, 0.6, 32, 32); // Desenha a esfera com a textura da bola
    gluDeleteQuadric(quadric1);

    glPopMatrix();

    // maçã
    glBindTexture(GL_TEXTURE_2D, maca_textureID);

    glPushMatrix();

    glColor3f(0.80f, 0.4f, 0.75f);
    glTranslatef(2.4f, -1.0f, 0.0f);
    glRotatef(45, 0, 1, 0);
    GLUquadric *quadric2 = gluNewQuadric();
    gluQuadricTexture(quadric2, GL_TRUE); // Habilita textura na esfera
    gluSphere(quadric2, 0.7, 32, 32); // Desenha a esfera com a textura da maçã
    gluDeleteQuadric(quadric2);

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

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(900, 500);
    glutCreateWindow("Projeto Final CG");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(display);

    glutMainLoop();
    return 0;
}
