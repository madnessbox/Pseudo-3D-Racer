#include "RoadSegment.h"
#include "Vector.h"
#include "Vector3.h"
#include "Camera.h"

Vector RoadSegment::Project(const Camera& Cam)
{
	// Reset Values
	Scale = 1;
	Width = 10000;
	ZLength = 200;
	Scale = 1;

	Vector ScreenCoords;
	Vector3 CamCoordDif;
	Scale = Cam.Depth / (Position3D.Z - Cam.Position.Z);

	ScreenCoords.y = (1 - Scale * (Position3D.Y - Cam.Position.Y)) * (Cam.Height / 2);
	ScreenCoords.x = (Scale * (Position3D.X + Curve - Cam.Position.X)) * (Cam.Width / 2);

	ScreenCoords.y = ScreenCoords.y < 0 ? 0 : ScreenCoords.y;

	Width *= Scale;
	ZLength *= Scale;

	return ScreenCoords;
}