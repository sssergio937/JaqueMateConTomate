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
    void inicializa_piezas(); // Nuevo método
    Pieza* getPieza(int fila, int col);
    int getFilaDesdeY(float y);
    int getColDesdeX(float x);
    void setPieza(int fila, int col, Pieza* pieza);
	
    ~Tablero(); // Para liberar memoria
};
