#pragma once
#include "Vector.h"
// #include "cocos2d.h"
#include <ostream> // needed for '<<' operator overloading
#include <iostream> // iostream contains istream, and istream contains ostream


typedef class Mat4
{
public:
	Mat4();
	// right normalized vector (x), up normalized vector (y), direct, position
	Mat4(const Vector4 right, const Vector4 up, const Vector4 dir, const Vector4 pos);
	Mat4(float f0, float f1, float f2, float f3,
		   float f4, float f5, float f6, float f7,
		   float f8, float f9, float f10, float f11,
		   float f12, float f13, float f14, float f15);

	const Vector4& operator[](const int) const;
	Vector4 & operator[](const int);

	Mat4 operator+(const Mat4 &) const;
	Mat4 operator*(const Mat4 &) const; // applying two rotations to one another to create a new matrix

	Mat4 operator+=(const Mat4 &); // shortcut addition
	Mat4 operator*=(const Mat4 &); // shortcut multiplication

	Mat4 getTranspose() const;

	Vector4 col[4];

} Matrix4;

inline std::ostream& operator<<(std::ostream& os, const Matrix4& m) // takes the out stream before it (cout) and the mat4
{
	// printing it out row by row
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			os << m[column][row] << "\t";
		}

		os << "\n";
	}

	return os;
}
