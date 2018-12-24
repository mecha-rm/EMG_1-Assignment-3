#include "Vector.h"
#include <cmath>

// Vector3
// Consturctors
Vector3::Vector3()
{
	x = 0.0f;
	y = 0.0f;
	// z(0.0f) doesn't work. Expression perceeding paranthesis must have (ponter-to) function type.
	z = 0.0f;
}

Vector3::Vector3(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

// Math Operations
Vector3 Vector3::operator^(Vector3 vec) const
{
	Vector3 vec2 = vec;
	vec2.x = pow(x, vec.x);
	vec2.y = pow(y, vec.y);
	vec2.z = pow(z, vec.z);

	return vec2;
}

Vector3 Vector3::operator*(Vector3 vec) const
{
	Vector3 vec2 = vec;
	vec2.x = x * vec.x;
	vec2.y = y * vec.y;
	vec2.z = z * vec.z;

	return vec2;
}

Vector3 Vector3::operator/(Vector3 vec) const
{
	Vector3 vec2 = vec;
	vec2.x = x / vec.x;
	vec2.y = y / vec.y;
	vec2.z = z / vec.z;

	return vec2;
}

Vector3 Vector3::operator+(Vector3 vec) const
{
	Vector3 vec2 = vec;
	vec2.x = x + vec.x;
	vec2.y = y + vec.y;
	vec2.z = z + vec.z;

	return vec2;
}

Vector3 Vector3::operator-(Vector3 vec) const
{
	Vector3 vec2 = vec;
	vec2.x = x - vec.x;
	vec2.y = y - vec.y;
	vec2.z = z - vec.z;

	return vec2;
}

Vector3 operator-(const float a, const Vector3 b)
{
	Vector3 temp;
	temp.x = a - b.x;
	temp.y = a - b.y;
	temp.z = a - b.z;

	return temp;
}

Vector3 Vector3::operator-() const
{
	return 0.0f - *this;
}


std::string Vector3::toString()
{
	std::string str;
	// std::string str = "x: " + x;
	return str;
}


// Vector3 4 class
// Vector4::Vector4() {}


Vector4::Vector4(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

Vector3 Vector3::operator+=(Vector3 v3)
{
	return *this = *this + v3;
}

Vector3 Vector3::operator-=(Vector3 v3)
{
	return *this = *this - v3;
}

Vector3 Vector3::operator*=(Vector3 v3)
{
	return *this = *this * v3;
}

Vector3 Vector3::operator/=(Vector3 v3)
{
	return *this = *this / v3;
}


const float& Vector4::operator[](const int index) const
{
	// Since all of the variables are sequential in memory, offsetting the location of 'x' by the index will provide the other variables
	return(&x)[index]; // returning the location of 'x', offset by our index.
}


float& Vector4::operator[](const int index)
{
	// Since all of the variables are sequential in memory, offsetting the location of 'x' by the index will provide the other variables
	return(&x)[index]; // returning the location of 'x', offset by our index.
}

// operators
Vector4 Vector4::operator+(const Vector4 &vec) const
{
	return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
}

Vector4 Vector4::operator-(const Vector4 &vec) const
{
	return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
}

Vector4 Vector4::operator*(const Vector4 &vec) const
{
	return Vector4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
}

Vector4 Vector4::operator/(const Vector4 &vec) const
{
	return Vector4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
}