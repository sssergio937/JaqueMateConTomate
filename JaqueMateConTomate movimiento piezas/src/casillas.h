#pragma once
class Casilla
{
public:
    int fila = 0, columna = 0;
    Casilla() {};
    static bool noSaltarDiagonal(Casilla inicio, Casilla fin);
    static bool mlineal(Casilla inicio, Casilla  final);
    static bool mDiagonal(Casilla inicio, Casilla fin);
    static bool movRey(Casilla inicio, Casilla fin);
    static bool movPeonBlanco(Casilla inicio, Casilla fin);
    static bool movPeonNegro(Casilla inicio, Casilla fin);
    static bool comerPeonBlanco(Casilla inicio, Casilla fin);
    static bool comerPeonNegro(Casilla inicio, Casilla fin);
    static bool movAlfil(Casilla inicio, Casilla fin);
    static bool movCaballo(Casilla inicio, Casilla fin);
    static bool movTorre(Casilla inicio, Casilla fin);
    static bool movReina(Casilla inicio, Casilla fin);
    // no se permite el avance de dos casillas para los peones en este modo de juego
    static bool fueraTablero(Casilla c);
};

