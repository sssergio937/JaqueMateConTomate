#pragma once
#include "pieza.h"
class peon : public Pieza
{
public:
	peon(COLOR color) : Pieza(color, TIPO::PEON, "imagenes/peon rojo.png", "imagenes/peon verde.png") {};
	bool movimiento_valido(Casilla inicio, Casilla fin, Tablero& tablero);
};

