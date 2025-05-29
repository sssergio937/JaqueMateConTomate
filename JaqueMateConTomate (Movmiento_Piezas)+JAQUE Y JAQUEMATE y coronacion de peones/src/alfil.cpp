#include "alfil.h" 
#include "tablero.h"

bool alfil::movimiento_valido(Casilla inicio, Casilla fin, Tablero& tablero) 
{
    int filaInicio = inicio.fila;
    int colInicio = inicio.columna;
    int filaFin = fin.fila;
    int colFin = fin.columna;

    // No puede moverse a su misma posición
    if (filaInicio == filaFin && colInicio == colFin)
        return false;

    int desplazamientoVertical = filaFin - filaInicio;
    int desplazamientoHorizontal = colFin - colInicio;

    // Debe moverse en diagonal (valor absoluto igual en filas y columnas)
    if (abs(desplazamientoVertical) != abs(desplazamientoHorizontal))
        return false;

    int dirFila;
    int dirCol;

    if (desplazamientoVertical > 0)
        dirFila = 1;
    else
        dirFila = -1;

    if (desplazamientoHorizontal > 0)
        dirCol = 1;
    else
        dirCol = -1;

    int f = filaInicio + dirFila;
    int c = colInicio + dirCol;

    // Verifica que no haya piezas en el camino
    while (f != filaFin && c != colFin) {
        if (tablero.getPieza(f, c) != nullptr)
            return false;
        f += dirFila;
        c += dirCol;
    }

    return true;
}