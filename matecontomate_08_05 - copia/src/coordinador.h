#pragma once
#include "freeglut.h"
#include "mundo.h"

enum Estado { INICIO, JUEGO, FIN };		//	 estados del juego, tendremos que añadir mas

class Coordinador
{
private:
	enum Estado { INICIO, JUEGO, FIN } estado{};		//	 estados del juego, se crea una variable de tipo Estado con valor INICIO
	Mundo mundo;
public:
	//metodos
	void dibuja();
	void tecla(unsigned char key);
};

