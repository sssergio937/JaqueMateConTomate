#pragma once
#include "freeglut.h"
#include "mundo.h"
#include "ETSIDI.h"

class Coordinador
{
private:
	enum Estado { INICIO, FADE_IN, PEDIR_DATOS, RANKING, CREDITOS, AJUSTES, JUEGO1J, JUEGO2J, MENU, FIN } estado{};		//	 estados del juego, se crea una variable de tipo Estado con valor INICIO
	Mundo mundo;

	// seleccion de jugadores y variante
	bool variante = 0;						// 0 -> ajedrez baby   1 -> ajedrez gardner
	bool jugadores = 0;						// 0 -> 1Jugador   1 -> 2Jugadores
	bool iniciado= false;

	// para la seleccion dentro del menu
	int seleccionMenu = 0;
	char opcionesMenu[7][20] = {				//tantos elementos como opciones diferentes en el menu
		"UN JUGADOR",
		"DOS JUGADORES",
		"RANKING",
		"AJUSTES",
		"CREDITOS",
		"SALIR",
	};

	float alpha = 0.0f;			//para el efecto de transicion fade_in
	
	//para la musica
	bool musicaActiva = true;
	bool transicionSonidoReproducido = false;

	//para pedir datos del jugador
	std::string nombreJugador;
	int dificultadMaquina = 1; //1=fácil, 2=media, 3=difícil
	int pedirDatosPaso = 0;    //0=nombre, 1=dificultad
	std::string bufferNombre;  //para ir escribiendo el nombre

public:
	//metodos
	void dibuja();
	void tecla(unsigned char key);
	void mueve();
	void inicializa();
	void clickRaton(int x, int y);
};

