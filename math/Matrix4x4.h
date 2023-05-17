#pragma once

#include <array>
#include <string>

static const int kRowheight = 20;
static const int kColumnWidth = 60;

class Vector3;

class Matrix4x4 final {
public:
	/// <summary>
	/// 規定コンストラクタ
	/// </summary>
	Matrix4x4();

	/// <summary>
	/// コピーコンストラクタ
	/// </summary>
	Matrix4x4(const Matrix4x4& mat);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="num"></param>
	Matrix4x4(std::array<std::array<float, 4>, 4> num);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Matrix4x4() = default;

private:
	static const int HEIGHT = 4;
	static const int WIDTH = 4;

public:
	std::array<std::array<float, 4>, 4> m;

public:
	Matrix4x4 operator*(const Matrix4x4& mat) const;
	const Matrix4x4& operator=(const Matrix4x4& mat);
	const Matrix4x4& operator*=(const Matrix4x4& mat);

	Matrix4x4 operator+(const Matrix4x4& mat) const;
	const Matrix4x4& operator+=(const Matrix4x4& mat);
	Matrix4x4 operator-(const Matrix4x4& mat) const;
	const Matrix4x4& operator-=(const Matrix4x4& mat);

	std::array<float, 4>& operator[](size_t index);

	bool operator==(const Matrix4x4& mat) const;
	bool operator!=(const Matrix4x4& mat) const;

public:
	/// <summary>
	/// 単位行列化
	/// </summary>
	void Indentity();

	/// <summary>
	/// 平行移動行列化
	/// </summary>
	/// <param name="vec">移動ベクトル</param>
	void Translate(const Vector3& vec);

	/// <summary>
	/// スカラー倍行列化
	/// </summary>
	/// <param name="vec">大きさベクトル</param>
	void Scalar(const Vector3& vec);

	/// <summary>
	/// x軸回転
	/// </summary>
	/// <param name="rad">ラジアン</param>
	void RotateX(float rad);

	/// <summary>
	/// y軸回転
	/// </summary>
	/// <param name="rad">ラジアン</param>
	void RotateY(float rad);

	/// <summary>
	/// z軸回転
	/// </summary>
	/// <param name="rad">ラジアン</param>
	void RotateZ(float rad);

	/// <summary>
	/// アフィン
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <param name="rad">ラジアン</param>
	/// <param name="translate">平行移動</param>
	void Affin(const Vector3& scale, const Vector3& rad, const Vector3& translate);

	/// <summary>
	/// 逆行列化
	/// </summary>
	void Inverse();

	/// <summary>
	/// 転置行列化
	/// </summary>
	void Transepose();
};


/// <summary>
/// 単位行列
/// </summary>
/// <returns>単位行列を返す</returns>
Matrix4x4 MakeMatrixIndentity();

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="vec">移動ベクトル</param>
/// <returns>平行移動行列を返す</returns>
Matrix4x4 MakeMatrixTranslate(Vector3 vec);

/// <summary>
/// スカラー倍行列
/// </summary>
/// <param name="vec">大きさベクトル</param>
/// <returns>スカラー倍行列を返す</returns>
Matrix4x4 MakeMatrixScalar(Vector3 vec);

/// <summary>
/// x軸回転
/// </summary>
/// <param name="rad">ラジアン</param>
/// <returns>x軸回転した行列</returns>
Matrix4x4 MakeMatrixRotateX(float rad);

/// <summary>
/// y軸回転
/// </summary>
/// <param name="rad">ラジアン</param>
/// <returns>y軸回転した行列</returns>
Matrix4x4 MakeMatrixRotateY(float rad);

/// <summary>
/// z軸回転
/// </summary>
/// <param name="rad">ラジアン</param>
/// <returns>z軸回転した行列</returns>
Matrix4x4 MakeMatrixRotateZ(float rad);

/// <summary>
/// アフィン
/// </summary>
/// <param name="scale">スケール</param>
/// <param name="rad">ラジアン</param>
/// <param name="translate">平行移動</param>
Matrix4x4 MakeMatrixAffin(const Vector3& scale, const Vector3& rad, const Vector3& translate);


/// <summary>
/// 逆行列
/// <para>失敗したら引数の行列を返す</para>
/// </summary>
/// <param name="mat">逆行列にしたい行列</param>
/// <returns>引数の逆行列</returns>
Matrix4x4 MakeMatrixInverse(Matrix4x4 mat);

/// <summary>
/// 転置行列
/// </summary>
/// <param name="mat">転置行列にしたい行列</param>
/// <returns>引数の転置行列</returns>
Matrix4x4 MakeMatrixTransepose(Matrix4x4 mat);