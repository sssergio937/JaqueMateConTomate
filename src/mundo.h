#include "tablero.h"
#include "modo.h"

class Mundo
{
public: 

	// instanciacion de los objetos de las diferentes clases RELACION DE COMPOSICION
	Tablero tablero{ 5, 5, 2.0 };
	Modo modo;

	void tecla(unsigned char key);
	void inicializa();
	void dibuja();

	double x_ojo;
	double y_ojo;
	double z_ojo; 
};
