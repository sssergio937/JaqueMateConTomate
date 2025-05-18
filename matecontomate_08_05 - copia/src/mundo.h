#include "tablero.h"
#include "pieza.h"
class Mundo
{
private:
	Tablero tablero{ 5, 5, 4.0 };		// tablero de 5x5 con casillas de lado 10
	// instanciacion de los objetos pieza
public: 
	/*
	// instanciacion de los objetos de las diferentes clases
	Tablero tablero{ 5, 5, 5.0 };		// tablero de 5x5 con casillas de lado 10
	// instanciacion de las piezas 

*/

	void tecla(unsigned char key);
	void inicializa();
	void mueve();
	void dibuja();


};
