#pragma once
#include "Vector.h"

struct Sphere
{
	Sphere() : Origin(0.f), Radius(0.f) {}
	Sphere(const Vector& Origin, float Radius) : Origin(Origin), Radius(Radius) {}

	Vector Origin;
	float Radius;
};

inline void DrawSphere(const Sphere& S, unsigned int Color = 0xFFFFFFFF)
{
	engSetColor(Color);
	engDrawSphere(S.Origin.x, S.Origin.y, S.Radius);
}