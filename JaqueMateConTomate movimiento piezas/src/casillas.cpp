#include "casillas.h"
#include <cmath>
// Devuelve true si el movimiento entre esta casilla y otra NO es diagonal

bool Casilla::mlineal(Casilla inicio, Casilla fin) {
	if ((fin.fila != inicio.fila && fin.columna == inicio.columna) || (fin.columna != inicio.columna && fin.fila == inicio.fila)) return true;
	else return false;

}

bool Casilla::mDiagonal(Casilla inicio, Casilla fin) {
	if (((abs(fin.fila - inicio.fila) + abs(fin.columna - inicio.columna)) % 2 == 0) && (abs(fin.fila - inicio.fila) == abs(fin.columna - inicio.columna)))
		return true;
	else return false;
}

bool Casilla::noSaltarDiagonal(Casilla inicio, Casilla fin) {
	if ((fin.columna - inicio.columna == fin.fila - inicio.fila) && fin.columna != inicio.columna && fin.fila != inicio.fila) return true;
	else return false;
}

bool Casilla::movRey(Casilla inicio, Casilla fin) {
	if (abs(fin.fila - inicio.fila) <= 1 && abs(fin.columna - inicio.columna) <= 1) return true;
	else return false;
}

bool Casilla::movPeonBlanco(Casilla inicio, Casilla fin) {
	// Movimiento vertical de una casilla hacia adelante (para peón blanco)
	if (fin.columna == inicio.columna && fin.fila == inicio.fila + 1) return true;
	else return false;
}

bool Casilla::movPeonNegro(Casilla inicio, Casilla fin) {
	// Movimiento vertical de una casilla hacia adelante (para peón negro)
	if (fin.columna == inicio.columna && fin.fila == inicio.fila - 1) return true;
	else return false;
}

bool Casilla::comerPeonBlanco(Casilla inicio, Casilla fin) {
	// Captura en diagonal: una fila adelante y una columna a la izquierda o derecha
	if ((fin.fila == inicio.fila + 1) && (fin.columna == inicio.columna + 1 || fin.columna == inicio.columna - 1)) return true;
	else return false;
}

bool Casilla::comerPeonNegro(Casilla inicio, Casilla fin) {
	// Captura en diagonal: una fila atrás y una columna a la izquierda o derecha
	if ((fin.fila == inicio.fila - 1) && (fin.columna == inicio.columna + 1 || fin.columna == inicio.columna - 1)) return true;
	else return false;
}

bool Casilla::movAlfil(Casilla inicio, Casilla fin) {
	// Un movimiento es válido para el alfil si la diferencia de filas y columnas es igual (movimiento diagonal)
	if (abs(fin.fila - inicio.fila) == abs(fin.columna - inicio.columna) && fin.fila != inicio.fila) return true;
	else return false;
}

bool Casilla::movCaballo(Casilla inicio, Casilla fin) {
	int df = abs(fin.fila - inicio.fila);
	int dc = abs(fin.columna - inicio.columna);
	// Movimiento en L: 2 en una dirección y 1 en la otra
	if ((df == 2 && dc == 1) || (df == 1 && dc == 2)) return true;
	else return false;
}

bool Casilla::movTorre(Casilla inicio, Casilla fin) {
	// Movimiento válido si está en la misma fila o en la misma columna (pero no ambos a la vez)
	if ((fin.fila == inicio.fila && fin.columna != inicio.columna) || (fin.columna == inicio.columna && fin.fila != inicio.fila)) return true;
	else return false;
}

bool Casilla::movReina(Casilla inicio, Casilla fin) {
	// Movimiento válido si es un movimiento de torre o de alfil
	if (movTorre(inicio, fin) || movAlfil(inicio, fin)) return true;
	else return false;
}

bool Casilla::fueraTablero(Casilla c)
{
	if (c.fila > 5 || c.fila < 0 || c.columna > 5 || c.columna < 0) return true;
	else return false;
}