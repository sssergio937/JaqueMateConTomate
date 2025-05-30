#include "peon.h"
#include"tablero.h"

bool peon::movimiento_valido(Casilla inicio, Casilla fin,  Tablero& tablero)
{
    int direccionMovimiento;
    if (getColor() == VERDE)
        direccionMovimiento = -1;
    else
        direccionMovimiento = 1;

    int diferenciaFilas = fin.fila - inicio.fila;
    int diferenciaColumnas = abs(fin.columna - inicio.columna);

    Pieza* piezaEnDestino = tablero.getPieza(fin.fila, fin.columna);

    // Movimiento simple hacia adelante
    if (diferenciaColumnas == 0 && diferenciaFilas == direccionMovimiento && piezaEnDestino == nullptr)
        return true;

    // Captura en diagonal
    if (diferenciaColumnas == 1 && diferenciaFilas == direccionMovimiento && piezaEnDestino != nullptr)
        return true;

    return false;
}