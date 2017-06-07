
#ifndef __NM_VECTOR_H__
#define __NM_VECTOR_H__

#include "types.h"
#include "project.h"

namespace dream
{

// 
// �x�N�g������舵���N���X�ł��B
// 
class Vector
{
protected:

	f32 x;
	f32 y;
	f32 z;

public:

	// 
	// �������w�肹���ɐ������܂��B
	// ���̏ꍇ�x�N�g�����̒l�͑S�� 0 �ɂȂ�܂��B
	// 
	explicit Vector(void);

	// 
	// �������w�肵�Đ������܂��B
	// param:
	//   x - ���Wx
	//   y - ���Wy
	//   z - ���Wz
	// 
	explicit Vector(f32 x, f32 y, f32 z);
	virtual ~Vector(void);

public:

	// ���l�̑���֐�

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

	// ���l�̉��Z�֐�

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

	// ���l�̌��Z�֐�

	RVector Sub(CRVector vector);
	RVector Sub(f32 x, f32 y, f32 z);

	// ���l�̔{���֐�

	RVector Mul(CRVector vector);
	RVector Mul(f32 x, f32 y, f32 z);

	// ���l�̕���

	RVector Copy(CRVector vector);

	// ���l�̏�����

	RVector Zero(void);

	// �w�肵���p�x�ւ̉��Z

	RVector AddAngle(f32 angle, f32 y_angle, f32 amount);
	RVector AddAngleZ(f32 angle, f32 amount);
	RVector AddAngleY(f32 angle, f32 amount);

public:

	// 
	// �x�N�g����X�̒l��Ԃ��܂��B
	// 
	f32 GetX(void) const;

	// 
	// �x�N�g����Y�̒l��Ԃ��܂��B
	// 
	f32 GetY(void) const;

	// 
	// �x�N�g����Z�̒l��Ԃ��܂��B
	// 
	f32 GetZ(void) const;

	// 
	// �x�N�g���̎l�̌ܓ����������lX�̒l��Ԃ��܂��B
	// 
	s32 GetIntX(void) const;

	// 
	// �x�N�g���̎l�̌ܓ����������lY�̒l��Ԃ��܂��B
	// 
	s32 GetIntY(void) const;

	// 
	// �x�N�g���̎l�̌ܓ����������lZ�̒l��Ԃ��܂��B
	// 
	s32 GetIntZ(void) const;

public:

	// 
	// �x�N�g���̊O�ς�Ԃ��܂��B
	// 
	Vector GetCrossProdcut(CRVector vector) const;

	// 
	// �x�N�g���̒�����Ԃ��܂��B
	// 
	f32 GetLength(void) const;

	// 
	// �x�N�g���̓��ς�Ԃ��܂��B
	// 
	Vector GetNormalize(void) const;

public:

	// 
	// �Q�̃x�N�g���v�f����l�̑傫���v�f�݂̂𒊏o�����x�N�g���N���X��Ԃ��܂��B
	// 
	static Vector GetMax(CRVector vec, CRVector vec2);

	// 
	// �Q�̃x�N�g���v�f����l�̏������v�f�݂̂𒊏o�����x�N�g���N���X��Ԃ��܂��B
	// 
	static Vector GetMin(CRVector vec, CRVector vec2);

public:

	// 
	// ���̃N���X���ێ�����v�f�𕶎���ɂ��ĕԂ��܂��B
	// 
	std::string ToString(void) const;

public:

	// 
	// �v�f�̔�r��
	// 
	bool Equals(CRVector vector) const;

	// 
	// ��_�̃x�N�g��������̈�ɂ��̃x�N�g���������Ă邩���r
	// 
	bool IsInRegion(CRVector min, CRVector max) const;

	// 
	// ��_�̃x�N�g���Ɣ��a���w�肵���̈�ɂ��̃x�N�g���������Ă��邩���r 
	//
	bool IsInRegionSphere(CRVector pos, f32 radius) const;

public:

	// 
	// �x�N�g���v�f�̈ꊇ�����
	// 
	RVector operator = (CRVector vector);

	// 
	// ��r�� ( Equals(CRVector) �֐��Ɠ��`)
	// 
	bool operator == (CRVector vector) const;

	// 
	// ��r�� ( !Equals(CRVector) �֐��Ɠ��`)
	// 
	bool operator != (CRVector vector) const;

	// 
	// ���Z�� ( Add(CRVector) �֐��Ɠ��`)
	// 
	RVector operator += (CRVector vector);

	// 
	// ���Z�� ( Sub(CRVector) �֐��Ɠ��`)
	// 
	RVector operator -= (CRVector vector);

	// 
	// �{�Z�� ( Mul(CRVector) �Ɠ��`)
	// 
	RVector operator *= (CRVector vector);

};

} // namespace dream

#endif // __NM_VECTOR_H__
