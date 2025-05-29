#include "Pieza.h"
#include "Tablero.h"
#include "casillas.h"

bool Pieza::movimiento_valido(Casilla inicio, Casilla fin, Tablero& tablero)
{
    return true;    
}

void Pieza::dibuja() {
    float lado = 4.0f;
    float x = posicion.x * lado - 10.0f + lado / 2.0f;  // centrado horizontalmente
    float y = -(posicion.y * lado - 10.0f + lado / 2.0f); // centrado verticalmente

    imagen.setPos(x, y);
    imagen.setCenter(2.0f, 2.0f);
    imagen.draw();
}
