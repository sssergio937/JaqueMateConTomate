#pragma once
#include "freeglut.h"
#include "ETSIDI .h"
#include <vector> 

//CLASE PARA CREACIÓN Y MODIFICACIONES DEL TABLERO 5X5
class Tablero {
private:
    int filas, columnas;
    float lado;
    std::vector<std::vector<int>> colores; // 0 = blanco, 1 = negro, 2 = verde

public:
    Tablero(int f, int c, float l);
    void Dibuja() const;
    void Click(float x, float z);
};