#include "Matrix4x4.h"
#include "Vector3.h"
#include <cmath>
#include <algorithm>


Matrix4x4::Matrix4x4()
	:m({ 0.0f })
{}

Matrix4x4::Matrix4x4(const Matrix4x4& mat) {
	*this = mat;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mat) const{
	Matrix4x4 tmp;

	for (int y = 0; y < Matrix4x4::HEIGHT; y++) {
		for (int x = 0; x < Matrix4x4::WIDTH; x++) {
			for (int i = 0; i < Matrix4x4::WIDTH; i++) {
				tmp.m[y][x] += this->m[y][i] * mat.m[i][x];
			}
		}
	}

	return tmp;
}

Matrix4x4::Matrix4x4(std::array<std::array<float, 4>, 4> num) {
	m = num;
}

const Matrix4x4& Matrix4x4::operator=(const Matrix4x4& mat) {
	this->m = mat.m;

	return *this;
}

const Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& mat) {
	*this = *this * mat;

	return *this;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& mat) const {
	Matrix4x4 tmp;

	for (int y = 0; y < Matrix4x4::HEIGHT; y++) {
		for (int x = 0; x < Matrix4x4::WIDTH; x++) {
			tmp[y][x] = this->m[y][x] + mat.m[y][x];
		}
	}

	return tmp;
}
const Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& mat) {
	for (int y = 0; y < Matrix4x4::HEIGHT; y++) {
		for (int x = 0; x < Matrix4x4::WIDTH; x++) {
			this->m[y][x] += mat.m[y][x];
		}
	}

	return *this;
}
Matrix4x4 Matrix4x4::operator-(const Matrix4x4& mat) const {
	Matrix4x4 tmp;

	for (int y = 0; y < Matrix4x4::HEIGHT; y++) {
		for (int x = 0; x < Matrix4x4::WIDTH; x++) {
			tmp[y][x] = this->m[y][x] - mat.m[y][x];
		}
	}

	return tmp;
}
const Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& mat) {
	for (int y = 0; y < Matrix4x4::HEIGHT; y++) {
		for (int x = 0; x < Matrix4x4::WIDTH; x++) {
			this->m[y][x] -= mat.m[y][x];
		}
	}

	return *this;
}

std::array<float, 4>& Matrix4x4::operator[](size_t index) {
	return m[index];
}

bool Matrix4x4::operator==(const Matrix4x4& mat) const {
	return m == mat.m;
}

bool Matrix4x4::operator!=(const Matrix4x4& mat) const {
	return m != mat.m;
}

void Matrix4x4::Indentity() {
	m = { 0.0f };

	for (int i = 0; i < WIDTH; i++) {
		m[i][i] = 1.0f;
	}
}

void Matrix4x4::Translate(const Vector3& vec) {
	this->m = { 0.0f };

	this->m[0][0] = 1.0f;
	this->m[1][1] = 1.0f;
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;

	this->m[3][0] = vec.x;
	this->m[3][1] = vec.y;
	this->m[3][2] = vec.z;
}

void Matrix4x4::Scalar(const Vector3& vec) {
	this->m = { 0.0f };

	this->m[0][0] = vec.x;
	this->m[1][1] = vec.y;
	this->m[2][2] = vec.z;
	this->m[3][3] = 1.0f;
}

void Matrix4x4::RotateX(float rad) {
	this->m = { 0.0f };
	this->m[0][0] = 1.0f;
	this->m[3][3] = 1.0f;

	this->m[1][1] = std::cos(rad);
	this->m[1][2] = std::sin(rad);
	this->m[2][1] = -std::sin(rad);
	this->m[2][2] = std::cos(rad);
}

void Matrix4x4::RotateY(float rad) {
	this->m = { 0.0f };
	this->m[1][1] = 1.0f;
	this->m[3][3] = 1.0f;

	this->m[0][0] = std::cos(rad);
	this->m[0][2] = -std::sin(rad);
	this->m[2][0] = std::sin(rad);
	this->m[2][2] = std::cos(rad);
}

void Matrix4x4::RotateZ(float rad) {
	this->m = { 0.0f };
	this->m[2][2] = 1.0f;
	this->m[3][3] = 1.0f;
	
	this->m[0][0] = std::cos(rad);
	this->m[0][1] = std::sin(rad);
	this->m[1][0] = -std::sin(rad);
	this->m[1][1] = std::cos(rad);
}


