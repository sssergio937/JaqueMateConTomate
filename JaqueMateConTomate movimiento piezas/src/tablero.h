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
    Pieza* getPieza(const Casilla& c) const;

    ~Tablero(); // Para liberar memoria
};
