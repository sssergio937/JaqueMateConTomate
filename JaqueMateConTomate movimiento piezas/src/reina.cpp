#include "reina.h"
#include "tablero.h"
#include "casillas.h"

bool reina::movimiento_valido(Casilla inicio, Casilla fin, Tablero& celda) {
    // Comprobar que el destino está dentro del tablero
    if (Casilla::fueraTablero(fin))
        return false;

    // La reina se mueve como torre o como alfil
    if (Casilla::movTorre(inicio, fin) || Casilla::movAlfil(inicio, fin))
        return true;
    
    return false;
}
