#include "tablero.h"
#include "pieza.h"
class Mundo
{
private:
	Tablero tablero{ 5, 5, 4.0 };		// tablero de 5x5 con casillas de lado 10
	bool variante = 0;					// 0 -> ajedrez baby   1 -> ajedrez gardner
	bool modo = 0;						// 0 -> 1player   1 -> 2players
	Casilla seleccionada;
	bool haySeleccion = false;

	// instanciacion de los objetos pieza
	Pieza::COLOR turno = Pieza::VERDE; // Comienza el turno con las blancas

public: 
	/*
	// instanciacion de los objetos de las diferentes clases
	// instanciacion de las piezas 

*/

	void tecla(unsigned char key);
	void inicializa();
	void mueve();
	void dibuja();
	void cambiarTurno();
	void dibujarTexto(float x, float y, const char* texto);
	void clickRaton(int x, int y);


};
