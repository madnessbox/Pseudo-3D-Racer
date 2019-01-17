#include "Car.h"
#include "TinyEngine.h"
#include "Color.h"

Car::Car(int WindowWidth, int WindowHeight) : WindowWidth(WindowWidth), WindowHeight(WindowHeight)
{
	CarOrigin = Vector(WindowWidth / 2, WindowHeight - 500);
}

void Car::RenderCar()
{

	CarOrigin.y = CarOrigin.y < WindowHeight - 300 ? CarOrigin.y += CarGravity : CarOrigin.y;
	RenderBody();
}

void Car::RenderBody()
{

	if (TurnScale <= -1) // Full Left
	{
		// High ress
		//engDrawSprite(CarOrigin.x - ((77 * 5) / 2), CarOrigin.y, 77 * 5, 45 * 5, 77, 45, 11, 123, "OutrunSprites.png");

		// Low ress
		engDrawSprite(CarOrigin.x - ((39 * 10 ) / 2), CarOrigin.y, 39 * 10, 23 * 10, 39, 23, 5, 61, "OutrunSpritesS.png");
	}
	else if (TurnScale < -0.4f && TurnScale > -1) // Half Left
	{
		// High ress
		//engDrawSprite(CarOrigin.x - ((78 * 5) / 2), CarOrigin.y, 78 * 5, 45 * 5, 78, 45, 98, 123, "OutrunSprites.png");

		// Low ress
		engDrawSprite(CarOrigin.x - ((39 * 10 ) / 2), CarOrigin.y, 39 * 10, 23 * 10, 39, 23, 49, 61, "OutrunSpritesS.png");
	}
	else if (TurnScale > 0.4f && TurnScale < 1) // Half Right
	{
		// High ress
		//engDrawSprite(CarOrigin.x - ((78 * 5) / 2), CarOrigin.y, 78 * 5, 45 * 5, 78, 45, 272, 123, "OutrunSprites.png");

		// Low ress
		engDrawSprite(CarOrigin.x - ((39 * 10 ) / 2), CarOrigin.y, 39 * 10, 23 * 10, 39, 23, 136, 61, "OutrunSpritesS.png");
	}
	else if (TurnScale >= 1) // Full Right
	{
		// High ress
		//engDrawSprite(CarOrigin.x - ((77 * 5 ) / 2), CarOrigin.y, 77 * 5, 45 * 5, 77, 45, 360, 123, "OutrunSprites.png");

		// Low ress
		engDrawSprite(CarOrigin.x - ((38 * 10) / 2), CarOrigin.y, 38 * 10, 23 * 10, 38, 23, 180, 61, "OutrunSpritesS.png");
	}
	else // Forward
	{
		// High ress
		//engDrawSprite(CarOrigin.x - ((78 * 5 ) / 2), CarOrigin.y, 78 * 5, 45 * 5, 78, 45, 185, 123, "OutrunSprites.png");

		// Low ress
		engDrawSprite(CarOrigin.x - ((39 * 10) / 2), CarOrigin.y, 39 * 10, 23 * 10, 39, 23, 92, 61, "OutrunSpritesS.png");
	}
	
}