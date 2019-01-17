#include "TinyEngine.h"
#include "Collision.h"
#include "Vector.h"
#include "WorldGenerator.h"
#include "Camera.h"
#include "Car.h"

#include <cstdlib>
#include <math.h>
#include <time.h>

void main()
{
	engInit(1500, 1000);
	srand(time(NULL));

	Camera Cam;
	Cam.Width = 1500;
	Cam.Height = 1000;
	Cam.Position.X = 0;
	Cam.Position.Y = 4;
	Cam.Position.Z = 1.2f;

	WorldGenerator WG(Cam.Width, Cam.Height, Cam);
	
	WG.PlayerCar = new Car(Cam.Width, Cam.Height);

	while (engIsOpen())
	{

		if (engGetKeyDown(Key::Escape))
			engClose();

		// Increase / Decrease FoV
		if (engGetKey(Key::PageUp))
			Cam.Depth += 0.01f;

		if (engGetKey(Key::PageDown))
			Cam.Depth -= 0.01f;


		// Move Camera
		if (engGetKey(Key::NumPad8))
			Cam.Position.Y += 0.1f;

		if (engGetKey(Key::NumPad2))
			Cam.Position.Y -= 0.1f;

		if (engGetKey(Key::NumPad4))
			Cam.Position.X -= 0.1f;

		if (engGetKey(Key::NumPad6))
			Cam.Position.X += 0.1f;


		// Move Forwards / Backwards / Right / Left
		if (engGetKey(Key::Up))
			Cam.Position.Z += 1.5f;

		if (engGetKey(Key::Down))
			Cam.Position.Z -= 1.5f;

		if (engGetKey(Key::Left))
		{
			Cam.Position.X -= 0.2f;
			WG.PlayerCar->TurnScale =
				WG.PlayerCar->TurnScale < -1 ?
				WG.PlayerCar->TurnScale = -1 :
				WG.PlayerCar->TurnScale -= 0.2f;
		}
			//WG.PlayerCar->TurnScale -= 0.2f;
		else if (engGetKey(Key::Right))
		{
			Cam.Position.X += 0.2f;
			WG.PlayerCar->TurnScale =
				WG.PlayerCar->TurnScale > 1 ?
				WG.PlayerCar->TurnScale = 1 :
				WG.PlayerCar->TurnScale += 0.2f;
		}
			//WG.PlayerCar->TurnScale += 0.2f;
		else
		{
			WG.PlayerCar->TurnScale =
				WG.PlayerCar->TurnScale < 0 ? 
				WG.PlayerCar->TurnScale += 0.2f :
				WG.PlayerCar->TurnScale -= 0.2f;
		}

		WG.DrawWorld();


		engUpdate();
	}

	engDestroy();
}