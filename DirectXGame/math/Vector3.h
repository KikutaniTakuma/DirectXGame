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
	Vector3 operator+(const Vector3& vec) const;
	Vector3 operator-(const Vector3& vec) const;
	Vector3 operator+=(const Vector3& vec);
	Vector3 operator-=(const Vector3& vec);
	Vector3 operator*(float scalar) const;
	Vector3 operator*=(float scalar);
	Vector3 operator*(const Matrix4x4& mat) const;
	Vector3& operator*=(const Matrix4x4& mat);

	float Dot(const Vector3& vec) const;
	Vector3 Cross(const Vector3& vec) const;
	float Length() const;
	Vector3 Normalize() const;
};

struct Line {
	Vector3 origin;
	Vector3 diff;
};

struct Ray {
	Vector3 origin;
	Vector3 diff;
};

struct Segment {
	Vector3 origin;
	Vector3 diff;
};

Vector3 Project(const Vector3& vec1, const Vector3& vec2);

Vector3 ClosestPoint(const Vector3& point, const Segment& segment);