#include "Vector2D.h"

Vector2D& Vector2D::add(const Vector2D& vec) {
	this->x += vec.x;
	this->y += vec.y;

	return *this;
}

Vector2D& Vector2D::subtract(const Vector2D& vec) {
	this->x -= vec.x;
	this->y -= vec.y;

	return *this;
}

Vector2D& Vector2D::multiply(const Vector2D& vec) {
	this->x *= vec.x;
	this->y *= vec.y;

	return *this;
}

Vector2D& Vector2D::divide(const Vector2D& vec) {
	this->x /= vec.x;
	this->y /= vec.y;

	return *this;
}

Vector2D operator+(const Vector2D& v1, const Vector2D& v2) {
	Vector2D res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	return res;
}

Vector2D operator-(const Vector2D& v1, const Vector2D& v2) {
	Vector2D res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	return res;
}

Vector2D operator*(const Vector2D& v1, const Vector2D& v2) {
	Vector2D res;

	res.x = v1.x * v2.x;
	res.y = v1.y * v2.y;
	return res;
}

Vector2D operator/(const Vector2D& v1, const Vector2D& v2) {
	Vector2D res;

	res.x = v1.x / v2.x;
	res.y = v1.y / v2.y;
	return res;
}

Vector2D& Vector2D::operator+=(const Vector2D& v2) {
	return this->add(v2);
}

Vector2D& Vector2D::operator-=(const Vector2D& v2) {
	return this->subtract(v2);
}

Vector2D& Vector2D::operator*=(const Vector2D& v2) {
	return this->multiply(v2);
}

Vector2D& Vector2D::operator/=(const Vector2D& v2) {
	return this->divide(v2);
}

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
	stream << "(" << vec.x << ", " << vec.y << ")";
	return stream;
}

float Vector2D::dotProduct(const Vector2D& v1, const Vector2D& v2) const
{
	return v1.x * v2.x + v1.y * v2.y;
}

Vector2D Vector2D::getReflectedVector(const Vector2D& n) const
{
	Vector2D t;
	
	auto dotProd = this->dotProduct(*this, n);

	t.x = 2 * dotProd * n.x;
	t.y = 2 * dotProd * n.y;

	auto reflected = *this - t;

	return reflected;
}