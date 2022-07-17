#include "Vector.h"

Vector Vector::operator+(const Vector& other) 
{
	return Vector(x + other.x, y + other.y);
}

Vector Vector::operator-(const Vector& other) 
{
	return Vector(x - other.x, y - other.y);
}

Vector Vector::operator*(const int& other) 
{
	return Vector(x * other, y * other);
}

float Vector::dot(const Vector& other) 
{
	return x * other.x + y * other.y;
}

float Vector::length() 
{
	return (float)sqrt(pow(x, 2) + pow(y, 2));
}

Vector Vector::normalized() 
{
	return Vector(x / length(), y / length());
}

Vector Vector::mirror(Vector axis) 
{
	return normalized() + axis.normalized() * 2;
}