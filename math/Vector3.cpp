#include "Vector3.h"
#include <cmath>
#include "Matrix4x4.h"
#include <cassert>

Vector3::Vector3():
	x(0.0f),
	y(0.0f),
	z(0.0f)
{}

Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3 Vector3::operator+(const Vector3& vec) {
	Vector3 tmp(x + vec.x, y + vec.y, z + vec.z);

	return tmp;
}
Vector3 Vector3::operator-(const Vector3& vec) {
	Vector3 tmp(x - vec.x, y - vec.y, z - vec.z);

	return tmp;
}
Vector3 Vector3::operator+=(const Vector3& vec) {
	*this = *this + vec;

	return *this;
}
Vector3 Vector3::operator-=(const Vector3& vec) {
	*this = *this - vec;

	return *this;
}

Vector3 Vector3::operator*(float scalar) {
	Vector3 tmp(x * scalar, y * scalar, z * scalar);

	return tmp;
}
Vector3 Vector3::operator*=(float scalar) {
	*this = *this * scalar;

	return *this;
}

Vector3 Vector3::Normalize() {
	float nor = this->Length();

	return Vector3(x / nor, y / nor, z / nor);
}

Vector3 Vector3::operator*(const Matrix4x4& mat) {
	Vector3 result;

	result.x = x * mat.m[0][0] + y * mat.m[1][0] + z * mat.m[2][0] + 1.0f * mat.m[3][0];
	result.y = x * mat.m[0][1] + y * mat.m[1][1] + z * mat.m[2][1] + 1.0f * mat.m[3][1];
	result.z = x * mat.m[0][2] + y * mat.m[1][2] + z * mat.m[2][2] + 1.0f * mat.m[3][2];
	const float&& w = x * mat.m[0][3] + y * mat.m[1][3] + z * mat.m[2][3] + 1.0f * mat.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;

	return result;
}

Vector3& Vector3::operator*=(const Matrix4x4& mat) {
	*this = *this * mat;

	return *this;
}

float Vector3::Length() const {
	return sqrtf(powf(x,2.0f)+ powf(y, 2.0f)+ powf(z, 2.0f));
}

float Vector3::Dot(const Vector3& vec) {
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::Normalize() const {
	Vector3 tmp = *this;

	tmp *= 1.0f / this->Length();

	return tmp;
}