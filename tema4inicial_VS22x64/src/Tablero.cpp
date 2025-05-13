
#include "tablero.h"
#include "freeglut.h"

Tablero::Tablero(int f, int c, float l)
    : filas(f), columnas(c), lado(l) {
    colores.resize(filas, std::vector<int>(columnas));
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            colores[i][j] = (i + j) % 2;  // Alternar entre blanco (0) y negro (1)
        }
    }
}

void Tablero::Dibuja() const {
    glDisable(GL_LIGHTING);

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (colores[i][j] == 0)
                glColor3ub(255, 255, 255); // Blanco
            else if (colores[i][j] == 1)
                glColor3ub(0, 0, 0);       // Negro
            else
                glColor3ub(0, 255, 0);     // Verde

            float x = j * lado;
            float z = i * lado;

            glBegin(GL_QUADS);
            glVertex3f(x, 0, z);
            glVertex3f(x, 0, z + lado);
            glVertex3f(x + lado, 0, z + lado);
            glVertex3f(x + lado, 0, z);
            glEnd();
        }
    }

    // Dibujar contorno del tablero en gris
    glColor3ub(100, 100, 100);
    glBegin(GL_LINE_LOOP);
    glVertex3f(0.0f, 0.01f, 0.0f); // esquina inferior izquierda
    glVertex3f(0.0f, 0.01f, filas * lado); // esquina superior izquierda
    glVertex3f(columnas * lado, 0.01f, filas * lado); // esquina superior derecha
    glVertex3f(columnas * lado, 0.01f, 0.0f); // esquina inferior derecha
    glEnd();

    glEnable(GL_LIGHTING);
}

void Tablero::Click(float x, float z) {
    int j = x / lado;
    int i = z / lado;

    if (i >= 0 && i < filas && j >= 0 && j < columnas) {
        if (colores[i][j] == 0) // Solo cambiar si era blanco
            colores[i][j] = 2;  // Cambiar a verde
    }
}
