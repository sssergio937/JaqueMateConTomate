#pragma once
#include "pieza.h"


class alfil : public Pieza
{
public:
	alfil(COLOR color) : Pieza(color, TIPO::ALFIL, "imagenes/alfil rojo.png", "imagenes/alfil verde.png") {};
	


};

