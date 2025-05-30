#include "Mundo.h"
#include "freeglut.h"
#include <cmath>
#include <cstring>
#include "reina.h"
#include "torre.h"
#include "alfil.h"
#include "caballo.h"
#include <vector>
#include <cstdlib>
#include <ctime>

struct Movimiento {
    int origenFila = 0, origenCol = 0;
    int destinoFila = 0, destinoCol = 0;
    int puntos = 0;
};

std::vector<Movimiento> simularMovimientos( Tablero& tablero, Pieza::COLOR color) {

    std::vector<Movimiento> movimientosValidos;
    for (int origenFila = 0; origenFila < 5; ++origenFila) {
        for (int origenCol = 0; origenCol < 5; ++origenCol) {
            Pieza* pieza = tablero.getPieza(origenFila, origenCol);
            if (pieza && pieza->getColor() == color) {
                for (int destinoFila = 0; destinoFila < 5; ++destinoFila) {
                    for (int destinoCol = 0; destinoCol < 5; ++destinoCol) {
                        if (origenFila == destinoFila && origenCol == destinoCol)
                            continue;
                        Casilla origen(origenFila, origenCol);
                        Casilla destino(destinoFila, destinoCol);
                        Pieza* piezaDestino = tablero.getPieza(destinoFila, destinoCol);

                        // No capturar el propio rey
                        if (piezaDestino && piezaDestino->getColor() == color && piezaDestino->getPieza() == Pieza::REY)
                            continue;

                        // Comprobar si el movimiento es válido
                        if (pieza->movimiento_valido(origen, destino, tablero)) {
                            // Simular el movimiento
                            Pieza* capturada = tablero.getPieza(destinoFila, destinoCol);
                            tablero.setPieza(destinoFila, destinoCol, pieza);
                            tablero.setPieza(origenFila, origenCol, nullptr);

                            bool enJaque = tablero.reyEnJaque(color);

                            // Deshacer el movimiento
                            tablero.setPieza(origenFila, origenCol, pieza);
                            tablero.setPieza(destinoFila, destinoCol, capturada);

                            // Si no queda en jaque, es válido
                            if (!enJaque) {
                                movimientosValidos.push_back({ origenFila, origenCol, destinoFila, destinoCol });
                            }
                        }
                    }
                }
            }
        }
    }
    return movimientosValidos;
}

int evaluarTablero(const Movimiento& movimiento, Tablero& tablero, Pieza::COLOR color) {
    int puntos = 0;
    Pieza* piezaDestino = tablero.getPieza(movimiento.destinoFila, movimiento.destinoCol);

    // Penalización por capturar una pieza propia
    if (piezaDestino && piezaDestino->getColor() == color) {
        puntos -= 7; // Penaliza capturar tus propias piezas
    }

    //puntos por capturar piezas
    if (piezaDestino && piezaDestino->getColor() != color) {
        switch (piezaDestino->getPieza()) {
        case Pieza::REINA:   puntos += 9; break;
        case Pieza::TORRE:   puntos += 5; break;
        case Pieza::ALFIL:   puntos += 3; break;
        case Pieza::CABALLO: puntos += 3; break;
        case Pieza::PEON:    puntos += 1; break;
        default: break;
        }
    }
    //simular el movimiento
    Pieza* pieza = tablero.getPieza(movimiento.origenFila, movimiento.origenCol);
    Pieza* capturada = tablero.getPieza(movimiento.destinoFila, movimiento.destinoCol);
    tablero.setPieza(movimiento.destinoFila, movimiento.destinoCol, pieza);
    tablero.setPieza(movimiento.origenFila, movimiento.origenCol, nullptr);

    //se premia tener mayor movilidad 
    std::vector<Movimiento> movs = simularMovimientos(tablero, color);
    puntos += static_cast<int>(movs.size());

    //se premia controlar el centro
    if ((movimiento.destinoFila == 2 && movimiento.destinoCol == 2) ||
        (movimiento.destinoFila == 2 && movimiento.destinoCol == 1) ||
        (movimiento.destinoFila == 2 && movimiento.destinoCol == 3) ||
        (movimiento.destinoFila == 1 && movimiento.destinoCol == 2) ||
        (movimiento.destinoFila == 3 && movimiento.destinoCol == 2)) {
        puntos += 2;
    }

    //se premia la seguridad del rey
    if (tablero.reyEnJaque(color)) {
        puntos -= 20; // Penalización fuerte si el propio rey queda en jaque
    }

    //comprobar jaque y jaque mate
    Pieza::COLOR rival = (color == Pieza::VERDE) ? Pieza::ROJO : Pieza::VERDE;
    if (tablero.reyEnJaque(rival)) {
        puntos += 5; // Jaque
        if (tablero.esJaqueMate(rival)) {
            puntos += 100; // Jaque mate
        }
    }
    //comprobar si la casilla destino está defendida por una pieza del mismo color
    bool defendidaPorAliado = false;
    bool defendidaPorEnemigo = false;
    for (int f = 0; f < 5; ++f) {
        for (int c = 0; c < 5; ++c) {
            if (f == movimiento.destinoFila && c == movimiento.destinoCol)
                continue;
            Pieza* p = tablero.getPieza(f, c);
            if (p) {
                Casilla origen(f, c);
                Casilla destino(movimiento.destinoFila, movimiento.destinoCol);
                if (p->movimiento_valido(origen, destino, tablero)) {
                    if (p->getColor() == color)
                        defendidaPorAliado = true;
                    else
                        defendidaPorEnemigo = true;
                }
            }
        }
    }
    if (defendidaPorAliado)
        puntos += 2; //casilla defendida por aliado
    if (defendidaPorEnemigo)
        puntos -= 2; //casilla defendida por enemigo

    //deshacer el movimiento
    tablero.setPieza(movimiento.origenFila, movimiento.origenCol, pieza);
    tablero.setPieza(movimiento.destinoFila, movimiento.destinoCol, capturada);

    return puntos;
}

