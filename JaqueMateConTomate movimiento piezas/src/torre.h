#pragma once
#include "pieza.h"
class torre : public Pieza
{
public:
	torre(COLOR color) : Pieza(color, TIPO::TORRE, "imagenes/torre roja.png", "imagenes/torre verde.png") {};
	virtual bool movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda);

};

