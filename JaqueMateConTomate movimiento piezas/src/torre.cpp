#include "torre.h"
#include "tablero.h"
#include "casillas.h"

bool torre::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda) {
   // Comprobar que el destino est� dentro del tablero
    if (Casilla::fueraTablero(fin))
        return false;

    // Comprobar que el movimiento es v�lido para la torre (horizontal o vertical)
    if (Casilla::movTorre(inicio, fin))
        return true;

    return false;
}
