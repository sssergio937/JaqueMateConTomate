#include "tablero.h"
#include "modo.h"

class Mundo
{
public: 

	// instanciacion de los objetos de las diferentes clases RELACION DE COMPOSICION
	Tablero tablero{ 5, 5, 2.0 };
	Modo modo;

	Caballo caballoverde{ Pieza::VERDE, Pieza::CABALLO, "imagenes/caballo_verde.png", "imagenes/caballo_rojo.png" };
	Caballo caballorojo{ Pieza::ROJO, Pieza::CABALLO, "imagenes/caballo_rojo.png", "imagenes/caballo_verde.png" };

	void tecla(unsigned char key);
	void inicializa();
	void dibuja();

	double x_ojo;
	double y_ojo;
	double z_ojo; 
};
