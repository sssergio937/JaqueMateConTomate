#include "torre.h"
#include "tablero.h"

bool torre::movimiento_valido(Casilla inicio, Casilla fin,  Tablero& tablero) {
    int filaInicio = inicio.fila;
    int colInicio = inicio.columna;
    int filaFin = fin.fila;
    int colFin = fin.columna;

    // No puede moverse a su propia casilla
    if (filaInicio == filaFin && colInicio == colFin)
        return false;

    // Solo se permite movimiento recto (horizontal o vertical)
    if (filaInicio != filaFin && colInicio != colFin)
        return false;

    int dirFila = 0;
    int dirCol = 0;

    if (filaFin > filaInicio)
        dirFila = 1;
    else if (filaFin < filaInicio)
        dirFila = -1;

    if (colFin > colInicio)
        dirCol = 1;
    else if (colFin < colInicio)
        dirCol = -1;

    int f = filaInicio + dirFila;
    int c = colInicio + dirCol;
    while (f != filaFin || c != colFin) {
        if (tablero.getPieza(f, c) != nullptr)
            return false;
        f += dirFila;
        c += dirCol;
    }

    return true;
}