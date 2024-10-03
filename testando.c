#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#define pi 3.142857


// function to initialize
void myInit(void) {
    glClearColor(0, 0, 0, 1); // background colors

    // breadth of picture boundary is 1 pixel
    glPointSize(2.2);
    glLineWidth(2.2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // setting window dimension in X- and Y- direction
    gluOrtho2D(-780, 780, -420, 420);
}

void display_circle(float radius) {
    glBegin(GL_POINTS);
    for (float i = 0; i < 2 * pi; i += 0.001) {
        float x = radius * cos(i);
        float y = radius * sin(i);

        glVertex2i(x, y);
    }
    glEnd();
}

void display_line(float x1, float y1, float x2, float y2) {
    float X, Y, Xinc, Yinc;
    float length = abs(x2 - x1);

    if (abs(y2 - y1) > length) {
        length = abs(y2 - y1);
        Xinc = (x2 - x1) / length;
        Yinc = (y2 - y1) / length;
        X = x1;
        Y = y1;
    }
    glBegin(GL_POINTS);
    while (X < x2) {
        glVertex2d(X, Y);
        X = X + Xinc;
        Y = Y + Yinc;
    }
    glEnd();
}

void display_dagaz(float side) {
    float right = side / 2;
    float left = -right;
    float top = side / 2;
    float bottom = -top;

    glBegin(GL_LINE_LOOP);

    glVertex2f(left, top);
    glVertex2f(left, bottom);
    glVertex2f(right, top);
    glVertex2f(right, bottom);

    glEnd();
}

void display_square(float side) {
    float right = side / 2;
    float left = -right;
    float top = side / 2;
    float bottom = -top;

    glBegin(GL_LINE_LOOP);

    glVertex2f(left, top);
    glVertex2f(left, bottom);
    glVertex2f(right, bottom);
    glVertex2f(right, top);

    glEnd();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 9; i++) {
        glColor3f(0.3 - 0.04 * i, 0.7 - 0.05 * i, 1.0 - 0.05 * i);
        display_circle(250 + 2.2 * i);
    }

    for (int i = 0; i < 9; i++) {
        glColor3f(1.0 - 0.05 * i, 0.3 - 0.04 * i, 0.7 - 0.05 * i);
        display_square(280 + 2.2 * i);
    }

    glColor3f(1.0, 0.7, 0.3);
    display_dagaz(150);

    glFlush();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowSize(1366, 768);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("Testes");
    myInit();

    glutDisplayFunc(display);
    glutMainLoop();
}
