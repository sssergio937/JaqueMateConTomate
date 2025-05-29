#include "rey.h"
#include "tablero.h"

bool rey::movimiento_valido(Casilla inicio, Casilla fin, Tablero& tablero) 
{
    int filaInicio = inicio.fila;
    int colInicio = inicio.columna;
    int filaFin = fin.fila;
    int colFin = fin.columna;

    // No puede quedarse en la misma casilla
    if (filaInicio == filaFin && colInicio == colFin)
        return false;

    int desplazamientoVertical = abs(filaFin - filaInicio);
    int desplazamientoHorizontal = abs(colFin - colInicio);

    // Movimiento válido: una casilla en cualquier dirección
    if (desplazamientoVertical <= 1 && desplazamientoHorizontal <= 1)
        return true;

    return false;
}