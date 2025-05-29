#include "Mundo.h"
#include "freeglut.h"
#include <cmath>

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
            // Captura (sin comprobar color)
            Pieza* destinoPieza = tablero.getPieza(fila, columna);
            if (destinoPieza) {
                delete destinoPieza;
                tablero.setPieza(fila, columna, nullptr);  // limpia el puntero eliminado
            }

            // Movimiento
            tablero.setPieza(destino.fila, destino.columna, seleccionadaPieza);
            tablero.setPieza(seleccionada.fila, seleccionada.columna, nullptr);
            seleccionadaPieza->setPosicion(columna, fila);

            haySeleccion = false;
            cambiarTurno();

            std::cout << "Movimiento realizado\n";
        }
        else {
            haySeleccion = false;
            std::cout << "Movimiento invalido\n";
        }
    }

    glutPostRedisplay();
}