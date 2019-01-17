#pragma once
#include "Vector.h"

struct Plane
{
	Plane() : Point(0.f), Normal(1.f, 0.f) {}
	Plane(const Vector& Point, const Vector& Normal) 
		: Point(Point), Normal(Normal) {}

	Vector Point;
	Vector Normal;

	float DistanceToPoint(const Vector& OtherPoint) const
	{
		return Dot(OtherPoint - Point, Normal);
	}

	Vector ProjectPoint(const Vector& OtherPoint, bool* OutIsPositive = nullptr) const
	{
		float NormalDot = Dot(OtherPoint - Point, Normal);
		if(OutIsPositive != nullptr)
			*OutIsPositive = NormalDot >= 0.f;

		Vector NormalProjection = Normal * NormalDot;
		return OtherPoint - NormalProjection;
	}
};

inline void DrawPlane(const Plane& P, unsigned int Color = 0xFFFFFFFF)
{
	engSetColor(Color);

	Vector PlanePerpendicular(-P.Normal.y, P.Normal.x);
	Vector MinusInf = P.Point + PlanePerpendicular * 2000.f;
	Vector PlusInf = P.Point - PlanePerpendicular * 2000.f;

	Vector PointNormal = P.Point + P.Normal * 40.f;

	engDrawLine(MinusInf.x, MinusInf.y, PlusInf.x, PlusInf.y);
	engSetColor(0x0000FFFF);
	engDrawLine(P.Point.x, P.Point.y, PointNormal.x, PointNormal.y);
}
