#include "caballo.h"
#include "tablero.h"

bool caballo::movimiento_valido(Casilla inicio, Casilla fin,  Tablero& tablero) {
    int filaInicio = inicio.fila;
    int colInicio = inicio.columna;
    int filaFin = fin.fila;
    int colFin = fin.columna;

    // No puede quedarse en la misma casilla
    if (filaInicio == filaFin && colInicio == colFin)
        return false;

    int desplazamientoVertical = abs(filaFin - filaInicio);
    int desplazamientoHorizontal = abs(colFin - colInicio);

    // Verificar movimiento en "L"
    bool esMovimientoL = (desplazamientoVertical == 2 && desplazamientoHorizontal == 1) ||
        (desplazamientoVertical == 1 && desplazamientoHorizontal == 2);
    if (!esMovimientoL)
        return false;

    return true;
}