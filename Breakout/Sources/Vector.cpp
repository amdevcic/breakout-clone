#include "Vector.h"

Vector::Vector(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector Vector::operator+(const Vector& other) {
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) {
	return Vector(x - other.x, y - other.y);
}

float Vector::dot(const Vector& other) {
	return x * other.x + y * other.y;
}

float const Vector::length() {
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vector Vector::normalized() {
	return Vector(x / length(), y / length());
}

Vector Vector::mirror(Vector axis) {
	return normalized() + axis.normalized() + axis.normalized();
}