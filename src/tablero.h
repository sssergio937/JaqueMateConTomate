#pragma once

class Tablero
{
private:
	int filas, columnas;
	float lado;
public:
	Tablero(int f, int c, float l);
	void dibuja();
	int getPieza{ return filas,columnas };
};

