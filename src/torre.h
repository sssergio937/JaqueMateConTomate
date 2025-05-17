#pragma once
#include "pieza.h"

class Torre : public Pieza
{
public:
	Torre(COLOR c, TIPO t, const char* im_b, const char* im_n)
		: Pieza(c, t, im_b, im_n) {
	}
};

