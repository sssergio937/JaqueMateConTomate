#pragma once
#include "pieza.h"
class Rey : public Pieza
{
public:
	Rey(COLOR c, TIPO t, const char* im_b, const char* im_n)
		: Pieza(c, t, im_b, im_n) {
	}
};

