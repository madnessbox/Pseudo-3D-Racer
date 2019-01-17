#pragma once
#include "Vector3.h"

struct Camera
{
public:
	Camera(float Xpos, float Ypos, float Zpos) : Position(Xpos, Ypos, Zpos) {};
	Camera(Vector3 Position) : Position(Position) {};
	Camera() : Position(0,0,0) {};

	Vector3 Position;

	unsigned int Width;
	unsigned int Height;
	float Depth = 0.55f;
	float FOV;
};