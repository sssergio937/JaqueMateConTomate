

#include "freeglut.h"
#include "tablero.h"

Tablero tablero(5, 5, 2.0f);  // Tablero de 5x5 con celdas de 2x2

void OnDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 10.0, 20.0,   // posición de la cámara
        5.0, 0.0, 5.0,     // hacia dónde mira
        0.0, 1.0, 0.0);    // "arriba" es Y

    tablero.Dibuja();

    glutSwapBuffers();
}

void OnKeyboardDown(unsigned char key, int x, int y) {
    if (key == 27) exit(0); // Salir con ESC
}

void OnTimer(int value) {
    glutTimerFunc(25, OnTimer, 0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tablero Ajedrez 5x5");

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.0, 800 / 600.0f, 1.0, 100.0);

    glutDisplayFunc(OnDraw);
    glutTimerFunc(25, OnTimer, 0);
    glutKeyboardFunc(OnKeyboardDown);

    glutMainLoop();
    return 0;
}