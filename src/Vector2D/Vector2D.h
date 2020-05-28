#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <iostream>

class Vector2D
{
public:
	Vector2D() : x(0), y(0) {};
	Vector2D(float x, float y) :x(x), y(y) {};

	Vector2D& add(const Vector2D& vec);
	Vector2D& subtract(const Vector2D& vec);
	Vector2D& multiply(const Vector2D& vec);
	Vector2D& divide(const Vector2D& vec);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	friend Vector2D operator+(const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator-(const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator*(const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator/(const Vector2D& v1, const Vector2D& v2);

	friend std::ostream& operator<<(std::ostream& stram, const Vector2D& vec);

	float dotProduct(const Vector2D& v, const Vector2D& n) const;
	Vector2D getReflectedVector(const Vector2D& n) const;

	float x;
	float y;
};

#endif 