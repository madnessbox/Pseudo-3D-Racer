#pragma once
#include <math.h>
#include "TinyEngine.h"

class Vector
{
public:
	Vector() : x(0), y(0) {}
	Vector(float scalar) : x(scalar), y(scalar) {}
	Vector(float x, float y) : x(x), y(y) {}

	Vector operator+(Vector otherVec) const
	{
		return(Vector(x + otherVec.x, y + otherVec.y));
	}
	Vector operator-(Vector otherVec) const
	{
		return(Vector(x - otherVec.x, y - otherVec.y));
	}
	Vector operator*(float scalar) const
	{
		return(Vector(x * scalar, y * scalar));
	}
	Vector operator/(float scalar) const
	{
		return Vector(x / scalar, y / scalar);
	}
	Vector operator+() const
	{
		return Vector(x, y);
	}
	Vector operator-() const
	{
		return Vector(-x, -y);
	}

	Vector& operator+=(const Vector& otherVec)
	{
		*this = *this + otherVec; 
		return *this;
	}
	Vector& operator-=(const Vector& otherVec)
	{
		*this = *this - otherVec; 
		return *this;
	}
	Vector& operator*=(float scalar)
	{
		*this = *this * scalar; 
		return *this;
	}
	Vector& operator/=(float scalar)
	{
		*this = *this / scalar; 
		return *this;
	}
	

	float x, y;
};

inline float Length(Vector vec)
{
	float lengthSqrd = (vec.x * vec.x + vec.y * vec.y);
	return sqrt(lengthSqrd);
}

inline Vector Normalize(Vector vec)
{
	return vec / Length(vec);
}

inline float Dot(const Vector& A, const Vector& B)
{
	return(A.x * B.x + A.y * B.y);
}

inline void DrawVector(Vector vec, unsigned int color = 0xFFFFFFFF)
{
	engSetColor(color);
	engDrawLine(0, 0, vec.x, vec.y);
	engDrawRect(vec.x - 2, vec.y - 2, 7, 7);
	engSetColor(0xFFFFFFFF);
}

inline void DrawVectorFrom(Vector vec, Vector source, unsigned int color = 0xFFFFFFFF)
{
	engSetColor(color);
	engDrawLine(source.x, source.y, vec.x + source.x, vec.y + source.y);
	engDrawRect(vec.x + source.x - 2, vec.y + source.y - 2, 7, 7);
}
