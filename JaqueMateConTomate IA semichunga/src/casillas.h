#pragma once
#include"pieza.h"

class Tablero;

class Casilla {
public:
    int fila = 0;
    int columna = 0;

    Casilla() {}
    Casilla(int f, int c) : fila(f), columna(c) {}

};

