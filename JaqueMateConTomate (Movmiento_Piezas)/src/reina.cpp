#include "reina.h"
#include "tablero.h"

bool reina::movimiento_valido(Casilla inicio, Casilla fin, Tablero& tablero) {
    int filaInicio = inicio.fila;
    int colInicio = inicio.columna;
    int filaFin = fin.fila;
    int colFin = fin.columna;

    // No puede moverse a su propia casilla
    if (filaInicio == filaFin && colInicio == colFin)
        return false;

    int despVertical = filaFin - filaInicio;
    int despHorizontal = colFin - colInicio;

    bool esDiagonal = false;
    bool esRecto = false;

    if (abs(despVertical) == abs(despHorizontal))
        esDiagonal = true;

    if (filaInicio == filaFin || colInicio == colFin)
        esRecto = true;

    if (!esDiagonal && !esRecto)
        return false;

    int dirFila = 0;
    int dirCol = 0;

    if (despVertical > 0)
        dirFila = 1;
    else if (despVertical < 0)
        dirFila = -1;

    if (despHorizontal > 0)
        dirCol = 1;
    else if (despHorizontal < 0)
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