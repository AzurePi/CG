#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Variáveis para controle da iluminação e rotação da cena
GLfloat light_pos[] = {1.0, 1.0, 1.0, 0.0}; // Posição da luz
GLfloat light_ambient[] = {0.2, 0.2, 0.2, 1.0}; // Luz ambiente
GLfloat light_diffuse[] = {0.8, 0.8, 0.8, 1.0}; // Luz difusa
GLfloat light_specular[] = {1.0, 1.0, 1.0, 1.0}; // Luz especular

GLuint wood_texture; // Identificador da textura da maçã
GLuint metal_texture; // Identificador da textura de metal

// Função para carregar a textura
void loadTexture(const char *filename, GLuint *textureID) {
    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            printf("Formato de imagem não suportado: %d canais\n", nrChannels);
            stbi_image_free(data);
            return;
        }

        glGenTextures(1, textureID);
        glBindTexture(GL_TEXTURE_2D, *textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

        // Parâmetros da textura
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        printf("Textura carregada com sucesso: %s (%d x %d)\n", filename, width, height);
    }
    else { printf("Falha ao carregar a textura: %s\n", filename); }
    stbi_image_free(data); // Libera a memória
}

// Função para desenhar o caule da maçã
void drawStem() {
    glColor3f(0.4, 0.2, 0.0); // Cor do caule
    glPushMatrix();
    glTranslatef(0.0, 0.6, 0.0); // Posição do caule
    glRotatef(-90, 1.0, 0.0, 0.0); // Rotacionar para a orientação correta
    GLUquadric *quad = gluNewQuadric();
    gluCylinder(quad, 0.05, 0.05, 0.3, 30, 30); // Desenha um cilindro como caule
    gluDeleteQuadric(quad);
    glPopMatrix();
}


void drawSphere(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();

    if (texture == wood_texture)
        glTranslatef(0.5,0.5,0);
    else
        glTranslatef(-0.5,-0.5,0);

    // Desenha uma esfera usando uma malha
    glColor3f(1.0, 1.0, 1.0); // Define a cor como branca para usar a textura
    GLUquadric *quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE); // Habilitar textura na quadric
    gluSphere(quad, 0.35, 50, 50); // Desenha uma esfera com a textura especificada

    gluDeleteQuadric(quad);

    glPopMatrix();
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0, 1.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Posiciona a câmera

    glRotatef(30, 1.0, 0.0, 0.0); // Rotaciona a cena para visualizar melhor

    drawSphere(wood_texture); // Desenha uma esfera de madeira
    drawSphere(metal_texture); // Desenha uma esfera de madeira

    glutSwapBuffers();
}


// Função de inicialização
void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); // Fundo preto
    glEnable(GL_DEPTH_TEST); // Habilita o teste de profundidade

    // Configuração da iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    loadTexture("wood.png", &wood_texture); // Carregar textura de madeira
    loadTexture("metal.png", &metal_texture); // Carregar textura de metal
}

// Função de redimensionamento da janela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Função principal
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 800);
    glutCreateWindow("Esferas");

    init(); // Inicializar configurações

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
