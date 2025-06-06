#include "coordinador.h"
#include <vector>
#include <cstdlib>  // Para usar system()
#include <fstream>	

struct JugadorRanking {
	std::string nombre;
	int ganadas;
	int nivel;
};
static std::vector<JugadorRanking> ranking;

void guardarRanking() {
	std::ofstream file("ranking.txt");
	for (const auto& j : ranking) {
		file << j.nombre << " " << j.ganadas << " " << j.nivel << std::endl;
	}
}
void cargarRanking() {
	ranking.clear();
	std::ifstream file("ranking.txt");
	std::string nombre;
	int ganadas, nivel;
	while (file >> nombre >> ganadas >> nivel) {
		ranking.push_back({ nombre, ganadas, nivel });
	}
}



void Coordinador::inicializa()
{
	cargarRanking();
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

		// texto de la pantalla de inicio, dentro de un rectangulo para que se vea
		glDisable(GL_LIGHTING);
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1);
		glVertex3f(-11, -16.5, 0.1);
		glVertex3f(13.5, -16.5, 0.1);
		glVertex3f(13.5, -12.5, 0.1);
		glVertex3f(-11, -12.5, 0.1);
		glEnd();
		glEnable(GL_LIGHTING);
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
			ETSIDI::printxy("W y S para navegar por el men�", 8, -12);
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
			if (variante == 0)
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
	case RANKING: {
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto.ttf", 18);
		ETSIDI::printxy("RANKING", -10, 15);
		int y = 12;
		for (const auto& j : ranking) {
			std::string nivelStr = (j.nivel == 1) ? "Tomatito" : (j.nivel == 2) ? "Se�or Tomate" : "MAESTRO Tomate";
			std::string linea = j.nombre + " | Ganadas: " + std::to_string(j.ganadas) + " | Nivel: " + nivelStr;
			ETSIDI::printxy(linea.c_str(), -10, y);
			y -= 2;
		}
		ETSIDI::setFont("fuentes/Roboto.ttf", 14);
		ETSIDI::printxy("ESC para volver al men�", 11, -16);
		break;
	}
	case AJUSTES:
		
		//texto
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto.ttf", 14);
		ETSIDI::printxy("M para activar/desactivar m�sica", -20, 15);
		ETSIDI::printxy("ESC para volver al men�", 11, -16);
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
	
	case PEDIR_DATOS:
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto.ttf", 22);
		if (pedirDatosPaso == 0) {
			ETSIDI::printxy("Introduce tu nombre:", -10, 10);
			ETSIDI::printxy(bufferNombre.c_str(), -10, 7);
			ETSIDI::setFont("fuentes/Roboto.ttf", 14);
			ETSIDI::printxy("Pulsa ENTER para continuar", -10, 4);
		}
		else if (pedirDatosPaso == 1) {
			ETSIDI::printxy("Selecciona dificultad de la maquina:", -10, 10);
			std::string difText = (dificultadMaquina == 1) ? "Tomatito" : (dificultadMaquina == 2) ? "Se�or Tomate" : "MAESTRO Tomate";
			ETSIDI::printxy(difText.c_str(), -10, 7);
			ETSIDI::setFont("fuentes/Roboto.ttf", 14);
			ETSIDI::printxy("Usa A/D para cambiar, ENTER para jugar", -10, 4);
		}
		break;

	case JUEGO1J:
		if (!iniciado) {
			mundo.inicializa(variante); 
			iniciado = true;
		}
		mundo.dibuja();
		//si es el turno de la m�quina, ejecuta su movimiento autom�ticamente
		if (mundo.getTurno() == Pieza::ROJO && !mundo.getEnJaqueMate() && !mundo.getEsperandoCoronacion()) {
			mundo.turnoMaquina(dificultadMaquina);
		}
		if (mundo.getEnJaqueMate()) {
			// Solo se ejecuta una vez al detectar el jaque mate
			if (!nombreJugador.empty()) {
				bool encontrado = false;
				for (auto& j : ranking) {
					if (j.nombre == nombreJugador && j.nivel == dificultadMaquina) {
						j.ganadas++;
						encontrado = true;
						break;
					}
				}
				if (!encontrado) {
					ranking.push_back({ nombreJugador, 1, dificultadMaquina });
				}
				guardarRanking();
			}
			estado = FIN;
			iniciado = false;
			reproducido = false;
		}
		break;

	case JUEGO2J:
		
		if (!iniciado) {
			mundo.inicializa(variante);
			iniciado = true;
			reproducido = false;

		}
		mundo.dibuja();				// se llama a la funcion dibuja de mundo
		// Mostrar mensaje de jaque o jaque mate si existe
		if (mundo.getMensaje()[0] != '\0') {
			mundo.dibujarTexto(-3.5f, 15.0f, mundo.getMensaje());
		}
		if (mundo.getEnJaqueMate()) {
			estado = FIN;
			iniciado = false;
		}
		break;

	case CREDITOS:
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);		// color del fondo
		ETSIDI::setTextColor(1, 1, 1);
		ETSIDI::setFont("fuentes/Roboto.ttf", 14);
		ETSIDI::printxy("Desarrollado por: Equipo Jaque Mate con Tomate G23", -20, 15);
		ETSIDI::printxy("Mario: Creo el espantapajaros", -20, 13);
		ETSIDI::printxy("Diego: Encargado de azada y rastrillo", -20, 11);
		ETSIDI::printxy("Daniel: Encargado de insectizidas ", -20, 9);
		ETSIDI::printxy("Sergio: Recolect� y cosech� las piezas", -20, 7);
		ETSIDI::printxy("Oscar: Plant� y reg� las piezas", -20, 5);
		ETSIDI::printxy("GRACIAS POR JUGAR", -20, 1);
		ETSIDI::printxy("ESC para volver al men�", 11, -16);
		break; 
	case FIN:
		if (!reproducido) {
			//system("start /wait wmplayer.exe \"C:\\UNIVERSIDAD\\3� Carrera\\Informatica Industrial\\JaqueMateConTomate-cambios (2)\\JaqueMateConTomate-cambios\\JaqueMateConTomate IA semichunga\\bin\\JaqueMateConTomate.mp4\"");
			//system("start /wait wmplayer.exe \"bin/JaqueMateConTomate.mp4\"");

			reproducido = true;

		}

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Fin.png").id);
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
	case PEDIR_DATOS:
		
		if (pedirDatosPaso == 0) {
			if (key == 13) { // ENTER
				if (!bufferNombre.empty()) {
					nombreJugador = bufferNombre;
					pedirDatosPaso = 1;
				}
			}
			else if (key == 8 || key == 127) { // BACKSPACE
				if (!bufferNombre.empty())
					bufferNombre.pop_back();
			}
			else if (key >= 32 && key <= 126 && bufferNombre.size() < 15) { // Caracteres imprimibles
				bufferNombre += key;
			}
		}
		else if (pedirDatosPaso == 1) {
			if (key == 97 || key == 65) { // A o a
				dificultadMaquina = (dificultadMaquina == 1) ? 3 : dificultadMaquina - 1;
			}
			else if (key == 100 || key == 68) { // D o d
				dificultadMaquina = (dificultadMaquina == 3) ? 1 : dificultadMaquina + 1;
			}
			else if (key == 13) { // ENTER
				pedirDatosPaso = 0;
				bufferNombre.clear();
				estado = JUEGO1J;
				iniciado = false;       // Para que se inicialice el mundo en el nuevo estado
			}
		}
		break;

	case JUEGO1J:
		mundo.tecla(key);				// si estamos en juego le pasa el control a mundo
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
		if (key == 27) {
			mundo.inicializa(variante);
			estado = MENU;		// volver al menu
				// reiniciar el mundo

		}
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
void Coordinador::clickRaton(int x, int y) {
	if (mundo.getEnJaqueMate()) {
		// No permitir m�s acciones
		return;
	}
	mundo.clickRaton(x, y);
}



