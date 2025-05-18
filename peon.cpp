#include "peon.h"
#include "tablero.h"
#include "casilla.h"

bool Peon::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda) {
    // Comprobar que el destino está dentro del tablero
    if (Casilla::fueraTablero(fin))
        return false;

    // Movimiento vertical simple
    if (this->color == VERDE) { // Peón blanco
        if (Casilla::movPeonBlanco(inicio, fin))
            return true;
        if (Casilla::comerPeonBlanco(inicio, fin))
            return true;
    }
    else if (this->color == ROJO) { // Peón negro
        if (Casilla::movPeonNegro(inicio, fin))
            return true;
        if (Casilla::comerPeonNegro(inicio, fin))
            return true;
    }

    return false;
}
