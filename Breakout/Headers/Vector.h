#pragma once

#include <math.h>

class Vector {
public:
	Vector(float x = 0, float y = 0) : x(x), y(y) {};

	float x, y;
	
	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	Vector operator*(const int& other);

	float dot(const Vector& other);
	float length();
	Vector normalized();
	Vector mirror(Vector axis);
};