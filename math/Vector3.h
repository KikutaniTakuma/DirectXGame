#pragma once
#include <string>

class Matrix4x4;

class Vector3 {
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& vec) = default;

public:
	float x;
	float y;
	float z;

public:
	Vector3& operator=(const Vector3& vec) = default;
	Vector3 operator+(const Vector3& vec);
	Vector3 operator-(const Vector3& vec);
	Vector3 operator+=(const Vector3& vec);
	Vector3 operator-=(const Vector3& vec);
	Vector3 operator*(float scalar);
	Vector3 operator*=(float scalar);
	Vector3 Normalize();
	Vector3 operator*(const Matrix4x4& mat);
	Vector3& operator*=(const Matrix4x4& mat);

	float Dot(const Vector3& vec);
	float Length();
};