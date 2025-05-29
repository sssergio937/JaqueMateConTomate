#include "rey.h"
#include "tablero.h"
#include "casillas.h"

bool rey::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda) {
    // Comprobar que el destino está dentro del tablero
    if (Casilla::fueraTablero(fin))
        return false;

    // Comprobar que el movimiento es válido para el rey (una casilla en cualquier dirección)
    if (Casilla::movRey(inicio, fin))
        return true;
    
    return false;
}