void Mundo::inicializa()
{
    tablero.inicializa_piezas();
    turno = Pieza::VERDE;
    enJaque = false;
    enJaqueMate = false;
    esperandoCoronacion = false;
    haySeleccion = false;
    mensaje[0] = '\0';
}

void Mundo::dibujarTexto(float x, float y, const char* texto)
{
    glDisable(GL_LIGHTING);              // Desactivar iluminación para que el texto se vea
    glColor3f(1.0f, 1.0f, 1.0f);         // Color blanco
    glRasterPos3f(x, y, 0.5f);           // Posición del texto

    for (const char* c = texto; *c != '\0'; ++c)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }

    glEnable(GL_LIGHTING);               // Volver a activar iluminación si era necesaria
}

void Mundo::dibuja()
{
    tablero.dibuja();
    if (turno == Pieza::VERDE)
        dibujarTexto(-3.5f, 10.5f, "TURNO: ROJAS");
    else
        dibujarTexto(-3.5f, 10.5f, "TURNO: VERDES");

    if (mensaje[0] != '\0') {
        dibujarTexto(-3.5f, 15.0f, mensaje);
    }

    if (haySeleccion) {
        int f = seleccionada.fila;
        int c = seleccionada.columna;

        float lado = 4.0f;
        float x = (c * lado) - 10.0f;           // tablero centrado en 0
        float y = 10.0f - (f + 1) * lado;       // ajustado desde arriba

        glDisable(GL_LIGHTING);
        glColor3f(1.0f, 0.0f, 0.0f);           // rojo
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
        glVertex3f(x, y, 0.21f);
        glVertex3f(x + lado, y, 0.21f);
        glVertex3f(x + lado, y + lado, 0.21f);
        glVertex3f(x, y + lado, 0.21f);
        glEnd();
        glLineWidth(1.0f);
        glEnable(GL_LIGHTING);
    }
}

void Mundo::mueve()
{

}

void Mundo::tecla(unsigned char key)
{
    if (esperandoCoronacion) {
        Pieza* nuevaPieza = nullptr;
        int f = casillaCoronacion.fila;
        int c = casillaCoronacion.columna;

        // Elimina el peón actual
        Pieza* peon = tablero.getPieza(f, c);
        if (peon) {
            delete peon;
        }

        switch (tolower(key)) {
        case 'q': // Dama
            nuevaPieza = new reina(colorCoronacion);
            break;
        case 't': // Torre
            nuevaPieza = new torre(colorCoronacion);
            break;
        case 'a': // Alfil
            nuevaPieza = new alfil(colorCoronacion);
            break;
        case 'c': // Caballo
            nuevaPieza = new caballo(colorCoronacion);
            break;
        default:
            strcpy_s(mensaje, "Tecla no valida para coronar");
            glutPostRedisplay();
            return;
        }

        if (nuevaPieza) {
            nuevaPieza->setPosicion(c, f);
            tablero.setPieza(f, c, nuevaPieza);
        }
        glutPostRedisplay();
        esperandoCoronacion = false;
        mensaje[0] = '\0';

        // Tras coronar, comprobar jaque/jaque mate
        Pieza::COLOR rival = (turno == Pieza::VERDE) ? Pieza::ROJO : Pieza::VERDE;
        enJaque = tablero.reyEnJaque(rival);
        enJaqueMate = tablero.esJaqueMate(rival);

        if (enJaqueMate) {
            strcpy_s(mensaje, "JAQUE MATE CON TOMATE");
            if (key == 27)
            {
				// Si se presiona ESC, salir del juego
				enJaqueMate=false;
				esperandoCoronacion = false;

            }
        }
        else if (enJaque) {
            strcpy_s(mensaje, "JAQUE");
        }
        else {
            mensaje[0] = '\0';
        }
        cambiarTurno();
        glutPostRedisplay();
        return;
    }
}

