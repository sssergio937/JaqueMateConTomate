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
    // Fila 0: piezas rojas
    piezas[0][0] = new torre(Pieza::ROJO);    
    piezas[0][0]->setPosicion(0, 0);
    piezas[0][1] = new caballo(Pieza::ROJO); 
    piezas[0][1]->setPosicion(1, 0);
    piezas[0][2] = new rey(Pieza::ROJO);     
    piezas[0][2]->setPosicion(2, 0);
    piezas[0][3] = new reina(Pieza::ROJO);    
    piezas[0][3]->setPosicion(3, 0);
    piezas[0][4] = new alfil(Pieza::ROJO);   
    piezas[0][4]->setPosicion(4, 0);

    // Fila 1: peones rojos
    for (int j = 0; j < columnas; ++j) {
        piezas[1][j] = new peon(Pieza::ROJO);
        piezas[1][j]->setPosicion(j, 1);
    }

    // Fila 3: peones verdes
    for (int j = 0; j < columnas; ++j) {
        piezas[filas - 2][j] = new peon(Pieza::VERDE);
        piezas[filas - 2][j]->setPosicion(j, filas - 2);
    }

    // Fila 4: piezas verdes
    piezas[filas - 1][0] = new torre(Pieza::VERDE);   
    piezas[filas - 1][0]->setPosicion(0, filas - 1);
    piezas[filas - 1][1] = new caballo(Pieza::VERDE);  
    piezas[filas - 1][1]->setPosicion(1, filas - 1);
    piezas[filas - 1][2] = new rey(Pieza::VERDE);     
    piezas[filas - 1][2]->setPosicion(2, filas - 1);
    piezas[filas - 1][3] = new reina(Pieza::VERDE);   
    piezas[filas - 1][3]->setPosicion(3, filas - 1);
    piezas[filas - 1][4] = new alfil(Pieza::VERDE);    
    piezas[filas - 1][4]->setPosicion(4, filas - 1);
}




void Tablero::dibuja() {
    // Fondo gráfico
    glTranslated(0, 0, -0.2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/consola4.png").id);
    glDisable(GL_LIGHTING);

    glBegin(GL_POLYGON);
    glColor3f(0.9f, 1.0f, 1.0f);
    glTexCoord2d(0, 1); glVertex2f(-25.6f, -32.5f);
    glTexCoord2d(1, 1); glVertex2f(26.4f, -32.5f);
    glTexCoord2d(1, 0); glVertex2f(26.4f, 22.0f);
    glTexCoord2d(0, 0); glVertex2f(-25.6f, 22.0f);
    glEnd();

    glEnable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    // Casillas del tablero (z = 0.1)
    glTranslated(0, 0, 0.2);
    float despX = -(columnas * lado) / 2.0f;
    float despY = -(filas * lado) / 2.0f;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if ((i + j) % 2 == 0)
                glColor3ub(255, 255, 255); // blanco
            else
                glColor3ub(0, 0, 0);       // negro

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

    // Contorno del tablero (z = 0.2)
    glColor3ub(100, 100, 100);
    glBegin(GL_LINE_LOOP);
    glVertex3f(-columnas * lado / 2.0f, -filas * lado / 2.0f, 0.2f);
    glVertex3f(-columnas * lado / 2.0f, filas * lado / 2.0f, 0.2f);
    glVertex3f(columnas * lado / 2.0f, filas * lado / 2.0f, 0.2f);
    glVertex3f(columnas * lado / 2.0f, -filas * lado / 2.0f, 0.2f);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    // Dibujo de piezas
    
    
  

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (piezas[i][j]) {

                piezas[i][j]->dibuja();
            }
        }
    }

        
    
}
    


Pieza* Tablero::getPieza(int fila, int col) 
{
    if (fila >= 0 && fila < filas && col >= 0 && col < columnas)
        return piezas[fila][col];
    return nullptr;
}

int Tablero::getFilaDesdeY(float y) 
{
    return static_cast<int>((filas * lado / 2.0f - y) / lado);
}

int Tablero::getColDesdeX(float x) 
{
    return static_cast<int>((x + columnas * lado / 2.0f) / lado);
}
void Tablero::setPieza(int fila, int col, Pieza* pieza) 
{
    if (fila >= 0 && fila < filas && col >= 0 && col < columnas) {
        piezas[fila][col] = pieza;
        if (pieza) {
            pieza->setPosicion(col, fila);  
        }
    }
}
