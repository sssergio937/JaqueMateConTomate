#pragma once
class Casilla
{
public:
    int fila, columna;
    bool noSaltarDiagonal(const Casilla& inicio, const Casilla& final) const;
};

