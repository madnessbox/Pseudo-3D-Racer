#pragma once
#include "MathUtils.h"

struct Cube
{
	Cube() : Origin(0.f), Width(10), Height(10) {}
	Cube(Vector Origin, int Width, int Height, float RotAngle) : 
		Origin(Origin), 
		RotAngle(RotAngle), 
		Width(Width),
		Height(Height){}

	Vector Origin;
	int Width;
	int Height;
	float RotAngle;
};

inline void RotateCube(const Cube& C, const float& Angle)
{

}

inline void DrawCube(const Cube& C, unsigned int Color = 0xFFFFFFFF)
{
	Vector Perp = PerpLeft(C.Origin);
	float cosAngle = cos(C.RotAngle);
	float sinAngle = sin(C.RotAngle);

	Vector newVec = C.Origin * cosAngle + Perp * sinAngle;

	engDrawLine(C.Origin.x, C.Origin.y, newVec.x, newVec.y);
}