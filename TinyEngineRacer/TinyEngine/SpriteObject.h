#pragma once
#include "Vector.h"

class SpriteObject
{
public:
	SpriteObject(class Vector Position, char* SpriteFileName, bool IsAnimated);

	char* SpriteFileName;

private:
	bool IsAnimated;
	Vector Position;

};
