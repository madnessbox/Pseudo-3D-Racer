#include "Camera.h"
#include <math.h>

Camera::Camera(float Xpos, float Ypos, float Zpos)
{
	Position.X = Xpos;
	Position.Y = Ypos;
	Position.Z = Zpos;
};
Camera::Camera() 
{
	Position.X = Position.Y = Position.Z = 0;
};

void Camera::SetCameraPosition(float NewX, float NewY, float NewZ)
{
	Position.X = NewX;
	Position.Y = NewY;
	Position.Z = NewZ;
}
void Camera::SetCameraPosition(Vector3 NewPosition)
{
	Position = NewPosition;
}