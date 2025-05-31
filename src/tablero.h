#pragma once
#include <vector>
#include "pieza.h"

using namespace std;

class Tablero
{
private:
    int filas, columnas;
    float lado;
	
    vector<vector<Pieza*>> piezas;

public:
    Tablero(int f, int c, float l);
    void dibuja();
    void inicializa_piezas(bool variante); // Nuevo método
    Pieza* getPieza(int fila, int col) const;
    int getFilaDesdeY(float y);
    int getColDesdeX(float x);
    void setPieza(int fila, int col, Pieza* pieza);
    bool reyEnJaque(Pieza::COLOR colorRey);
    bool esJaqueMate(Pieza::COLOR colorRey);
    Casilla buscarRey(Pieza::COLOR colorRey);
	
    ~Tablero(); // Para liberar memoria
};
