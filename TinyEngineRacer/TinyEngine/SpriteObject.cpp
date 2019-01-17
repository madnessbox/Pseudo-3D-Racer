#include "SpriteObject.h"

SpriteObject::SpriteObject(class Vector Position, char* SpriteFileName = "NULL", bool IsAnimated = false) :
	Position(Position), SpriteFileName(SpriteFileName), IsAnimated(IsAnimated)
{
	// Todo: Make roadside sprites work;
};