void Mundo::cambiarTurno()
{
    if (turno == Pieza::VERDE) {
        turno = Pieza::ROJO;  //si era el turno de las blancas, ahora es el de las negras
    }
    else {
        turno = Pieza::VERDE; //si era el turno de las negras, ahora es el de las blancas
    }
}

void Mundo::turnoMaquina(int dificultad) {
    switch (dificultad)
    {
    case 1:  //fácil, movimientos validos random
    {
        std::vector<Movimiento> movimientosValidos = simularMovimientos(tablero, Pieza::ROJO);

        //para tener numeros aleatorios
        static bool semillaInicializada = false;
        if (!semillaInicializada) {
            //numero de segundos
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            semillaInicializada = true;
        }

        //eleccion del movimiento valido random
        if (!movimientosValidos.empty()) {
            int idx = std::rand() % movimientosValidos.size();
            Movimiento mov = movimientosValidos[idx];

            Pieza* pieza = tablero.getPieza(mov.origenFila, mov.origenCol);
            Pieza* capturada = tablero.getPieza(mov.destinoFila, mov.destinoCol);
            if (capturada) delete capturada;
            tablero.setPieza(mov.destinoFila, mov.destinoCol, pieza);
            tablero.setPieza(mov.origenFila, mov.origenCol, nullptr);
            pieza->setPosicion(mov.destinoCol, mov.destinoFila);

            //coronacion para la maquina, siempre dama
            if (pieza->getPieza() == Pieza::PEON && mov.destinoFila == 4) {
               
                delete pieza;
                
                Pieza* nuevaReina = new reina(Pieza::ROJO);
                nuevaReina->setPosicion(mov.destinoCol, mov.destinoFila);
                tablero.setPieza(mov.destinoFila, mov.destinoCol, nuevaReina);
            }

            mensaje[0] = '\0';
        }
        else {
            //si no hay movimientos válidos, mostrar un mensaje
            strcpy_s(mensaje, "Rey ahogado");
        }
        break;
    }
    case 2:
    {
        //normal, basado en puntos y capaz de preveer un movimiento
       
        std::vector<Movimiento> movimientosValidos = simularMovimientos(tablero, Pieza::ROJO);

        //para tener numeros aleatorios
        static bool semillaInicializada = false;
        if (!semillaInicializada) {
            //numero de segundos
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            semillaInicializada = true;
        }

        Movimiento mejor;
        Movimiento mov;
        mejor.puntos = 0;

        //recorre todos los movimientos validos y se va quedando con el mejor
        for (const auto& mov : movimientosValidos) {
            int puntos = evaluarTablero(mov, tablero, Pieza::ROJO);
            if (puntos > mejor.puntos) {
                mejor = mov;
            }
        }

        if (mejor.puntos > 0) {
            mov = mejor;
        }
        else if (!movimientosValidos.empty()) {
            int idx = std::rand() % movimientosValidos.size();
            mov = movimientosValidos[idx];
        }
        else {
            //si no hay movimientos validos, rey ahogado
            strcpy_s(mensaje, "Rey ahogado");
            break;
        }
           
        //ejecucion del mejor movimiento
        Pieza* pieza = tablero.getPieza(mov.origenFila, mov.origenCol);
        Pieza* capturada = tablero.getPieza(mov.destinoFila, mov.destinoCol);
        if (capturada) delete capturada;
        tablero.setPieza(mov.destinoFila, mov.destinoCol, pieza);
        tablero.setPieza(mov.origenFila, mov.origenCol, nullptr);
        pieza->setPosicion(mov.destinoCol, mov.destinoFila);

        // Coronación para la máquina, siempre dama
        if (pieza->getPieza() == Pieza::PEON && mov.destinoFila == 4) {
            delete pieza;
            Pieza* nuevaReina = new reina(Pieza::ROJO);
            nuevaReina->setPosicion(mov.destinoCol, mov.destinoFila);
            tablero.setPieza(mov.destinoFila, mov.destinoCol, nuevaReina);
        }

        mensaje[0] = '\0';
        break;
       
    }
        
    case 3: //modo chungo, simula dos turnos completos
    {
        std::vector<Movimiento> movimientosMaquina = simularMovimientos(tablero, Pieza::ROJO);

        static bool semillaInicializada = false;
        if (!semillaInicializada) {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            semillaInicializada = true;
        }

        Movimiento mejor;
        mejor.puntos = 0;

        for ( auto& movMaq : movimientosMaquina) {
            //simula el movimiento de la máquina
            Pieza* piezaMaq = tablero.getPieza(movMaq.origenFila, movMaq.origenCol);
            Pieza* capturadaMaq = tablero.getPieza(movMaq.destinoFila, movMaq.destinoCol);
            tablero.setPieza(movMaq.destinoFila, movMaq.destinoCol, piezaMaq);
            tablero.setPieza(movMaq.origenFila, movMaq.origenCol, nullptr);

            //puntuacion del movimiento de la máquina
            int puntosMaquina = evaluarTablero(movMaq, tablero, Pieza::ROJO);

            //calcula todos los movimientos validos del jugador en respuesta
            std::vector<Movimiento> movimientosJugador = simularMovimientos(tablero, Pieza::VERDE);
            int peorRespuesta = 0;

            for (auto movJug : movimientosJugador) {
                //simula el movimiento del jugador
                Pieza* piezaJug = tablero.getPieza(movJug.origenFila, movJug.origenCol);
                Pieza* capturadaJug = tablero.getPieza(movJug.destinoFila, movJug.destinoCol);
                tablero.setPieza(movJug.destinoFila, movJug.destinoCol, piezaJug);
                tablero.setPieza(movJug.origenFila, movJug.origenCol, nullptr);

                int puntosJugador = evaluarTablero(movJug, tablero, Pieza::VERDE);

                //deshacer movimiento del jugador
                tablero.setPieza(movJug.origenFila, movJug.origenCol, piezaJug);
                tablero.setPieza(movJug.destinoFila, movJug.destinoCol, capturadaJug);

                if (puntosJugador > peorRespuesta)
                    peorRespuesta = puntosJugador;
            }

            //deshacer movimiento de la máquina
            tablero.setPieza(movMaq.origenFila, movMaq.origenCol, piezaMaq);
            tablero.setPieza(movMaq.destinoFila, movMaq.destinoCol, capturadaMaq);

            //valoracion final: lo que gana la máquina menos lo que puede ganar el jugador en su mejor respuesta
            movMaq.puntos = puntosMaquina - peorRespuesta;

            if (movMaq.puntos > mejor.puntos) {
                mejor = movMaq;
            }
        }

        Movimiento mov;
        if (mejor.puntos > 0) {
            mov = mejor;
        }
        else if (!movimientosMaquina.empty()) {
            int idx = std::rand() % movimientosMaquina.size();
            mov = movimientosMaquina[idx];
        }
        else {
            strcpy_s(mensaje, "Rey ahogado");
            break;
        }

        //ejecutar el mejor movimiento
        Pieza* pieza = tablero.getPieza(mov.origenFila, mov.origenCol);
        Pieza* capturada = tablero.getPieza(mov.destinoFila, mov.destinoCol);
        if (capturada) delete capturada;
        tablero.setPieza(mov.destinoFila, mov.destinoCol, pieza);
        tablero.setPieza(mov.origenFila, mov.origenCol, nullptr);
        pieza->setPosicion(mov.destinoCol, mov.destinoFila);

        //coronar para la máquina, siempre dama
        if (pieza->getPieza() == Pieza::PEON && mov.destinoFila == 4) {
            delete pieza;
            Pieza* nuevaReina = new reina(Pieza::ROJO);
            nuevaReina->setPosicion(mov.destinoCol, mov.destinoFila);
            tablero.setPieza(mov.destinoFila, mov.destinoCol, nuevaReina);
        }

        mensaje[0] = '\0';
        break;
    }
    }

    //comprobar jaque y jaque mate tras el movimiento de la máquina
    Pieza::COLOR maquina = (turno == Pieza::VERDE) ? Pieza::ROJO : Pieza::VERDE;
    enJaque = tablero.reyEnJaque(maquina);
    enJaqueMate = tablero.esJaqueMate(maquina);

    if (enJaqueMate) {
        strcpy_s(mensaje, "JAQUE MATE CON TOMATE");
        
    } else if (enJaque) {
        strcpy_s(mensaje, "JAQUE");
    } else {
        mensaje[0] = '\0';
    }

    cambiarTurno();
}

