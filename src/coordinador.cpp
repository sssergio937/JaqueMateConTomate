#include "coordinador.h"

void Coordinador::inicializa()
{
	ETSIDI::playMusica("sonidos/tema_fondo.mp3");
	alpha = 0.0f;
	transicionSonidoReproducido = false;
}



void Coordinador::dibuja()
{
	switch (estado) {
	case INICIO:
		
		// imagen del fondo, que se situa en la altura z = 0
		glClearColor(0.212, 0.212, 0.212, 1);						// se establece 1 vez el color con el que se va a limpiar la pantalla, el de fondo
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Inicio_Juego.png").id);
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(0.9, 1, 1);
		glTexCoord2d(0, 1); glVertex2f(-24.5, -19);         // todo esto es el ajuste de la imagen del fondo 
		glTexCoord2d(1, 1); glVertex2f(24.5, -19);
		glTexCoord2d(1, 0); glVertex2f(24.5, 19);
		glTexCoord2d(0, 0); glVertex2f(-24.5, 19);
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);

		// texto de la pantalla de inicio
		ETSIDI::setTextColor(0, 0, 0);
		ETSIDI::setFont("fuentes/Roboto.ttf", 22);
		ETSIDI::printxy("Pulsa ENTER para comenzar...", -10, -15);
		break;

	case FADE_IN:
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0, 0, 0, 1.0f - alpha);
		glBegin(GL_QUADS);
		glVertex2f(-40, -40);
		glVertex2f(40, -40);
		glVertex2f(40, 40);
		glVertex2f(-40, 40);
		glEnd();
		glDisable(GL_BLEND);
		break;

	case MENU:

		// texto con las opciones del menu
		for (int i = 0; i < 6; i++)
		{
			if (i == seleccionMenu)
				ETSIDI::setTextColor(1, 1, 0);
				
			else
				ETSIDI::setTextColor(1, 1, 1);
			ETSIDI::setFont("fuentes/Roboto.ttf", 22);
			ETSIDI::printxy(opcionesMenu[i], -20, 15 - i * 3);
			
			// impresion de la variable actual
			ETSIDI::setTextColor(1, 1, 1);
			if (variante == 0)
				ETSIDI::printxy("AJEDREZ BABY", -20, -8);
			else
				ETSIDI::printxy("AJEDREZ GARDNER", -20, -8);
			ETSIDI::setFont("fuentes/Roboto.ttf", 14);
			ETSIDI::printxy("W y S para navegar por el menú", 8, -12);
			ETSIDI::printxy("ENTER para seleccionar", 8, -14);
			ETSIDI::printxy("V para cambiar la variante", 8, -16);
		
		// boton del cambio de variante
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/cambio_variante.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1); glVertex2f(-4, -13);   // inferior izquierda
			glTexCoord2d(1, 1); glVertex2f(4, -13);    // inferior derecha
			glTexCoord2d(1, 0); glVertex2f(4, -2);     // superior derecha
			glTexCoord2d(0, 0); glVertex2f(-4, -2);    // superior izquierda
			glEnd();
			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);

		// poner foto en funcion de la variante elegida
			glEnable(GL_TEXTURE_2D);
			if(variante == 0)
				glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/variante_baby.png").id);
			else
				glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/variante_gardner.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1); glVertex2f(8, 0);   // inferior izquierda
			glTexCoord2d(1, 1); glVertex2f(20, 0);    // inferior derecha
			glTexCoord2d(1, 0); glVertex2f(20, 12);     // superior derecha
			glTexCoord2d(0, 0); glVertex2f(8, 12);    // superior izquierda
			glEnd();
			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
		}
		break;
	case RANKING:
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto.ttf", 14);
		ETSIDI::printxy("ESC para volver al menú", 11, -16);
		break;
	case AJUSTES:
		
		//texto
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto.ttf", 14);
		ETSIDI::printxy("M para activar/desactivar música", -20, 15);
		ETSIDI::printxy("ESC para volver al menú", 11, -16);
		//imagenes
		if (musicaActiva == 1)
		{
			// dibujo de altavoz musica activa
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/sonido_on.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1); glVertex2f(-20, 8);         // todo esto es el ajuste de la imagen del fondo 
			glTexCoord2d(1, 1); glVertex2f(-15, 8);
			glTexCoord2d(1, 0); glVertex2f(-15, 13);
			glTexCoord2d(0, 0); glVertex2f(-20, 13);
			glEnd();
			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
		}
		else
		{
			// dibujo de altavoz musica inactiva
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/sonido_off.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1); glVertex2f(-20, 8);         // todo esto es el ajuste de la imagen del fondo 
			glTexCoord2d(1, 1); glVertex2f(-15, 8);
			glTexCoord2d(1, 0); glVertex2f(-15, 13);
			glTexCoord2d(0, 0); glVertex2f(-20, 13);
			glEnd();
			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
		}
		break;
	case JUEGO2J:
		mundo.dibuja();				// se llama a la funcion dibuja de mundo
		break;

	case CREDITOS:
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);		// color del fondo
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto.ttf", 14);
		ETSIDI::printxy("Desarrollado por Equipo Jaque Mate con Tomate", -20, 15);
		ETSIDI::printxy("Mario: Diseño del menu y transiciones", -20, 13);
		ETSIDI::printxy("Diego: Control de estados e interfaz", -20, 11);
		ETSIDI::printxy("Calde: Efectos visuales y sprites", -20, 9);
		ETSIDI::printxy("Sergio: Integracion de musica y sonidos", -20, 7);
		ETSIDI::printxy("Oscar: Gestion del ranking y entrada de datos", -20, 5);
		ETSIDI::printxy("GRACIAS POR JUGAR", -20, 1);
		ETSIDI::printxy("ESC para volver al menú", 11, -16);
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
		if (key == 13) 
		{
			estado = FADE_IN;
		}
		break;

	// funcionalidad de las teclas cuando estamos en estado MENU
	case MENU:
		// navegacion por el menu
		if (key == 119 || key == 87)				// con w o W
			seleccionMenu = (seleccionMenu - 1 + 6) % 6;		// 5 es el numero de opciones en el menu, si son mas cambiar el numero
		if (key == 115 || key == 83)				// con s o S
			seleccionMenu = (seleccionMenu + 1 + 6) % 6;		// 5 es el numero de opciones en el menu, si son mas cambiar el numero
		// seleccion en el menu
		if (key == 13)
		{
			if (seleccionMenu == 0) estado = PEDIR_DATOS;
			else if (seleccionMenu == 1) estado = JUEGO2J;
			else if (seleccionMenu == 2) estado = RANKING;
			else if (seleccionMenu == 3) estado = AJUSTES;
			else if (seleccionMenu == 4) estado = CREDITOS;
			else if (seleccionMenu == 5) exit(0);
		}
		
		// cambio de la variante elegida
		if (key == 118 || key == 86)
			variante = !variante;
		break;

	// funcionalidad de las teclas cuando estamos en estado AJUSTES
	case AJUSTES:
		if (key == 109 || key == 77)					// se activa o desactiva la musica con m y M
		{
			musicaActiva = !musicaActiva;

			// activacion/desactivacion de la musica
			if (musicaActiva == 0)
				ETSIDI::stopMusica();
			else
				ETSIDI::playMusica("sonidos/tema_fondo.mp3");
		}
		
		if (key == 27)
			estado = MENU;
		break;
	
	// funcionalidad de las teclas cuando estamos en estado RANKING
	case RANKING:
		if (key == 27)
			estado = MENU;
		break;

	// funcionalidad de las teclas cuando estamos en estado JUEGO
	case JUEGO2J:

		mundo.tecla(key);				// si estamos en juego le pasa el control a mundo
		break;
	
	// funcionalidad de las teclas cuando estamos en estado CREDITOS
	case CREDITOS:
		if (key == 27)
			estado = MENU;
		break;
	// funcionalidad de las teclas cuando estamos en estado FIN
	case FIN:
		// codigo de entrada por teclado para la pantalla de fin
		break;

	}
}

void Coordinador::mueve()
{
	//efecto fade_in
	if (estado == FADE_IN) {
		alpha += 0.01f;
		if (alpha >= 1.0f) {
			alpha = 1.0f;
			estado = MENU;
			if (!transicionSonidoReproducido) {
				ETSIDI::play("sonidos/transicion.mp3");
				transicionSonidoReproducido = true;
			}
		}
	}
}


