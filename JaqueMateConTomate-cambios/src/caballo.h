#pragma once
#include "pieza.h"

class Caballo : public Pieza
{
public:
    Caballo(COLOR c, TIPO t, const char* im_b, const char* im_n) : Pieza(c, t, im_b, im_n) {}
    virtual bool movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda);

};

