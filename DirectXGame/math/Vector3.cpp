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

Vector3 Vector3::operator+(const Vector3& vec) const {
	Vector3 tmp(x + vec.x, y + vec.y, z + vec.z);

	return tmp;
}
Vector3 Vector3::operator-(const Vector3& vec) const {
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

Vector3 Vector3::operator*(float scalar) const {
	Vector3 tmp(x * scalar, y * scalar, z * scalar);

	return tmp;
}
Vector3 Vector3::operator*=(float scalar) {
	*this = *this * scalar;

	return *this;
}

Vector3 Vector3::operator*(const Matrix4x4& mat) const {
	Vector3 result;

	result.x = x * mat.get()[0][0] + y * mat.get()[1][0] + z * mat.get()[2][0] + 1.0f * mat.get()[3][0];
	result.y = x * mat.get()[0][1] + y * mat.get()[1][1] + z * mat.get()[2][1] + 1.0f * mat.get()[3][1];
	result.z = x * mat.get()[0][2] + y * mat.get()[1][2] + z * mat.get()[2][2] + 1.0f * mat.get()[3][2];
	const float&& w = x * mat.get()[0][3] + y * mat.get()[1][3] + z * mat.get()[2][3] + 1.0f * mat.get()[3][3];
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
	return sqrtf(x * x + y * y + z * z);
}

Vector3 Vector3::Normalize() const {
	float nor = this->Length();

	return Vector3(x / nor, y / nor, z / nor);
}

float Vector3::Dot(const Vector3& vec) const {
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::Cross(const Vector3& vec) const {
	Vector3 result;

	result.x = y * vec.z - z * vec.y;
	result.y = z * vec.x - x * vec.z;
	result.z = x * vec.y - y * vec.x;

	return result;
}

Vector3 Project(const Vector3& vec1, const Vector3& vec2) {
	return vec2 * (vec1.Dot(vec2) / std::pow(vec2.Length(), 2.0f));
}

Vector3 ClosestPoint(const Vector3& point, const Segment& segment) {
	return segment.origin + Project(point - segment.origin, segment.diff);
}