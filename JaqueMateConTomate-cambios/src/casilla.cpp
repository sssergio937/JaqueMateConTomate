#include "casilla.h"

// Devuelve true si el movimiento entre esta casilla y otra NO es diagonal

bool Casilla::mlineal(const Casilla& inicio, const Casilla& final) const {
	if ((fin.fila != inicio.fila && fin.columna == inicio.columna) || (fin.columna != inicio.columna && fin.fila == inicio.fila)) return true;
	else return false;

}

bool Casilla::mDiagonal(const Casilla& inicio, const Casilla & final) const {
	if (((abs(fin.fila - inicio.fila) + abs(fin.columna - inicio.columna)) % 2 == 0) && (abs(fin.fila - inicio.fila) == abs(fin.columna - inicio.columna)))
		return true;
	else return false;
}

bool Casilla::noSaltarDiagonal(const Casilla& inicio, const Casilla&final) const {
	if ((fin.columna - inicio.columna == fin.fila - inicio.fila) && fin.columna != inicio.columna && fin.fila != inicio.fila) return true;
	else return false;
}

bool Casilla::movRey(const Casilla& inicio, const Casilla& fin) const{
	if (abs(fin.fila - inicio.fila) <= 1 && abs(fin.columna - inicio.columna) <= 1) return true;
	else return false;
}

bool Casilla::movPeonBlanco(const Casilla& inicio, const Casilla& fin) const {
	// Movimiento vertical de una casilla hacia adelante (para peón blanco)
	if (fin.columna == inicio.columna && fin.fila == inicio.fila + 1) return true;
	else return false;
}

bool Casilla::movPeonNegro(const Casilla& inicio, const Casilla& fin) const {
	// Movimiento vertical de una casilla hacia adelante (para peón negro)
	if (fin.columna == inicio.columna && fin.fila == inicio.fila - 1) return true;
	else return false;
}

bool Casilla::comerPeonBlanco(const Casilla& inicio, const Casilla& fin) const {
	// Captura en diagonal: una fila adelante y una columna a la izquierda o derecha
	if ((fin.fila == inicio.fila + 1) && (fin.columna == inicio.columna + 1 || fin.columna == inicio.columna - 1)) return true;
	else return false;
}

bool Casilla::comerPeonNegro(const Casilla& inicio, const Casilla& fin) const {
	// Captura en diagonal: una fila atrás y una columna a la izquierda o derecha
	if ((fin.fila == inicio.fila - 1) && (fin.columna == inicio.columna + 1 || fin.columna == inicio.columna - 1)) return true;
	else return false;
}

bool Casilla::movAlfil(const Casilla& incio, const Casilla& fin)const {
	// Un movimiento es válido para el alfil si la diferencia de filas y columnas es igual (movimiento diagonal)
	if (abs(fin.fila - inicio.fila) == abs(fin.columna - inicio.columna) && fin.fila != inicio.fila) return true;
	else return false;
}

bool Casilla::movCaballo(const Casilla& inicio, const Casilla& fin) const {
	int df = abs(fin.fila - inicio.fila);
	int dc = abs(fin.columna - inicio.columna);
	// Movimiento en L: 2 en una dirección y 1 en la otra
	if ((df == 2 && dc == 1) || (df == 1 && dc == 2)) return true;
	else return false;
}

bool Casilla::movTorre(const Casilla& inicio, const Casilla& fin) const {
	// Movimiento válido si está en la misma fila o en la misma columna (pero no ambos a la vez)
	if ((fin.fila == inicio.fila && fin.columna != inicio.columna) || (fin.columna == inicio.columna && fin.fila != inicio.fila)) return true;
	else return false;
}

bool Casilla::movReina(const Casilla& inicio, const Casilla& fin) const {
	// Movimiento válido si es un movimiento de torre o de alfil
	if (movTorre(inicio, fin) || movAlfil(inicio, fin)) return true;
	else return false;
}

bool Casilla::fueraTablero(const Casilla& c)const
{
	if (c.fila > 5 || c.fila < 0 || c.columna > 5 || c.columna < 0) return true;
	else return false;
}