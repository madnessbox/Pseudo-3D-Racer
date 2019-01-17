#pragma once
#include "MathUtils.h"

class Vector3
{
public:
	Vector3() : X(0), Y(0), Z(0) {}
	Vector3(float Scalar) : X(Scalar), Y(Scalar), Z(Scalar) {}
	Vector3(float X, float Y, float Z) : X(Y), Y(Y), Z(Z) {}

	Vector3 operator+(Vector3 OtherVec) const
	{
		return(Vector3(X + OtherVec.X, Y + OtherVec.Y, Z + OtherVec.Z));
	}
	Vector3 operator-(Vector3 OtherVec) const
	{
		return(Vector3(X - OtherVec.X, Y - OtherVec.Y, Z - OtherVec.Z));
	}
	Vector3 operator*(float Scalar) const
	{
		return(Vector3(X * Scalar, Y * Scalar, Z * Scalar));
	}
	Vector3 operator/(float Scalar) const
	{
		return Vector3(X / Scalar, Y / Scalar, Z / Scalar);
	}
	Vector3 operator+() const
	{
		return Vector3(X, Y, Z);
	}
	Vector3 operator-() const
	{
		return Vector3(-X, -Y, -Z);
	}

	Vector3& operator+=(const Vector3& OtherVec)
	{
		*this = *this + OtherVec;
		return *this;
	}
	Vector3& operator-=(const Vector3& OtherVec)
	{
		*this = *this - OtherVec;
		return *this;
	}
	Vector3& operator*=(float Scalar)
	{
		*this = *this * Scalar;
		return *this;
	}
	Vector3& operator/=(float Scalar)
	{
		*this = *this / Scalar;
		return *this;
	}

	inline float Length(Vector3 Vec)
	{
		float LengthSqrd = (Vec.X * Vec.X + Vec.Y * Vec.Y + Vec.Z * Vec.Z);
		return sqrt(LengthSqrd);
	}
	inline Vector3 Normalize(Vector3 Vec)
	{
		return Vec / Length(Vec);
	}
	inline float Dot2D(const Vector3& A, const Vector3& B)
	{
		return(A.X * B.X + A.Y * B.Y);
	}
	inline float Dot3D(const Vector3& A, const Vector3& B)
	{
		return(A.X * B.X + A.Y * B.Y + A.Z * B.Z);
	}

	float X, Y, Z;
};