void Mundo::clickRaton(int x, int y)
{
    // Si ya hay jaque mate o esperando coronación, no permitir más acciones
    if (enJaqueMate || esperandoCoronacion) {
        return;
    }

    int ancho = glutGet(GLUT_WINDOW_WIDTH);
    int alto = glutGet(GLUT_WINDOW_HEIGHT);

    float xf = (x / (float)ancho) * 40.0f - 20.0f;
    float yf = ((alto - y) / (float)alto) * 40.0f - 20.0f;

    float lado = 4.0f;
    int columna = static_cast<int>((xf + 10.0f) / lado);
    int fila = static_cast<int>((10.0f - yf) / lado);

    if (fila < 0 || fila >= 5 || columna < 0 || columna >= 5)
    {
        haySeleccion = false;
        return;
    }

    Pieza* p = tablero.getPieza(fila, columna);

    if (!haySeleccion) {
        // PRIMER CLIC: seleccionar pieza si es del turno actual
        if (p && p->getColor() == turno)
        {
            seleccionada.fila = fila;
            seleccionada.columna = columna;
            haySeleccion = true;
        }
    }
    else {

        // SEGUNDO CLIC: intentar mover la pieza previamente seleccionada
        Casilla destino(fila, columna);
        Pieza* seleccionadaPieza = tablero.getPieza(seleccionada.fila, seleccionada.columna);

        if (seleccionadaPieza && seleccionadaPieza->movimiento_valido(seleccionada, destino, tablero))
        {
            // Guardar el estado previo
            Pieza* destinoPieza = tablero.getPieza(fila, columna);


            // --- IMPEDIR CAPTURAR TU PROPIO REY ---
            if (destinoPieza && destinoPieza->getColor() == seleccionadaPieza->getColor() && destinoPieza->getPieza() == Pieza::REY) {
                //strcpy(mensaje, "No puedes capturar tu propio rey");
                haySeleccion = false;
                glutPostRedisplay();
                return;
            }

            // Simular el movimiento
            tablero.setPieza(destino.fila, destino.columna, seleccionadaPieza);
            tablero.setPieza(seleccionada.fila, seleccionada.columna, nullptr);

            // Comprobar si el propio rey sigue en jaque tras el movimiento
            if (tablero.reyEnJaque(turno)) {
                // Deshacer el movimiento
                tablero.setPieza(seleccionada.fila, seleccionada.columna, seleccionadaPieza);
                tablero.setPieza(destino.fila, destino.columna, destinoPieza);
                //strcpy(mensaje, "Movimiento ilegal");
                haySeleccion = false;
                glutPostRedisplay();
                return;
            }

            // Si había pieza en destino, eliminarla (captura)
            if (destinoPieza) {
                delete destinoPieza;
            }

            seleccionadaPieza->setPosicion(columna, fila);
            haySeleccion = false;

            // --- CORONACIÓN ---
            // Si la pieza es un peón y ha llegado a la última fila
            if (seleccionadaPieza->getPieza() == Pieza::PEON) {
                if ((seleccionadaPieza->getColor() == Pieza::VERDE && fila == 0) ||
                    (seleccionadaPieza->getColor() == Pieza::ROJO && fila == 4)) {
                    esperandoCoronacion = true;
                    casillaCoronacion = Casilla(fila, columna);
                    colorCoronacion = seleccionadaPieza->getColor();
                    strcpy_s(mensaje, "Coronacion: Q=Dama T=Torre A=Alfil C=Caballo");
                    glutPostRedisplay();
                    return;
                }
            }

            // Determina el color del rival
            Pieza::COLOR rival = (turno == Pieza::VERDE) ? Pieza::ROJO : Pieza::VERDE;

            enJaque = tablero.reyEnJaque(rival);
            enJaqueMate = tablero.esJaqueMate(rival);

            if (enJaqueMate) {
                strcpy_s(mensaje, "JAQUE MATE CON TOMATE");

            }
            else if (enJaque) {
                strcpy_s(mensaje, "JAQUE");
            }
            else {
                mensaje[0] = '\0';
            }
            cambiarTurno();

            //std::cout << "Movimiento realizado\n";
        }
        else {
            haySeleccion = false;
            strcpy_s(mensaje, "Movimiento invalido");
            //std::cout << "Movimiento invalido\n";
        }
    }

    glutPostRedisplay();
}

/*
int evaluarTablero(const Tablero& tablero) {

    //recorre todo el tablero y lo evalua 

   

}*/
