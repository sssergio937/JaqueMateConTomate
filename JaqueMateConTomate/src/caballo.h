#pragma once
#include "pieza.h"
class caballo : public Pieza
{
public:
	caballo(COLOR color) : Pieza(color, TIPO::CABALLO, "imagenes/caballo rojo.png", "imagenes/caballo verde.png") {};
	bool movimiento_valido(Casilla inicio, Casilla fin,  Tablero& tablero);

};