void Matrix4x4::Affin(const Vector3& scale, const Vector3& rad, const Vector3& translate) {
	Matrix4x4 rotate = MakeMatrixRotateX(rad.x) * MakeMatrixRotateY(rad.y) * MakeMatrixRotateZ(rad.z);

	*this = Matrix4x4({
		scale.x * rotate.m[0][0], scale.x * rotate.m[0][1],scale.x * rotate.m[0][2], 0.0f,
		scale.y * rotate.m[1][0], scale.y * rotate.m[1][1],scale.y * rotate.m[1][2], 0.0f,
		scale.z * rotate.m[2][0], scale.z * rotate.m[2][1],scale.z * rotate.m[2][2], 0.0f,
		translate.x, translate.y, translate.z, 1.0f
		});
}


void Matrix4x4::Inverse() {
	//一時保存用
	Matrix4x4 tmp = *this;

	//単位行列
	Matrix4x4 identity = MakeMatrixIndentity();

	// pibotを1にするためのバッファ
	float toOne = *(tmp.m.begin()->begin());

	// 見ている行の一部の値を0.0fにするためのバッファ(0除算が発生しないように初期化は1.0fで行う)
	float tmpNum = 0.0f;

	// 掃き出し法
	for (int i = 0; i < Matrix4x4::HEIGHT; i++) {
		// ピボット選択
		if (tmp.m[i][i] == 0.0f && i < Matrix4x4::HEIGHT) {
			// 行要素番号バッファ
			int pibIndex = i;
			// ピボットバッファ
			float pibot = fabsf(tmp.m[i][i]);

			// ピボット設定
			for (int y = i + 1; y < Matrix4x4::HEIGHT; y++) {
				if (tmp.m[y][i] != 0.0f && pibot < fabsf(tmp.m[y][i])) {
					pibot = fabsf(tmp.m[y][i]);
					pibIndex = y;
				}
			}

			//ピボットが0だった場合逆行列は存在しないので処理終了
			if (pibot == 0.0f) {
				return;
			}

			// 見てる値が0だったらその行を見ている値の列で絶対値の一番高い行と交換
			tmp.m[i].swap(tmp.m[pibIndex]);
			identity.m[i].swap(identity.m[pibIndex]);
		}

		// tmpを単位行列に近づけるために見ている要素の行を見ている要素で割る
		toOne = tmp.m[i][i];
		for (int x = 0; x < Matrix4x4::HEIGHT; x++) {
			tmp.m[i][x] /= toOne;
			identity.m[i][x] /= toOne;
		}

		// tmpの見ている列を単位行列に近づけるための処理
		for (int y = 0; y < Matrix4x4::HEIGHT; ++y) {
			if (i == y) {
				continue;
			}

			tmpNum = -tmp.m[y][i];
			for (int x = 0; x < Matrix4x4::WIDTH; x++) {
				tmp.m[y][x] += tmpNum * tmp.m[i][x];
				identity.m[y][x] += tmpNum * identity.m[i][x];
			}
		}
	}

	// tmpが単位行列になっていない場合失敗なので処理終了
	if (tmp != MakeMatrixIndentity()) {
		return;
	}

	// 逆行列にした行列を代入
	*this = identity;


	/// 苦労した割にはすっきりしないプログラムでつらい
}


void Matrix4x4::Transepose() {
	std::swap(m[1][0], m[0][1]);
	std::swap(m[2][0], m[0][2]);
	std::swap(m[3][0], m[0][3]);
	std::swap(m[2][1], m[1][2]);
	std::swap(m[2][3], m[3][2]);
	std::swap(m[3][1], m[1][3]);
}


Matrix4x4 MakeMatrixIndentity() {
	Matrix4x4 tmp;
	tmp.Indentity();
	return tmp;
}

Matrix4x4 MakeMatrixInverse(Matrix4x4 mat) {
	Matrix4x4 tmp = mat;
	tmp.Inverse();
	return tmp;
}

Matrix4x4 MakeMatrixTransepose(Matrix4x4 mat) {
	Matrix4x4 tmp = mat;
	tmp.Transepose();
	return tmp;
}

Matrix4x4 MakeMatrixTranslate(Vector3 vec) {
	Matrix4x4 mat;

	mat.Translate(vec);

	return mat;
}

Matrix4x4 MakeMatrixScalar(Vector3 vec) {
	Matrix4x4 mat;

	mat.Scalar(vec);

	return mat;
}

Matrix4x4 MakeMatrixRotateX(float rad) {
	Matrix4x4 tmp;

	tmp.RotateX(rad);

	return tmp;
}

Matrix4x4 MakeMatrixRotateY(float rad) {
	Matrix4x4 tmp;

	tmp.RotateY(rad);

	return tmp;
}

Matrix4x4 MakeMatrixRotateZ(float rad) {
	Matrix4x4 tmp;

	tmp.RotateZ(rad);

	return tmp;
}

Matrix4x4 MakeMatrixAffin(const Vector3& scale, const Vector3& rad, const Vector3& translate) {
	Matrix4x4 tmp;

	tmp.Affin(scale, rad, translate);

	return tmp;
}