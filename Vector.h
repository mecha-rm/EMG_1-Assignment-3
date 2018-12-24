#pragma once
#include <string>

class Vector3
{
public:
	Vector3();
	Vector3(float, float);
	Vector3(float, float, float);
	
	Vector3 operator^(Vector3) const;
	Vector3 operator+(Vector3) const;
	Vector3 operator-(Vector3) const;
	Vector3 operator*(Vector3) const;
	Vector3 operator/(Vector3) const;
	
	Vector3 operator-() const;
	friend Vector3 operator-(const float, const Vector3);

	Vector3 operator+=(Vector3);
	Vector3 operator-=(Vector3);
	Vector3 operator*=(Vector3);
	Vector3 operator/=(Vector3);

	std::string toString();

	float x;
	float y;
	float z;
};


class Vector4
{
public:
	float x, y, z, w;

	// Constructors
	Vector4() = default; // creates default constructor
	Vector4(float, float, float, float);

	// one is for reading the value, the other is for editing
	const float& operator[](const int index) const;
	float& operator[](const int index);

	Vector4 operator+(const Vector4 &vec) const;
	Vector4 operator-(const Vector4 &vec) const;
	Vector4 operator*(const Vector4 &vec) const;
	Vector4 operator/(const Vector4 &vec) const;
};

