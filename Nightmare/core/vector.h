
#ifndef __NM_VECTOR_H__
#define __NM_VECTOR_H__

#include "types.h"
#include "project.h"

namespace dream
{

// 
// ベクトルを取り扱うクラスです。
// 
class Vector
{
protected:

	f32 x;
	f32 y;
	f32 z;

public:

	// 
	// 引数を指定せずに生成します。
	// この場合ベクトル内の値は全て 0 になります。
	// 
	explicit Vector(void);

	// 
	// 引数を指定して生成します。
	// param:
	//   x - 座標x
	//   y - 座標y
	//   z - 座標z
	// 
	explicit Vector(f32 x, f32 y, f32 z);
	virtual ~Vector(void);

public:

	// 数値の代入関数

	RVector Set(CRVector vector);
	RVector Set(f32 x, f32 y, f32 z);

	RVector SetX(f32 x)
	{
		this->x = x; NM_RETURN_THIS;
	}
	RVector SetY(f32 y)
	{
		this->y = y; NM_RETURN_THIS;
	}
	RVector SetZ(f32 z)
	{
		this->z = z; NM_RETURN_THIS;
	}

	// 数値の加算関数

	RVector Add(CRVector vector);
	RVector Add(f32 x, f32 y, f32 z);

	RVector AddX(f32 x)
	{
		this->x += x; NM_RETURN_THIS;
	}
	RVector AddY(f32 y)
	{
		this->y += y; NM_RETURN_THIS;
	}
	RVector AddZ(f32 z)
	{
		this->z += z; NM_RETURN_THIS;
	}

	// 数値の減算関数

	RVector Sub(CRVector vector);
	RVector Sub(f32 x, f32 y, f32 z);

	// 数値の倍数関数

	RVector Mul(CRVector vector);
	RVector Mul(f32 x, f32 y, f32 z);

	// 数値の複製

	RVector Copy(CRVector vector);

	// 数値の初期化

	RVector Zero(void);

	// 指定した角度への加算

	RVector AddAngle(f32 angle, f32 y_angle, f32 amount);
	RVector AddAngleZ(f32 angle, f32 amount);
	RVector AddAngleY(f32 angle, f32 amount);

public:

	// 
	// ベクトルのXの値を返します。
	// 
	f32 GetX(void) const;

	// 
	// ベクトルのYの値を返します。
	// 
	f32 GetY(void) const;

	// 
	// ベクトルのZの値を返します。
	// 
	f32 GetZ(void) const;

	// 
	// ベクトルの四捨五入した整数値Xの値を返します。
	// 
	s32 GetIntX(void) const;

	// 
	// ベクトルの四捨五入した整数値Yの値を返します。
	// 
	s32 GetIntY(void) const;

	// 
	// ベクトルの四捨五入した整数値Zの値を返します。
	// 
	s32 GetIntZ(void) const;

public:

	// 
	// ベクトルの外積を返します。
	// 
	Vector GetCrossProdcut(CRVector vector) const;

	// 
	// ベクトルの長さを返します。
	// 
	f32 GetLength(void) const;

	// 
	// ベクトルの内積を返します。
	// 
	Vector GetNormalize(void) const;

public:

	// 
	// ２つのベクトル要素から値の大きい要素のみを抽出したベクトルクラスを返します。
	// 
	static Vector GetMax(CRVector vec, CRVector vec2);

	// 
	// ２つのベクトル要素から値の小さい要素のみを抽出したベクトルクラスを返します。
	// 
	static Vector GetMin(CRVector vec, CRVector vec2);

public:

	// 
	// このクラスが保持する要素を文字列にして返します。
	// 
	std::string ToString(void) const;

public:

	// 
	// 要素の比較式
	// 
	bool Equals(CRVector vector) const;

	// 
	// 二点のベクトルから作る領域にこのベクトルが入ってるかを比較
	// 
	bool IsInRegion(CRVector min, CRVector max) const;

	// 
	// 一点のベクトルと半径を指定した領域にこのベクトルが入っているかを比較 
	//
	bool IsInRegionSphere(CRVector pos, f32 radius) const;

public:

	// 
	// ベクトル要素の一括代入式
	// 
	RVector operator = (CRVector vector);

	// 
	// 比較式 ( Equals(CRVector) 関数と同義)
	// 
	bool operator == (CRVector vector) const;

	// 
	// 比較式 ( !Equals(CRVector) 関数と同義)
	// 
	bool operator != (CRVector vector) const;

	// 
	// 加算式 ( Add(CRVector) 関数と同義)
	// 
	RVector operator += (CRVector vector);

	// 
	// 減算式 ( Sub(CRVector) 関数と同義)
	// 
	RVector operator -= (CRVector vector);

	// 
	// 倍算式 ( Mul(CRVector) と同義)
	// 
	RVector operator *= (CRVector vector);

};

} // namespace dream

#endif // __NM_VECTOR_H__
