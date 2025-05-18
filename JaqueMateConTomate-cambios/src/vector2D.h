#pragma once
#include <cmath>

//CLASE QUE SE ENCARGA DE LA RESOLUCION DE OPERACIONES CON VECTORES 2D
//los metodos que no se vayan a usar se borran luego
struct Vector2D
{
	double x{};
	double y{};

	//modulo de un vector
	inline double modulo() const {
		return sqrt(x * x + y * y);
	}

	//argumento
	inline double argumento() const {
		return atan2(y, x);
	}

	//vector unitario
	inline Vector2D unitario() const {
		auto mod = modulo();
		if (mod > 0.00001) return { x / mod, y / mod };
		return { x,y };
	}

	//resta de vectores
	inline Vector2D operator - (const Vector2D& v) const {
		return { x - v.x , y - v.y };
	}

	//suma de vectores
	inline Vector2D operator + (const Vector2D& v) const {
		return { x + v.x , y + v.y };
	}

	//division de vector por un escalar 
	inline Vector2D operator / (double f) const {
		return { x / f,y / f };
	}

	//producto escalar
	inline double operator * (const Vector2D& v) const {
		return  x * v.x + y * v.y;
	}

	//vector por un escalar
	inline Vector2D operator * (double f) const {
		return { x * f, y * f };
	}

	//escalar por un vector
	friend Vector2D operator * (double, const Vector2D&);
};
//escalar por un vector
inline Vector2D operator * (double f, const Vector2D& v) {
	return { v.x * f, v.y * f };
}
