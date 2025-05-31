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
	bool enJaque = false;
	bool enJaqueMate = false;
	char mensaje[100] = "";
	bool esperandoCoronacion = false;
	Casilla casillaCoronacion;
	Pieza::COLOR colorCoronacion;
	// instanciacion de los objetos pieza
	Pieza::COLOR turno = Pieza::VERDE; // Comienza el turno con las blancas

public: 
	/*
	// instanciacion de los objetos de las diferentes clases
	// instanciacion de las piezas 

*/

	void tecla(unsigned char key);
	void inicializa(bool variante);
	void mueve();
	void dibuja();
	void cambiarTurno();
	void dibujarTexto(float x, float y, const char* texto);
	void clickRaton(int x, int y);
	bool getEnJaque() const { return enJaque; }
	bool getEnJaqueMate() const { return enJaqueMate; }
	const char* getMensaje() const { return mensaje; }
	void turnoMaquina(int dificultad); 
	Pieza::COLOR getTurno() const { return turno; }
	bool getEsperandoCoronacion() const { return esperandoCoronacion; }
	//int evaluarTablero(const Tablero& tablero);
	

};
