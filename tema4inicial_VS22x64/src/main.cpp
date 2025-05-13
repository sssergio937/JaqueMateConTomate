

#include "freeglut.h"
#include "tablero.h"

Tablero tablero(5, 5, 2.0f); // Tablero de 5x5 con celdas de 2x2

void OnDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Cámara
    gluLookAt(5.0, 10.0, 20.0,  // posición de la cámara
        5.0, 0.0, 5.0,    // punto de interés (centro del tablero)
        0.0, 1.0, 0.0);   // vector "arriba"

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

void OnMouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        GLint viewport[4];
        GLdouble modelview[16], projection[16];
        GLfloat winX, winY, winZ;
        GLdouble posX, posY, posZ;

        glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
        glGetDoublev(GL_PROJECTION_MATRIX, projection);
        glGetIntegerv(GL_VIEWPORT, viewport);

        winX = (float)x;
        winY = (float)viewport[3] - (float)y;
        glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

        gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

        tablero.Click(posX, posZ);
        glutPostRedisplay();
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Tablero Ajedrez 5x5");

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0, 800.0 / 600.0, 1.0, 1000.0);

    glutDisplayFunc(OnDraw);
    glutKeyboardFunc(OnKeyboardDown);
    glutMouseFunc(OnMouse);
    glutTimerFunc(25, OnTimer, 0);

    glutMainLoop();
    return 0;
}
