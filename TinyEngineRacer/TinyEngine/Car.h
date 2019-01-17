#pragma once
#include "Vector.h"

class Car
{
public:
	Car(int WindowWidth, int WindowHeight);

	Vector CarOrigin;

	void RenderCar();
	void RenderBody();

	float CarGravity = 9.8f;

	int TurnSpriteNum = 0;

	float TurnScale = 1;


private:
	int WindowWidth;
	int WindowHeight;
};

