#pragma once
#include "pieza.h"
class reina :public Pieza
{
public:
	reina(COLOR color) : Pieza(color, TIPO::REINA, "imagenes/reina roja.png", "imagenes/reina verde.png") {};
};

