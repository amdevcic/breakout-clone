#pragma once
#include <math.h>

class Vector {
public:
	float x, y;
	Vector(float x, float y);
	Vector() : Vector(0, 0) {};
	Vector operator+(const Vector& other);
	Vector operator-(const Vector& other);
	float dot(const Vector& other);
	float const length();
	Vector normalized();
	Vector mirror(Vector axis);
};