#include <iostream>
#include "freeglut.h"
#include "ETSIDI.h"
#include "tablero.h"
#include "peon.h"
#include "torre.h"
#include "caballo.h"
#include "alfil.h"
#include "reina.h"
#include "rey.h"




// constructor 
Tablero::Tablero(int f, int c, float l) : filas(f), columnas(c), lado(l) {
    piezas.resize(filas, std::vector<Pieza*>(columnas, nullptr));
    inicializa_piezas();
}
Tablero::~Tablero() {
    for (auto& fila : piezas)
        for (auto& p : fila)
            delete p;
}

void Tablero::inicializa_piezas() {
    // Ejemplo para tablero 5x5 (ajedrez baby)
    // Fila 0: piezas rojas
    piezas[0][0] = new torre(Pieza::ROJO);
    piezas[0][1] = new caballo(Pieza::ROJO);
    piezas[0][2] = new rey(Pieza::ROJO);
    piezas[0][3] = new reina(Pieza::ROJO);
    piezas[0][4] = new alfil(Pieza::ROJO);

    // Fila 1: peones rojos
    for (int j = 0; j < columnas; ++j)
        piezas[1][j] = new peon(Pieza::ROJO);

    // Fila 3: peones verdes
    for (int j = 0; j < columnas; ++j)
        piezas[filas - 2][j] = new peon(Pieza::VERDE);

    // Fila 4: piezas verdes
    piezas[filas - 1][0] = new torre(Pieza::VERDE);
    piezas[filas - 1][1] = new caballo(Pieza::VERDE);
    piezas[filas - 1][2] = new rey(Pieza::VERDE);
    piezas[filas - 1][3] = new reina(Pieza::VERDE);
    piezas[filas - 1][4] = new alfil(Pieza::VERDE);
}




void Tablero::dibuja()	

{
    glTranslated(0, 0, -0.2);
    //imagen del fondo, que se situa en la altura z = 0
    glEnable(GL_TEXTURE_2D);
   glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/consola4.png").id);
    glDisable(GL_LIGHTING);
    glBegin(GL_POLYGON);
    glColor3f(0.9, 1, 1);
    glTexCoord2d(0, 1); glVertex2f(-25.6, -32.5);         // todo esto es el ajuste de la imagen del fondo 
    glTexCoord2d(1, 1); glVertex2f(26.4, -32.5);
    glTexCoord2d(1, 0); glVertex2f(26.4, 22);
    glTexCoord2d(0, 0); glVertex2f(-25.6, 22);
    glEnd();
    
    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);
    glTranslated(0, 0, 0.2);

    // dibujo de las casillas, en la altura z = 0.1
    float despX = -(columnas * lado) / 2.0f;          // desplazamiento X para centrarlo
    float despY = -(filas * lado) / 2.0f;             // desplazamiento Y para centrarlo
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Alternar colores
            if ((i + j) % 2 == 0)
                glColor3ub(255, 255, 255);  // Blanco
            else
                glColor3ub(0, 0, 0);        // Negro

            float x = j * lado + despX;
            float y = i * lado + despY;
            glBegin(GL_QUADS);
            glVertex3f(x, y, -0.1f);
            glVertex3f(x, y + lado, -0.1f);
            glVertex3f(x + lado, y + lado, -0.1f);
            glVertex3f(x + lado, y, -0.1f);
            glEnd();
        }
    }

    
    // dibujo del contorno del tablero, en la altura z =  0.2
    glColor3ub(100, 100, 100);
    glBegin(GL_LINE_LOOP);                                   // un poco por encima de las casillas y de color gris
    glVertex3f(-columnas * lado / 2.0f, -filas * lado / 2.0f, 0.2f);  // esquina inferior izquierda
    glVertex3f(-columnas * lado / 2.0f, filas * lado / 2.0f, 0.2f);   // esquina superior izquierda
    glVertex3f(columnas * lado / 2.0f, filas * lado / 2.0f, 0.2f);    // esquina superior derecha
    glVertex3f(columnas * lado / 2.0f, -filas * lado / 2.0f, 0.2f);   // esquina inferior derecha
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);



    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (piezas[i][j]) {
                float despX = -(columnas * lado) / 2.0f;
                float despY = -(filas * lado) / 2.0f;

                piezas[i][j]->posicion = Vector2D{j * lado + despX + lado/2, i * lado + despY + lado/2}; // se añade el lado/2 para que las piezas se impriman en el mediod e las casillas
                piezas[i][j]->dibuja();
            }
        }
    }
    

}

