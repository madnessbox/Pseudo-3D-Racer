#pragma once
#include "Vector.h"

struct Ray
{
	static Ray FromTo(const Vector& From, const Vector& To)
	{
		return Ray(From, Normalize(To - From));
	}

	Ray() : Origin(0.f), Direction(1.f,0.f) {}
	Ray(const Vector& Origin, const Vector& Direction)
		: Origin(Origin), Direction(Direction) {}

	Vector Origin;
	Vector Direction;

	Vector GetPoint(float T) const
	{
		return Origin + Direction * T;
	}

	Vector ProjectPoint(const Vector& Point, bool* OutIsPositive = nullptr) const
	{
		float DotResult = Dot(Point - Origin, Direction);
		if(OutIsPositive != nullptr)
			*OutIsPositive = DotResult >= 0.f;
		return GetPoint(DotResult);
	}
};

inline void DrawRay(const Ray& R, unsigned int Color = 0xFFFFFFFF)
{
	Vector RayTarget = R.GetPoint(2000.f);

	engSetColor(Color);
	engDrawRect(R.Origin.x - 2, R.Origin.y - 2, 4, 4);
	engDrawLine(R.Origin.x - 2, R.Origin.y, RayTarget.x, RayTarget.y);
}