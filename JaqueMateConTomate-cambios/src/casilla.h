#pragma once
class Casilla
{
public:
    int fila=0, columna=0;
    Casilla() {};
   static bool noSaltarDiagonal(const Casilla& inicio, const Casilla& final) const;
   static bool mlineal(const Casilla& inicio, const Casilla & final) const;
   static bool mDiagonal(const Casilla& inicio,const Casilla& fin)const;
   static bool movRey(const Casilla& inicio,const Casilla& fin)const;
   static bool movPeonBlanco(const Casilla& inicio,const Casilla& fin)const;
   static bool movPeonNegro(const Casilla& inicio, const Casilla& fin)const;
   static bool comerPeonBlanco(const Casilla& inicio, const Casilla& fin)const;
   static bool comerPeonNegro(const Casilla& inicio, const Casilla& fin)const;
   static bool movAlfil(const Casilla& inicio, const Casilla& fin)const;
   static bool movCaballo(const Casilla& inicio, const Casilla& fin)const;
   static bool movTorre(const Casilla& inicio, const Casilla& fin)const;
   static bool movReina(const Casilla& inicio, const Casilla& fin)const;
   // no se permite el avance de dos casillas para los peones en este modo de juego
   static bool fueraTablero(const Casilla& c)const;
};

