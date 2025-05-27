#pragma once
#include "pieza.h"
class rey : public Pieza
{
public:
	rey(COLOR color) : Pieza(color, TIPO::REY, "imagenes/rey rojo.png", "imagenes/rey verde.png") {};

};

