#include "Mundo.h"
#include "freeglut.h"

void Mundo::dibuja()
{
	gluLookAt(x_ojo, y_ojo, z_ojo,  // posicion del ojo
			5.0, 0, 5.0,      // hacia que punto mira  (0,0,0) 
			0.0, 1.0, 0.0);      // definimos hacia arriba (eje Y)    

	tablero.dibuja();
}


void Mundo::inicializa()
{
	x_ojo=5;
	y_ojo=20;
	z_ojo=4.99;			// para evitar problemas con el plano cercano
}

void Mundo::tecla(unsigned char key)
{

}
