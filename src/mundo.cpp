#include "Mundo.h"
#include "freeglut.h"

void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			5.0, 0, 5.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	tablero.dibuja();

	for(auto pieza: piezas) {
		pieza->dibuja();
	}
}

void Mundo::inicializa()
{
	x_ojo = 5;
	y_ojo = 20;
	z_ojo = 4.99;			// para evitar problemas con el plano cercano

    piezas.clear();
    piezas.push_back(new Caballo(Pieza::VERDE, Pieza::CABALLO, "imagenes/caballo_verde.png", "imagenes/caballo_rojo.png"));
    piezas.back()->posicion = {0, 0}; // ejemplo de posición

    piezas.push_back(new Alfil(Pieza::ROJO, Pieza::ALFIL, "imagenes/alfil_rojo.png", "imagenes/alfil_verde.png"));
    piezas.back()->posicion = {2, 2}; // ejemplo de posición

    // ... añade el resto de piezas ...
}

void Mundo::tecla(unsigned char key)
{

}


