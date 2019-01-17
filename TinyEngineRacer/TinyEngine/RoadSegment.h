#pragma once
#include "Vector3.h"

class Vector;
class Camera;

class RoadSegment
{
public:
	RoadSegment(Vector3 Position3D, int Width, float Length) : Position3D(Position3D), Width(Width), ZLength(Length){};
	RoadSegment() : Position3D(Vector3(0,0,0)) {};

	Vector Project(const Camera& Cam);

	Vector3 Position3D;
	Vector ScreenPosition;
	int RenderColor = 0x434447FF;
	bool Render = true;
	int Width = 10000;
	int DefWidth = 300;
	float ZLength = 200;
	float Scale = 1;
	float Curve = 0;
	float Hill = 0;
	int Index = 0;

	char* LeftSideSprite = "NULL";
	char* RightSideSprite = "NULL";
};
