#include "Mundo.h"
#include "freeglut.h"
#include <cmath>
#include <cstring>
#include "reina.h"
#include "torre.h"
#include "alfil.h"
#include "caballo.h"

void Mundo::inicializa()
{
    //tablero.inicializa_piezas();
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
            strcpy(mensaje, "Tecla no valida para coronar");
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
            strcpy(mensaje, "JAQUE MATE CON TOMATE");
        }
        else if (enJaque) {
            strcpy(mensaje, "JAQUE");
        }
        else {
            mensaje[0] = '\0';
        }
        cambiarTurno();
        glutPostRedisplay();
        return;
    }

    // Aquí puedes añadir el resto de controles de teclado si los tienes
}

void Mundo::cambiarTurno()
{
    if (turno == Pieza::VERDE) {
        turno = Pieza::ROJO;  // Si era el turno de las blancas, ahora es el de las negras
    }
    else {
        turno = Pieza::VERDE; // Si era el turno de las negras, ahora es el de las blancas
    }
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
        Pieza* destinoPieza = tablero.getPieza(fila, columna);

        // --- IMPEDIR CAPTURAR TU PROPIO REY ---
        if (destinoPieza && destinoPieza->getColor() == seleccionadaPieza->getColor() && destinoPieza->getPieza() == Pieza::REY) {
            strcpy(mensaje, "No puedes capturar tu propio rey");
            haySeleccion = false;
            glutPostRedisplay();
            return;
        }

        if (seleccionadaPieza && seleccionadaPieza->movimiento_valido(seleccionada, destino, tablero))
        {
            // Guardar el estado previo
            Pieza* destinoPieza = tablero.getPieza(fila, columna);

            // Simular el movimiento
            tablero.setPieza(destino.fila, destino.columna, seleccionadaPieza);
            tablero.setPieza(seleccionada.fila, seleccionada.columna, nullptr);

            // Comprobar si el propio rey sigue en jaque tras el movimiento
            if (tablero.reyEnJaque(turno)) {
                // Deshacer el movimiento
                tablero.setPieza(seleccionada.fila, seleccionada.columna, seleccionadaPieza);
                tablero.setPieza(destino.fila, destino.columna, destinoPieza);
                strcpy(mensaje, "Movimiento ilegal");
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
                    strcpy(mensaje, "Coronacion: Q=Dama T=Torre A=Alfil C=Caballo");
                    glutPostRedisplay();
                    return;
                }
            }

            // Determina el color del rival
            Pieza::COLOR rival = (turno == Pieza::VERDE) ? Pieza::ROJO : Pieza::VERDE;

            enJaque = tablero.reyEnJaque(rival);
            enJaqueMate = tablero.esJaqueMate(rival);

            if (enJaqueMate) {
                strcpy(mensaje, "JAQUE MATE CON TOMATE");
            }
            else if (enJaque) {
                strcpy(mensaje, "JAQUE");
            }
            else {
                mensaje[0] = '\0';
            }
            cambiarTurno();

            std::cout << "Movimiento realizado\n";
        }
        else {
            haySeleccion = false;
            strcpy(mensaje, "Movimiento invalido");
            std::cout << "Movimiento invalido\n";
        }
    }

    glutPostRedisplay();
}
