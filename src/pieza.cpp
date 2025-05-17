#include "Pieza.h"
#include "Tablero.h"
#include "casilla.h"



//MOVIMIENTOS COMUNES EN TABLERO 5x5
bool Pieza::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda)
{
	int aux;

	//COMPROBACION DE TRAYECTORIA. Objetivo: no saltar entre piezas
	//LINEAL EN FILAS // movimiento vertical
	if (fin.fila != inicio.fila && fin.columna == inicio.columna)
	{
		aux = (fin.fila - inicio.fila) / abs(fin.fila - inicio.fila);
		while (abs(fin.fila - inicio.fila) > 1)
		{
			inicio.fila = inicio.fila + aux;
			//if (celda[inicio] != nullptr) return false;
			if (celda.getPieza(inicio) != nullptr) return false;//chatgpt
		}
	}

	//LINEAL EN COLUMNAS //movimiento horizontal
	else if (fin.columna != inicio.columna && fin.fila == inicio.fila)
	{
		aux = (fin.columna - inicio.columna) / abs(fin.columna - inicio.columna);
		while (abs(fin.columna - inicio.columna) > 1)
		{
			inicio.columna = inicio.columna + aux;
			//if (celda[inicio] != nullptr) return false;
			if (celda.getPieza(inicio) != nullptr) return false;//chatgpt
		}
	}

	//DIAGONAL DE IZQUIERDA A DERECHA
	else if (Casilla::noSaltarDiagonal(inicio, fin) == true)
	{
		aux = (fin.columna - inicio.columna) / abs(fin.columna - inicio.columna);
		while (abs(fin.columna - inicio.columna) > 1)
		{
			inicio.columna = inicio.columna + aux;
			inicio.fila = inicio.fila + aux;
			if (celda[inicio] != nullptr) return false;
			//if (celda.getPieza(inicio) != nullptr) return false;//chatgpt
		}
	}

	//DIAGONAL DE DERECHA A IZQUIERDA
	else if (fin.columna != inicio.columna && fin.fila != inicio.fila)
	{
		aux = (fin.columna - inicio.columna) / abs(fin.columna - inicio.columna);
		while (abs(fin.columna - inicio.columna) > 1)
		{
			inicio.columna = inicio.columna + aux;
			inicio.fila = inicio.fila - aux;
			if (celda[inicio] != nullptr) return false;
			//if (celda.getPieza(inicio) != nullptr) return false;//chatgpt
		}
	}

	return true; // movimiento valido
}

void Pieza::dibuja() {
	imagen.setPos(posicion.x, posicion.y);
	imagen.draw();
}