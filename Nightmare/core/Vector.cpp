
#include "vector.h"

namespace dream
{

Vector::Vector(void) : Vector(0.0, 0.0, 0.0)
{}

Vector::Vector(f32 x, f32 y, f32 z) : x(x), y(y), z(z)
{}

Vector::~Vector(void)
{}

RVector Vector::Set(CRVector vector)
{
	return this->Set(
		vector.x,
		vector.y,
		vector.z);
}

RVector Vector::Set(f32 x, f32 y, f32 z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	NM_RETURN_THIS;
}

RVector Vector::Add(CRVector vector)
{
	return this->Add(
		vector.x,
		vector.y,
		vector.z);
}

RVector Vector::Add(f32 x, f32 y, f32 z)
{
	this->x += x;
	this->y += y;
	this->z += z;

	NM_RETURN_THIS;
}

RVector Vector::Sub(CRVector vector)
{
	return this->Sub(
		vector.x,
		vector.y,
		vector.z);
}

RVector Vector::Sub(f32 x, f32 y, f32 z)
{
	this->x = x;
	this->y = y;
	this->z = z;

	NM_RETURN_THIS;
}

RVector Vector::Mul(CRVector vector)
{
	return this->Mul(
		vector.x,
		vector.y,
		vector.z);
}

RVector Vector::Mul(f32 x, f32 y, f32 z)
{
	this->x *= x;
	this->y *= y;
	this->z *= z;

	NM_RETURN_THIS;
}

RVector Vector::Copy(CRVector vector)
{
	this->x = vector.x;
	this->y = vector.y;
	this->z = vector.z;

	NM_RETURN_THIS;
}

RVector Vector::Zero(void)
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;

	NM_RETURN_THIS;
}

RVector Vector::AddAngle(f32 angle, f32 y_angle, f32 amount)
{

	this->x += (std::cos(angle)) * amount;
	this->z += (std::sin(angle)) * amount;
	this->y += (std::tan(y_angle)) * amount;

	NM_RETURN_THIS;
}

RVector Vector::AddAngleZ(f32 angle, f32 amount)
{
	this->x += (std::cos(angle)) * amount;
	this->z += (std::sin(angle)) * amount;

	NM_RETURN_THIS;
}

RVector Vector::AddAngleY(f32 angle, f32 amount)
{
	this->x += (std::cos(angle)) * amount;
	this->y += (std::sin(angle)) * amount;

	NM_RETURN_THIS;
}



f32 Vector::GetX(void) const
{
	return this->x;
}

f32 Vector::GetY(void) const
{
	return this->y;
}

f32 Vector::GetZ(void) const
{
	return this->z;
}


s32 Vector::GetIntX(void) const
{
	return (s32) ::round(this->GetX());
}

s32 Vector::GetIntY(void) const
{
	return (s32) ::round(this->GetY());
}

s32 Vector::GetIntZ(void) const
{
	return (s32) ::round(this->GetZ());
}

float Vector::GetLength(void) const
{
	return std::sqrt((x * x) + (y * y) + (z * z));
}

Vector Vector::GetMax(CRVector vec, CRVector vec2)
{
	Vector result;

	result.x = std::max(vec.x, vec2.x);
	result.y = std::max(vec.y, vec2.y);
	result.z = std::max(vec.z, vec2.z);

	return result;
}

Vector Vector::GetMin(CRVector vec, CRVector vec2)
{
	Vector result;

	result.x = std::min(vec.x, vec2.x);
	result.y = std::min(vec.y, vec2.y);
	result.z = std::min(vec.z, vec2.z);

	return result;
}

Vector Vector::GetCrossProdcut(CRVector vector) const
{
	f32 x = (this->y * vector.z) - (vector.y * this->z);
	f32 y = (this->z * vector.x) - (vector.z * this->x);
	f32 z = (this->x * vector.y) - (vector.x * this->y);

	return Vector(x, y, z);
}

Vector Vector::GetNormalize(void) const
{
	float length = this->GetLength();

	float x = this->x / length;
	float y = this->y / length;
	float z = this->z / length;

	return Vector(x, y, z);
}

std::string Vector::ToString(void) const
{
	std::string result;

	result += std::to_string(this->x);
	result += ", ";
	result += std::to_string(this->y);
	result += ", ";
	result += std::to_string(this->z);

	return result;
}

bool Vector::Equals(CRVector vector) const
{
	if (this->x != vector.x)
	{
		return false;
	}

	if (this->y != vector.y)
	{
		return false;
	}

	if (this->z != vector.z)
	{
		return false;
	}

	return true;
}

bool Vector::IsInRegion(CRVector min, CRVector max) const
{
	return
		(x >= min.x && x <= max.x)
		&&
		(y >= min.y && y <= max.y)
		&&
		(z >= min.z && z <= max.z);
}

bool Vector::IsInRegionSphere(CRVector pos, f32 radius) const
{
	return
		std::pow((pos.x - this->x), 2.0) +
		std::pow((pos.y - this->y), 2.0)
		<=
		std::pow(radius, 2.0);
}

RVector Vector::operator = (CRVector vector)
{
	return this->Copy(vector);
}

bool Vector::operator == (CRVector vector) const
{
	return this->Equals(vector);
}

bool Vector::operator != (CRVector vector) const
{
	return !this->Equals(vector);

}

RVector Vector::operator += (CRVector vector)
{
	return this->Add(vector);
}

RVector Vector::operator -= (CRVector vector)
{
	return this->Sub(vector);
}

RVector Vector::operator *= (CRVector vector)
{
	return this->Mul(vector);
}

} // namespace dream
