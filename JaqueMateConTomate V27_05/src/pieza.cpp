#include "Pieza.h"
#include "Tablero.h"
#include "casillas.h"



//MOVIMIENTOS COMUNES EN TABLERO 5x5
bool Pieza::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda)
{
	return true;
}

void Pieza::dibuja() {

	imagen.setPos(posicion.x, posicion.y);
	imagen.draw();
}