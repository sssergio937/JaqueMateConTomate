#pragma once
#include <string>
#include <iostream>
#include "ETSIDI.h"
#include <freeglut.h>
#include "casillas.h"
#include "vector2D.h"

//using namespace ETSIDI;

class Tablero;


//CLASE ENCARGADA DE LOS ATRIBUTOS Y MÉTODOS COMUNES A TODAS LAS PIEZAS
class Pieza
{

public:
	//color de la pieza
	enum COLOR { NS = -1, VERDE, ROJO };
	//tipo de la pieza
	enum TIPO { NF = -1, PEON, CABALLO, REINA, REY, TORRE, ALFIL };
	Vector2D posicion; //posicion de la pieza

	Pieza(COLOR c, TIPO p, const char* im_b, const char* im_n) :
		color(c),
		tipo(p),
		imagen(c == ROJO ?  im_n : im_b)// si es la pieza verde se le mete la imagen verde, si no la roja
	{
		imagen.setCenter(static_cast<float>(0.4), static_cast<float>(0.4));
		imagen.setSize(0.8f, 0.8f);
		imagen.draw();
	};

	TIPO getPieza() { return tipo; }
	COLOR getColor() { return color; }

	virtual bool movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda);
	void setPosicion(double x, double y) { posicion = Vector2D{ x, y }; }
	//virtual void dibuja() { imagen.draw(); }
	virtual void dibuja();

protected:
	TIPO tipo = NF;
	COLOR color = NS;
	ETSIDI::Sprite imagen;

};

