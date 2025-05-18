#include "alfil.h"
#include "tablero.h"
#include "casilla.h"

bool Alfil::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda) {
    // Comprobar que el destino est� dentro del tablero
    if (Casilla::fueraTablero(fin))
        return false;

    // Comprobar que el movimiento es v�lido para el alfil (movimiento diagonal)
    if (Casilla::movAlfil(inicio, fin))
        return true;

    return false;
}
