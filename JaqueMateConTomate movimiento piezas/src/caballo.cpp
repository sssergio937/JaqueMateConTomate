#include "caballo.h"
#include "tablero.h"
#include "casillas.h"

bool caballo::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda) {
   // Comprobar que el destino está dentro del tablero
    if (Casilla::fueraTablero(fin))
        return false;

    // Comprobar que el movimiento es en L (caballo)
    if (!Casilla::movCaballo(inicio, fin))
        return false;
  

    return true;
}
