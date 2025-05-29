#pragma once
#include "pieza.h"
class reina :public Pieza
{
public:
	reina(COLOR color) : Pieza(color, TIPO::REINA, "imagenes/reina roja.png", "imagenes/reina verde.png") {};
	virtual bool movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda);

};

