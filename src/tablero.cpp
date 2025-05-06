#include "tablero.h"
#include "freeglut.h"

// constructor
Tablero::Tablero(int f, int c, float l) : filas(f), columnas(c), lado(l) {}

void Tablero::dibuja()
{
    glDisable(GL_LIGHTING);

    // dibujo de las casillas 
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Alternar colores mientras dibujamos las casillas
            if ((i + j) % 2 == 0)
                glColor3ub(255, 255, 255);  // Blanco
            else
                glColor3ub(0, 0, 0);        // Negro

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

    // dibujo del contorno del tablero en gris
    glColor3ub(100, 100, 100);
    glBegin(GL_LINE_LOOP);                              // se dibuja ligeramente por encima de las casillas
    glVertex3f(0.0f, 0.01f, 0.0f);                      // esquina inferior izquierda
    glVertex3f(0.0f, 0.01f, filas * lado);              // esquina superior izquierda
    glVertex3f(columnas * lado, 0.01f, filas * lado);   // esquina superior derecha
    glVertex3f(columnas * lado, 0.01f, 0.0f);           // esquina inferior derecha
    glEnd();

    glEnable(GL_LIGHTING);
}