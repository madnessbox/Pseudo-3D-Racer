#pragma once
#include "Vector3.h"

struct Screen
{
public:
	Screen(float Xpos, float Ypos, float Zpos) : Position(Xpos, Ypos, Zpos) {};
	Screen(Vector3 Position) : Position(Position) {};
	Screen() : Position(0, 0, 0) {};

	Vector3 Position;
};