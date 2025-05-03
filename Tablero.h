#pragma once
#include "freeglut.h"
#include"ETSIDI .h"


//CLASE PARA CREACIÓN Y MODIFICACIONES DEL TABLERO 5X5

class Tablero 
{
private:
    int filas, columnas;
    float lado;

public:
    Tablero(int f, int c, float l);
    void Dibuja() const;
};
