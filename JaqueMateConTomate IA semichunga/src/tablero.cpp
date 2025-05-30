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
#include <cstring>
#include "casillas.h"



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
	// Elimina las piezas existentes para evitar fugas de memoria
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (piezas[i][j]) {
                delete piezas[i][j];
                piezas[i][j] = nullptr;
            }
        }
    }
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
    


Pieza* Tablero::getPieza(int fila, int col) const
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

// Busca la posición del rey de un color dado
Casilla Tablero::buscarRey(Pieza::COLOR colorRey) {
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            Pieza* p = piezas[f][c];
            if (p && p->getColor() == colorRey && p->getPieza() == Pieza::REY) {
                return Casilla(f, c);
            }
        }
    }
    // Devuelve una casilla inválida si no se encuentra (manejar según tu lógica)
    return Casilla(-1, -1);
}

// Devuelve true si el rey de colorRey está en jaque
bool Tablero::reyEnJaque(Pieza::COLOR colorRey) {
    Casilla posRey = buscarRey(colorRey);
    if (posRey.fila == -1) return false; // No hay rey, error de lógica

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            Pieza* p = piezas[f][c];
            if (p && p->getColor() != colorRey) {
                if (p->movimiento_valido(Casilla(f, c), posRey, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Jaque mate: no hay ningún movimiento legal que saque al rey del jaque
bool Tablero::esJaqueMate(Pieza::COLOR colorRey) {
    if (!reyEnJaque(colorRey)) return false;

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            Pieza* p = piezas[f][c];
            if (p && p->getColor() == colorRey) {
                for (int nf = 0; nf < filas; ++nf) {
                    for (int nc = 0; nc < columnas; ++nc) {
                        Casilla origen(f, c);
                        Casilla destino(nf, nc);
                        if (p->movimiento_valido(origen, destino, *this)) {
                            // Simula el movimiento
                            Pieza* temp = piezas[nf][nc];
                            piezas[nf][nc] = p;
                            piezas[f][c] = nullptr;
                            bool sigueEnJaque = reyEnJaque(colorRey);
                            // Deshace el movimiento
                            piezas[f][c] = p;
                            piezas[nf][nc] = temp;
                            if (!sigueEnJaque) return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}