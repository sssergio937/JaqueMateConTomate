#include "tablero.h"
#include "modo.h"
#include <vector>
#include "pieza.h"
#include "caballo.h"
#include "alfil.h"
#include "torre.h"
#include "rey.h"
#include "peon.h"
#include "reina.h"

class Mundo
{
public: 

	// instanciacion de los objetos de las diferentes clases RELACION DE COMPOSICION
	Tablero tablero{ 5, 5, 2.0 };
	Modo modo;

	std::vector<Pieza*> piezas; // vector de punteros a piezas

	Caballo caballoverde{ Pieza::VERDE, Pieza::CABALLO, "imagenes/caballo_verde.png", "imagenes/caballo_rojo.png" };
	Caballo caballorojo{ Pieza::ROJO, Pieza::CABALLO, "imagenes/caballo_rojo.png", "imagenes/caballo_verde.png" };

	Alfil alfilverde{ Pieza::VERDE, Pieza::ALFIL, "imagenes/alfil_verde.png", "imagenes/alfil_rojo.png" };

	void tecla(unsigned char key);
	void inicializa();
	void dibuja();

	double x_ojo;
	double y_ojo;
	double z_ojo; 

	~Mundo()
	{
		for (auto pieza : piezas) {
			delete pieza;
		}
		piezas.clear();
	}
};
