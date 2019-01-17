#pragma once
#include "Vector.h"
#include "Sphere.h"
#include "Ray.h"
#include "Plane.h"
#include <cstdlib>
#define TAU 6.28318530718f

inline float Rad2Deg(float Rad)
{
	return (Rad / TAU) * 360.f;
}

inline float Deg2Rad(float Deg)
{
	return (Deg / 360.f) * TAU;
}

inline Vector PerpLeft(const Vector& V)
{
	return Vector(-V.y, V.x);
}

inline Vector PerpRight(const Vector& V)
{
	return Vector(V.y, -V.x);
}

inline Vector RotateVector(const Vector& VectorToRotate, float Angle)
{
	Vector Perpendicular = PerpLeft(VectorToRotate);
	float CosAngle = cos(Angle);
	float SinAngle = sin(Angle);

	return VectorToRotate * CosAngle + Perpendicular * SinAngle;
}

inline bool PointIsInsideSphere(const Vector& Point, const Sphere& S)
{
	Vector Difference = Point - S.Origin;
	return Length(Difference) < S.Radius;

}

inline bool SphereIntersecting(const Sphere& First, const Sphere& Second)
{
	Vector Difference = Second.Origin - First.Origin;
	return Length(Difference) < (First.Radius + Second.Radius);
}

inline bool RaySphereIntersection(const Ray& R, const Sphere& S)
{
	// Specific case where the ray origin is inside the sphere
	if(PointIsInsideSphere(R.Origin, S))
		return true;

	bool WasProjectionPositive = false;

	Vector Projection = R.ProjectPoint(S.Origin, &WasProjectionPositive);

	if(!WasProjectionPositive)
		return false;

	Vector VecToProjection = S.Origin - Projection;

	return Length(VecToProjection) < S.Radius;
}

inline bool SpherePlaneIntersection(const Sphere& S, const Plane& P)
{
	return abs(P.DistanceToPoint(S.Origin)) <= S.Radius;
}

inline bool ProjectRayToPlane(const Ray& R, const Plane& P, Vector& OutIntersectPoint)
{
	float Distance = P.DistanceToPoint(R.Origin);
	float CosAngle = Dot(R.Direction, -P.Normal);
	float RayLength = Distance / CosAngle;

	if (RayLength < 0.f)
	{
		OutIntersectPoint = Vector(0.f);
		return false;
	}

	OutIntersectPoint = R.GetPoint(RayLength);
	return true;
}