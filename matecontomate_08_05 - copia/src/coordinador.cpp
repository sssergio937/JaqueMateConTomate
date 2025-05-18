#include "coordinador.h"

void Coordinador::dibuja()
{
	switch (estado) {
	case INICIO:
		// CODIGO DE DIBUJO DE LA PANTALLA DE INICIO
		// definicion de la vista para este menu + dibujo de este menu
		break;
	case JUEGO:
		mundo.dibuja();				// se llama a la funcion dibuja de mundo
		break;
	case FIN:
		// CODIGO DE DIBUJO PARA LA PANTALLA DE FIN
		break;
	}
}

void Coordinador::tecla(unsigned char key)
{
	switch (estado) {

	// funcionalidad de las teclas cuando estamos en estado INICIO
	case INICIO:
		if (key == 's') exit(0);					// con la tecla s termina la ejecucion del programa
		if (key != 'e' && key != 'E') return;		// si la tecla no es e o E sale de la funcion
		mundo.inicializa();
		estado = JUEGO;
		break;

	// funcionalidad de las teclas cuando estamos en estado JUEGO
	case JUEGO:
		mundo.tecla(key);				// si estamos en juego le pasa el control a mundo
		break;

	// funcionalidad de las teclas cuando estamos en estado FIN
	case FIN:
		// codigo de entrada por teclado para la pantalla de fin
		break;

	}
}